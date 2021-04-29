#include <iostream>
#include <thread>
#include <stdexcept>

//-----------------------------------------------------------------------------

using namespace std;

//-----------------------------------------------------------------------------

struct Func {
public:
	Func(int& i_) : i {i_} {}

	void operator()() {
		for (auto j = 0; j!=1000; ++j) {
			do_something(i);
		}
	}
private:
	int& i;
	void do_something(int& i) {
		++i;
		cout<<"\nFunc thread counting: "<<i<<"\n";
	}
};

//-----------------------------------------------------------------------------

void do_something_in_current_thread() {
	for (auto k = 0; k!=10000; ++k) {
		cout<<"\nMain thread counting: "<<k<<"\n";
	}
}

//-----------------------------------------------------------------------------

void f() {
	int some_local_state = 0;
	Func my_func {some_local_state};
	thread t {my_func};

	try {
		do_something_in_current_thread();
	}
	catch (...) {
		t.join();
		throw;
	}

	t.join();
}

int main() {
	f();

	return 0;
}