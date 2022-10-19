#include <iostream>
#include <math.h>
#include <cmath>
#include <numbers>
#include <iomanip>
#include <memory>
#include <thread>
#include <atomic>
#include <mutex>

//#define _USE_MATH_DEFINES

// на вход задается некоторая строка, необходимо вывести из него колво цифр и колво букв



using std::cout;
using std::cin;
using std::endl;

constexpr double pi = std::numbers::pi;
constexpr double l = 1.0;
constexpr double h = 0.125;
constexpr double n_l = l / h;
constexpr int n_l_int = l / h;

constexpr double tau = 0.0001;
constexpr int n_tau = 30;

constexpr int val_on_core = n_l_int / 4;


//void tau_list(double*& arr, const int& size_arr, const double& step) {
//	for (int i = 0; i <= size_arr; i++) {
//		arr[i] = step * i;
//	}
//}

template<unsigned N>
constexpr double* tau_list(const double& step)
{
	double* res = new double[N];
	for (int i = 0; i <= N; i++) {
		res[i] = step * i;
	}
	return res;
}
struct arrs {
	double prev_str[n_l_int + 1]{ 0 };
	double current_str[n_l_int + 1]{ 0 };
	const double* arr_tau = tau_list<n_tau>(tau);
	const double* arr_l = tau_list<n_l_int>(h);
};




double fi(const double& x) {
	return 4 * (sin(2 * pi * x) * pow(cos(pi * x), 2));
}

void in_Thread(int start, int end, arrs& a, double& t) {
		for (int j = start; j < end; j++) {
			double x = a.arr_l[j];
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
					//m.unlock();
				}
			}
			//u_x_t = (round(u_x_t * 1000) / 1000);
			//cout << std::setw(8) << u_x_t;
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
	
	 
	//cout << val_on_core << endl;
	
	std::mutex m;

	int mlt_for_loop[6];
	for (int i = 0; i < 4; i++) {
		mlt_for_loop[i] = val_on_core * i;
		cout << mlt_for_loop[i] << ' ';
	}


	arrs a;


	cout << endl << std::setw(10) << "        |";

	for (int i = 0; i <= n_l_int; i++) {
		cout << std::setw(8) << a.arr_l[i];
	}
	cout << endl;

	for (int i = 0; i <= n_l_int; i++) {
		cout << "_________";
	}

	cout << endl;
	cout << '\n';
	


	for (int i = 0; i <= n_tau; i++) {
		double t = a.arr_tau[i];
		cout << std::setw(6) << t <<  "   |";
		int thread_test = 0;

		std::thread t1([&]() {
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

		for (int j = 0; j < n_l_int + 1; j++) {
			double u_x_t = (round(a.current_str[j] * 1000) / 1000);
			cout << std::setw(8) << u_x_t;
		}

		if (i != 0) {
			for (int k = 0; k < n_l_int; k++) {
				a.prev_str[k] = a.current_str[k];
			}
		}
		
		//prev_str = current_str;
		cout << endl;
		//cout << thread_test << endl;
	}
	/*delete[] arr_tau;
	delete[] arr_l;*/

	//cout << pi << endl;
	system("pause");
	return 0;
}
