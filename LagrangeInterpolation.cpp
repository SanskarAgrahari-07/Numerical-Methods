#include <iostream>
#include <vector>
#include <chrono>

double lagrange_interpolation(double x, const std::vector<double>& data_x, const std::vector<double>& data_y) {
    if (data_x.size() != data_y.size()) {
        throw std::invalid_argument("Data lists must have the same length");
    }

    int n = data_x.size();
    double result = 0.0;

    auto start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < n; ++i) {
        double term = data_y[i];
        for (int j = 0; j < n; ++j) {
            if (j != i) {
                term = term * (x - data_x[j]) / (data_x[i] - data_x[j]);
            }
        }
        result += term;
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::microseconds elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    std::cout << "Lagrange Interpolation at x=" << x << ": " << result << std::endl;
    std::cout << "Execution Time: " << elapsed_time.count() << " microseconds" << std::endl;

    return result;
}

int main() {
    std::vector<double> data_x = {0, 5, 10, 15, 20};
    std::vector<double> data_y = {20, 25, 30, 35, 40};
    double x_to_interpolate = 17;

    lagrange_interpolation(x_to_interpolate, data_x, data_y);

    return 0;
}
