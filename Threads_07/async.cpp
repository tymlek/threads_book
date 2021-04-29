// Tymoteusz Lekszycki
// 02.02.2016

#include <cstdio>
#include <future>			// promise, future, packed_task, async

double multiply(double x, double y)
{
	return (x * y);
}

int main()
{
	std::future<double> result = std::async(multiply, 9, 5);

	printf("Result: %fd\n", result.get());

	return EXIT_SUCCESS;
}