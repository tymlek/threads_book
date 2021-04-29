// Tymoteusz Lekszycki
// 02.02.2016

#include <cstdio>
#include <future>				// promise, future, packaged_task

long add(long x, long y)
{
	return (x + y);
}

int main()
{
	std::packaged_task<long(long, long)> pt1(add);

	pt1(4, 8);

	auto result = pt1.get_future();

	printf("Result: %ld\n", result.get());

	return EXIT_SUCCESS;
}