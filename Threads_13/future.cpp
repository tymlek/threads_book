// Tymoteusz Lekszycki
// 01.02.2016

#include <cstdio>
#include <thread>
#include <future>

void calculate(int x, int y, std::promise<int>& res)
{
	res.set_value(x * y);
}

int main(int argc, char* argv[])
{
	std::promise<int> resPromise;
	std::future<int> resFuture = resPromise.get_future();

	std::thread t(calculate, 60, 10, std::ref(resPromise));

	int result = resFuture.get();
	printf("Result: %ld\n", result);

	t.join();

	return EXIT_SUCCESS;
}