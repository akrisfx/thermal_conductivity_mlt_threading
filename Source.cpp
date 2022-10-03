#include <iostream>
#include <math.h>
#include <cmath>
#include <numbers>
#include <iomanip>
#include <memory>

//#define _USE_MATH_DEFINES

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

//void copy_arr(double[] &qwdn, double[n_l_int] &copy) {
//
//}

int main() {
	//cout << std::fixed << std::setprecision(6); // «адаем точность дл€ double в кауте, думаю будет достаточно
	
	constexpr double l = 1.0;
	constexpr double h = 0.125;
	constexpr double n_l = l / h;
	constexpr int n_l_int = l / h;
	if (n_l != n_l_int) {
		cout << "invalid";
		return 404;
	}
	constexpr double tau = 0.0001;
	constexpr int n_tau = 30;

	double* arr_tau = new double[n_tau + 1];
	tau_list(arr_tau, n_tau, tau);

	double* arr_l = new double[n_l_int + 1];
	tau_list(arr_l, n_l_int, h);

	//for (int i = 0; i < n_tau + 1; i++) {
	//	//arr_tau[i] = tau * i;
	//	cout << arr_tau[i] << ' ';
	//}
	//cout << endl << endl;
	//for (int i = 0; i < n_l_int + 1; i++) {
	//	cout << arr_l[i] << ' ';
	//}
	cout << endl;
	double prev_str[n_l_int + 1] {0};
	double current_str[n_l_int + 1] {0};

	for (int i = 0; i < n_tau + 1; i++) {
		double t = arr_tau[i];
		cout << std::setw(6) << t <<  "   |";

		for (int j = 0; j < n_l_int + 1; j++) {
			double x = arr_l[j];
			double fi_x;
			//cout << std::setw(8) << x;
			if (t == 0) {
				if (x == 0 || x == l){
					fi_x = 0;
				}
				else {
					fi_x = fi(x);
					fi_x = (round(fi_x * 1000) / 1000);
					if (fi_x == 0.0 || fi_x == -0.0) {
						fi_x = 0;
					}
				}
				prev_str[j] = fi_x;
			}
			else {
				if (x == 0 || x == l) {
					fi_x = 0;
					current_str[j] = fi_x;
				}
				else {
					fi_x = tau * ((prev_str[j - 1] - 2*prev_str[j] + prev_str[j + 1]) / pow(h, 2)) + prev_str[j];
					current_str[j] = fi_x;
				}
			}
			cout << std::setw(12) << fi_x;
		}
		if (i != 0) {
			for (int k = 0; k < n_l_int; k++) {
				prev_str[k] = current_str[k];
			}
		}
		
		//prev_str = current_str;
		cout << endl;
	}
	delete[] arr_tau;
	delete[] arr_l;

	cout << pi << endl;
	system("pause");
	return 0;
}
