// Tymoteusz Lekszycki
// 01.02.2016

#include <cstdio>
#include <thread>
#include <future>

void multiply(int x, int y, std::promise<int>& res)
{
	res.set_value(x * y);

	printf("I'm in thread 1\n");
}

void printResult(std::future<int>& res)
{
	int result = res.get();

	printf("I'm in thread 2\n");
	printf("Result: %ld\n", result);
}

int main(int argc, char* argv[])
{
	int x = 3;
	int y = 4;
	std::promise<int> resProm;
	std::future<int> resFut = resProm.get_future();

	std::thread t2(printResult, std::ref(resFut));
	std::thread t1(multiply, x, y,std::ref(resProm));

	t1.join();
	t2.join();
	return EXIT_SUCCESS;
}