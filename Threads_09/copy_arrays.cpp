// Tymoteusz Lekszycki
// 01.02.2016

#include <cstdio>
#include <thread>
#include <mutex>

#define ARRAY_SIZE 10000

std::mutex mtx;

void copyArray(long* sourceBegin, long* sourceEnd, long* dest)
{
	std::lock_guard<std::mutex> lock(mtx);

	for (auto p = sourceBegin; p != sourceEnd; ++p) {
		*dest = *p;
		++dest;
	}
}

int main(int argc, char* argv[])
{
	long source1[ARRAY_SIZE];
	long source2[ARRAY_SIZE];
	long dest1[ARRAY_SIZE];
	long dest2[ARRAY_SIZE];

	for (auto i = 0; i != ARRAY_SIZE; ++i) {
		source1[i] = i;
		source2[i] = i;
	}

	std::thread t1(copyArray, &source1[0], &source1[ARRAY_SIZE], &dest1[0]);
	std::thread t2(copyArray, &source2[0], &source2[ARRAY_SIZE], &dest2[0]);

	t1.join();
	t2.join();

	for (auto i = 0; i != ARRAY_SIZE; ++i)
		printf("%ld ", dest1[i]);

	printf("\n");

	for (auto i = 0; i != ARRAY_SIZE; ++i)
		printf("%ld ", dest2[i]);

	return EXIT_SUCCESS;
}