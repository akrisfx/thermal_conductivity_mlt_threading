#include <iostream>
#include <math.h>
#include <numbers>
#include <iomanip>
#include <memory>
#include <thread>
#include <atomic>
#include <mutex>
#include <chrono>
#include <vector>
using namespace std::chrono_literals;
//#define _USE_MATH_DEFINES

// на вход задается некоторая строка, необходимо вывести из него колво цифр и колво букв



using std::cout;
using std::cin;
using std::endl;

constexpr double pi = std::numbers::pi;
constexpr double l = 1.0;
constexpr double h = 0.001;
constexpr double n_l = l / h;
constexpr int n_l_int = l / h;

constexpr double tau = 0.001;
constexpr int n_tau = 300;
double t = 0;

constexpr uint32_t thread_count = 5;
constexpr int val_on_core = n_l_int / thread_count;
std::atomic_bool is_thread_finished[thread_count] = { false };
std::atomic_bool is_thread_stoped[thread_count];
bool thread_end = false;
std::atomic_bool thread_stop = false;



//template<unsigned N>
//double* tau_list(const double& step)
//{
//	double* res = new double[N];
//	for (int i = 0; i <= N; i++) {
//		res[i] = step * i;
//	}
//	return res;
//}

struct arrs {
	//std::atomic<double>* prev_str = new std::atomic<double>[n_l_int + 1];
	//std::atomic<double>* current_str = new std::atomic<double>[n_l_int + 1];
	double* prev_str = new double[n_l_int + 1]{ 0 };
	double* current_str = new double[n_l_int + 1]{ 0 };
	//double* arr_tau = tau_list<n_tau>(tau);
	//double* arr_l = tau_list<n_l_int>(h);
};


bool all_threads_finished() {
	for (short int i = 0; i < thread_count; ++i) {
		if (is_thread_finished[i] == false) {
			return false;
		}
	}
	return true;
}

double fi(const double& x) {
	return 4 * (sin(2 * pi * x) * pow(cos(pi * x), 2));
}

void in_Thread(int start, int end, arrs* b, int thread_number) {
	arrs &a = *b;
	while (!thread_end)
	{
		while (is_thread_stoped[thread_number]) {
			//std::this_thread::sleep_for(2ms);
		}
		for (int j = start; j < end; j++) {
			double x = h * j;
			double u_x_t;
			//cout << std::setw(8) << x;
			if (t == 0) {
				if (x == 0 || x == l) {
					u_x_t = 0;
				}
				else {
					u_x_t = fi(x);
					u_x_t = (round(u_x_t * 1000) / 1000);
					if (u_x_t == 0.0 || u_x_t == -0.0) {
						u_x_t = 0;
					}
				}
				//m.lock();
				a.prev_str[j] = u_x_t;
				//m.unlock();
			}
			else {
				if (x == 0 || x == l) {
					u_x_t = 0;
					//m.lock();
					a.current_str[j] = u_x_t;
					//m.unlock();
				}
				else {
					//m.lock();
					u_x_t = tau * ((a.prev_str[j - 1] - 2 * a.prev_str[j] + a.prev_str[j + 1]) / pow(h, 2)) + a.prev_str[j];
					a.current_str[j] = u_x_t;
					//std::cout << u_x_t << ' ';
					//m.unlock();
				}
			}
			//u_x_t = (round(u_x_t * 1000) / 1000);
			//cout << std::setw(8) << u_x_t;
		}
		is_thread_finished[thread_number] = true;
		is_thread_stoped[thread_number] = true;
		if (thread_number == 0) {

		};	
		/*while (thread_stop) {
			std::this_thread::sleep_for(1ms);
		}*/
	}
}



//void copy_arr(double[] &qwdn, double[n_l_int] &copy) {
//
//}


