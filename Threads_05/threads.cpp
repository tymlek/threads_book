#include <iostream>
#include <vector>
#include <numeric>
#include <thread>
#include <future>
#include <chrono>

//-----------------------------------------------------------------------------

using namespace std;

//-----------------------------------------------------------------------------

class F {
public:
	F(const vector<double>& vv, double* p) : v{vv}, res{p} {}
	void operator()();

private:
	const vector<double>& v;
	double* res;
};

//-----------------------------------------------------------------------------

void F::operator()() {
	for (auto num : v) {
		*res+=num;
	}
}

//-----------------------------------------------------------------------------

double accum(double* beg, double* end, double init) {
	return accumulate(beg,end,init);
}

//-----------------------------------------------------------------------------

void accum_ref(double* beg, double* end, double init, double* res) {
	*res = accumulate(beg,end,init);
}

//-----------------------------------------------------------------------------

double vector_sum(const vector<double>& v) {
	double sum = 0;
	for (auto number : v) {
		sum+=number;
	}
	return sum;
}

//-----------------------------------------------------------------------------

int main() {
	vector<double> numbers;

	for (auto i = 0; i<10000; ++i) {
		numbers.push_back(i);
	}

	auto v0 = &numbers[0];
	auto sz = numbers.size();

	auto t0 = std::chrono::high_resolution_clock::now();
	auto res_1 = async(accum,v0,v0+sz/2,0.0);
	auto res_2 = async(accum,v0+sz/2,v0+sz,0.0);
	auto t1 = std::chrono::high_resolution_clock::now();

	cout << "async:\n";
	cout << "Res: " << res_1.get()+res_2.get() << '\n';
	cout << "Duration: " << std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count() << " msec\n";

	t0 = std::chrono::high_resolution_clock::now();
	double res = accum(v0,v0+sz,0.0);
	t1 = std::chrono::high_resolution_clock::now();

	cout << "\naccum function:\n";
	cout << "Res: " << res << '\n';
	cout << "Duration: " << std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count() << " msec\n";

	res = 0;
	t0 = std::chrono::high_resolution_clock::now();
	thread thr{F{numbers,&res}};
	thr.join();
	t1 = std::chrono::high_resolution_clock::now();

	cout << "\nthread:\n";
	cout << "Res: " << res<<'\n';
	cout << "Duration: " << std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count() << " msec\n";

	double result_thr1 = 0;
	double result_thr2 = 0;
	t0 = std::chrono::high_resolution_clock::now();
	thread thr1{accum_ref,v0,v0+sz/2,0.0,&result_thr1};
	thread thr2{accum_ref,v0+sz/2,v0+sz,0.0,&result_thr2};
	thr1.join();
	thr2.join();
	res = result_thr1+result_thr2;
	t1 = std::chrono::high_resolution_clock::now();

	cout << "\nthread1 and 2:\n";
	cout << "Res: " << res << '\n';
	cout << "Duration: " << std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count() << " msec\n";

	res = 0;
	t0 = std::chrono::high_resolution_clock::now();
	res = vector_sum(numbers);
	t1 = std::chrono::high_resolution_clock::now();

	cout << "\nvector_sum:\n";
	cout << "Res: " << res << '\n';
	cout << "Duration: " << std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count() << " msec\n";

	return 0;
}