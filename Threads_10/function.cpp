// Tymoteusz Lekszycki
// 31.01.2016

#include <cstdio>
#include <thread>
#include <mutex>

std::mutex mtx;

void addTwoNumbers(int x, int y, int* result) {
	std::lock_guard<std::mutex> lock(mtx);
	*result = x + y;
}

int main(int argc, char* argv[])
{
	int result = 0;

	std::thread t(addTwoNumbers, 2, 6, &result);

	int mainResult = 4 + 3;

	t.join();

	printf("Result from main: %ld\n", mainResult);
	printf("Result from thread: %ld\n", result);

	return EXIT_SUCCESS;
}