int main() {
	//cout << std::fixed << std::setprecision(6); // Задаем точность для double в кауте, думаю будет достаточно
	
	if (n_l != n_l_int) {
		cout << "invalid";
		return 404;
	}
	
	std::cout << "Thread count: " << thread_count << std::endl;
	 
	//cout << val_on_core << endl;
	
	std::mutex m;

	int mlt_for_loop[thread_count];
	for (int i = 0; i < thread_count; i++) {
		mlt_for_loop[i] = val_on_core * i;
		//cout << mlt_for_loop[i] << ' ';
	}


	arrs a;


	//cout << endl << std::setw(10) << "        |";

	for (int i = 0; i <= n_l_int; i++) {
		//cout << std::setw(8) << a.arr_l[i];
	}
	cout << endl;

	for (int i = 0; i <= n_l_int; i++) {
		//cout << "_________";
	}

	cout << endl;
	cout << '\n';
	std::thread* thread_arr = new std::thread[thread_count]; // ---1---

	// thread creating
	for (int thrd = 0; thrd < thread_count; ++thrd) {
		if (thrd == thread_count - 1) {
			thread_arr[thrd] = std::thread(in_Thread, mlt_for_loop[thrd], n_l_int, &a, thrd);  // ---1---
			/*thread_arr[thrd] = std::thread([&]() {
				in_Thread(mlt_for_loop[thrd], n_l_int, std::ref(a), std::ref(t));
			}); */																	   //	---2---
			//std::thread thrd_to_push(in_Thread, mlt_for_loop[thrd], n_l_int, a, t); // ---vec---
			//thread_arr.push_back(thrd_to_push); // ---vec---
		}
		else {
			thread_arr[thrd] = std::thread(in_Thread, mlt_for_loop[thrd], mlt_for_loop[thrd + 1], &a, thrd); // ---1---
			/*thread_arr[thrd] = std::thread([&]() {
				in_Thread(mlt_for_loop[thrd], mlt_for_loop[thrd + 1], std::ref(a), std::ref(t));
				}); */																				  // ---2---
				//std::thread thrd_to_push(in_Thread, mlt_for_loop[thrd], mlt_for_loop[thrd + 1], a, t); // ---vec---
				//thread_arr.push_back(thrd_to_push); // ---vec---
		}
	}
	
	
	auto t1 = std::chrono::steady_clock::now();

	for (int i = 0; i <= n_tau; i++) {


		t = tau * i;
		
		//std::vector<std::thread> thread_arr; // ---vec---
		
		// clear flags of finished thread
		for (int thrd = 0; thrd < thread_count; ++thrd) {
			is_thread_stoped[thrd] = false;
		}

		if (i == 0) {
			for (int thrd = 0; thrd < thread_count; ++thrd) {
				thread_arr[thrd].detach();
			}
		}

		while (!all_threads_finished()) {
			//std::this_thread::sleep_for(13ms);
		}
		//std::cout << all_threads_finished()

		for (int thrd = 0; thrd < thread_count; ++thrd) {
			is_thread_finished[thrd] = false;
		}

		// dynamic threads
		// -------------------------------------Diffrent realizacia-------------------------
		// hardcoded 4 threads

		/*std::thread t1([&]() {
			in_Thread(mlt_for_loop[0], mlt_for_loop[1], a, t);
			});

		std::thread t2([&]() {
			in_Thread(mlt_for_loop[1], mlt_for_loop[2], a, t);
		});

		std::thread t3([&]() {
			in_Thread(mlt_for_loop[2], mlt_for_loop[3], a, t);
		});

		std::thread t4([&]() {
			in_Thread(mlt_for_loop[3], n_l_int, a, t);
		});

		t1.join();
		t2.join();
		t3.join();
		t4.join();
		cout << std::setw(6) << t << "   |";
		for (int j = 0; j < n_l_int + 1; j++) {
			double u_x_t = (round(a.current_str[j] * 1000) / 1000);
			cout << std::setw(8) << u_x_t;
		}
		cout << endl;*/

		if (i != 0) {
			for (int k = 0; k < n_l_int; k++) {
				//a.prev_str[k].store(a.current_str[k]);
				a.prev_str[k] = a.current_str[k];
			}
		}
		
		//prev_str = current_str;
	}
	auto t2 = std::chrono::steady_clock::now();
	thread_end = true;
	delete[] thread_arr;
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (t2 - t1).count() / 1'000'000.0<< "[ms] " << std::endl;

	cout << std::setw(6) << t << "   |";
	for (int j = 0; j < 20 ; j++) {
		//double u_x_t = (round(a.current_str[j] * 1000) / 1000);
		//cout << std::setw(8) << u_x_t;
		std::cout << a.current_str[j] << ' ';
	}
	cout << endl;
	delete[] a.current_str;
	delete[] a.prev_str;


	//cout << pi << endl;
	system("pause");
	return 0;
}
