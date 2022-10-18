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
void tau_list(double* &arr, const int &size_arr, const double &step) {
	for (int i = 0; i <= size_arr; i++) {
		arr[i] = step * i;
	}
}

double fi(const double& x) {
	return 4 * (sin(2 * pi * x) * pow(cos(pi * x), 2));
}

//void in_Thread(auto& n_l_int, int* arr_l[], double &t, const double &tau, double* prev_str[], double* currrent_str, int) {
//
//}

//void copy_arr(double[] &qwdn, double[n_l_int] &copy) {
//
//}

int main() {
	//cout << std::fixed << std::setprecision(6); // Задаем точность для double в кауте, думаю будет достаточно
	
	constexpr double l = 1.5;
	constexpr double h = 0.125;
	constexpr double n_l = l / h;
	constexpr int n_l_int = l / h;
	if (n_l != n_l_int) {
		cout << "invalid";
		return 404;
	}
	constexpr double tau = 0.0001;
	constexpr int n_tau = 30;
	
	int val_on_core = n_l_int / 4;
	
	std::mutex m;
	cout << val_on_core << endl;

	int mlt_for_loop[6];
	for (int i = 0; i < 4; i++) {
		mlt_for_loop[i] = val_on_core * i;
		cout << mlt_for_loop[i] << ' ';
	}


	double* arr_tau = new double[n_tau + 1];
	tau_list(arr_tau, n_tau, tau);

	double* arr_l = new double[n_l_int + 1];
	tau_list(arr_l, n_l_int, h);

	double prev_str[n_l_int + 1] {0};
	double current_str[n_l_int + 1] {0};

	//for (int i = 0; i < n_tau + 1; i++) {
	//	//arr_tau[i] = tau * i;
	//	cout << arr_tau[i] << ' ';
	//}
	//cout << endl << endl;
	//for (int i = 0; i < n_l_int + 1; i++) {
	//	cout << arr_l[i] << ' ';
	//}


	cout << endl << std::setw(10) << "        |";

	for (int i = 0; i < n_l_int + 1; i++) {
		cout << std::setw(8) << arr_l[i];
	}
	cout << endl;

	for (int i = 0; i < n_l_int; i++) {
		cout << "_________";
	}

	cout << endl;
	cout << '\n';

	for (int i = 0; i < n_tau + 1; i++) {
		double t = arr_tau[i];
		cout << std::setw(6) << t <<  "   |";
		int thread_test = 0;

		std::thread t1([&]() {
			thread_test++;
			for (int j = 0; j < mlt_for_loop[1]; j++) {
				double x = arr_l[j];
				double u_x_t;
				//cout << std::setw(8) << x;
				if (t == 0) {
					if (x == 0 || x == l){
						u_x_t = 0;
					}
					else {
						u_x_t = fi(x);
						u_x_t = (round(u_x_t * 1000) / 1000);
						if (u_x_t == 0.0 || u_x_t == -0.0) {
							u_x_t = 0;
						}
					}
					m.lock();
					prev_str[j] = u_x_t;
					m.unlock();
				}
				else {
					if (x == 0 || x == l) {
						u_x_t = 0;
						//m.lock();
						current_str[j] = u_x_t;
						//m.unlock();
					}
					else {
						//m.lock();
						u_x_t = tau * ((prev_str[j - 1] - 2 * prev_str[j] + prev_str[j + 1]) / pow(h, 2)) + prev_str[j];
						current_str[j] = u_x_t;
						//m.unlock();
					}
				}
				//u_x_t = (round(u_x_t * 1000) / 1000);
				//cout << std::setw(8) << u_x_t;
			}
			});

		std::thread t2([&]() {
			thread_test++;
			for (int j = mlt_for_loop[1]; j < mlt_for_loop[2]; j++) {
				double x = arr_l[j];
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
					m.lock();
					prev_str[j] = u_x_t;
					m.unlock();
				}
				else {
					if (x == 0 || x == l) {
						u_x_t = 0;
						//m.lock();
						current_str[j] = u_x_t;
						//m.unlock();
					}
					else {
						//m.lock();
						u_x_t = tau * ((prev_str[j - 1] - 2 * prev_str[j] + prev_str[j + 1]) / pow(h, 2)) + prev_str[j];
						current_str[j] = u_x_t;
						//m.unlock();
					}
				}
				//u_x_t = (round(u_x_t * 1000) / 1000);
				//cout << std::setw(8) << u_x_t;
			}
			});

		std::thread t3([&]() {
			thread_test++;
			for (int j = mlt_for_loop[2]; j < mlt_for_loop[3]; j++) {
				double x = arr_l[j];
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
					m.lock();
					prev_str[j] = u_x_t;
					m.unlock();
				}
				else {
					if (x == 0 || x == l) {
						u_x_t = 0;
						//m.lock();
						current_str[j] = u_x_t;
						//m.unlock();
					}
					else {
						//m.lock();
						u_x_t = tau * ((prev_str[j - 1] - 2 * prev_str[j] + prev_str[j + 1]) / pow(h, 2)) + prev_str[j];
						current_str[j] = u_x_t;
						//m.unlock();
					}
				}
				//u_x_t = (round(u_x_t * 1000) / 1000);
				//cout << std::setw(8) << u_x_t;
			}
			});

		std::thread t4([&]() {
			thread_test++;
			for (int j = mlt_for_loop[3]; j < n_l_int + 1; j++) {
				double x = arr_l[j];
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
					m.lock();
					prev_str[j] = u_x_t;
					m.unlock();
				}
				else {
					if (x == 0 || x == l) {
						u_x_t = 0;
						//m.lock();
						current_str[j] = u_x_t;
						//m.unlock();
					}
					else {
						//m.lock();
						u_x_t = tau * ((prev_str[j - 1] - 2 * prev_str[j] + prev_str[j + 1]) / pow(h, 2)) + prev_str[j];
						current_str[j] = u_x_t;
						//m.unlock();
					}
				}
				//u_x_t = (round(u_x_t * 1000) / 1000);
				//cout << std::setw(8) << u_x_t;
			}
			});

		t1.join();
		t2.join();
		t3.join();
		t4.join();

		for (int j = 0; j < n_l_int + 1; j++) {
			double u_x_t = (round(current_str[j] * 1000) / 1000);
			cout << std::setw(8) << u_x_t;
		}

		if (i != 0) {
			for (int k = 0; k < n_l_int; k++) {
				prev_str[k] = current_str[k];
			}
		}
		
		//prev_str = current_str;
		cout << endl;
		//cout << thread_test << endl;
	}
	delete[] arr_tau;
	delete[] arr_l;

	//cout << pi << endl;
	system("pause");
	return 0;
}
