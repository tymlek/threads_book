// Tymoteusz Lekszycki
// 01.02.2016

#include <cstdio>
#include <thread>
#include <vector>
#include <future>
#include <mutex>

std::mutex mtx;

void add(const std::vector<unsigned long>& source, unsigned long* res)
{
	std::lock_guard<std::mutex> lock(mtx);

	for (auto i = source.begin(); i != source.end(); ++i)
		*res += *i;
}

class Add
{
public:
	Add(const std::vector<unsigned long>& source, unsigned long* res)
		: s(source), r(res)
	{}

	void operator()()
	{
		std::lock_guard<std::mutex> lock(mtx);

		for (auto p = s.begin(); p != s.end(); ++p)
			*r += *p;
	}

private:
	const std::vector<unsigned long>& s;
	unsigned long* r;
};

class AddFuture
{
public:
	AddFuture(const std::vector<unsigned long>& source, std::promise<unsigned long>& r)
		: s(source), res(r)
	{}

	void operator()()
	{
		for (auto p = s.begin(); p != s.end(); ++p)
			result += *p;
		res.set_value(result);
	}

private:
	const std::vector<unsigned long>& s;
	std::promise<unsigned long>& res;
	unsigned long result;
};

int main()
{
	std::vector<unsigned long> source;
	std::promise<unsigned long> resPro;
	std::future<unsigned long> resFut = resPro.get_future();

	unsigned long result1;
	unsigned long result2;

	for (auto i = 0; i != 20; ++i)
		source.push_back(rand());

	std::thread t1(add, std::cref(source), &result1);
	std::thread t2(Add(source, &result2));
	std::thread t3(AddFuture(source, std::ref(resPro)));

	printf("Waiting...\n");
	printf("Number of hardware processing units: %ld\n", std::thread::hardware_concurrency());
	printf("Result from th3: %uld\n", resFut.get());

	t1.join();
	t2.join();
	t3.join();

	printf("Result from th1: %uld\n", result1);
	printf("Result from th2: %uld\n", result2);

	return EXIT_SUCCESS;
}