// Tymoteusz Lekszycki
// 31.01.2016

#include <cstdio>
#include <thread>
#include <mutex>

class AddTwoNumbers {
private:
	int x;
	int y;
	std::mutex mtx;

public:
	int result;

	AddTwoNumbers(int x_, int y_)
		: x(x_), y(y_)
	{}

	void operator()() {
		std::lock_guard<std::mutex> lock(mtx);
		result = x + y;
	}
};

int main(int argc, char* argv[])
{
	AddTwoNumbers addTwoNumbers(2, 8);

	std::thread t(std::ref(addTwoNumbers));

	int x = 5;
	int y = 6;
	int result = x + y;

	t.join();

	printf("Result from main: %ld\n", result);
	printf("Result from thread: %ld\n", addTwoNumbers.result);

	return EXIT_SUCCESS;
}