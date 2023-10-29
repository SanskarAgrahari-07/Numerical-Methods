#include <iostream>
#include <vector>
#include <chrono>

double inverseLagrangeInterpolation(const std::vector<double>& x, const std::vector<double>& y, double targetY) {
    if (x.size() != y.size()) {
        throw std::invalid_argument("Input vectors x and y must have the same size.");
    }

    int n = x.size();
    double result = 0;

    for (int i = 0; i < n; i++) {
        double term = y[i];
        for (int j = 0; j < n; j++) {
            if (i != j) {
                term *= (targetY - x[j]) / (x[i] - x[j]);
            }
        }
        result += term;
    }

    return result;
}

int main() {
    std::vector<double> x = {1, 2, 3, 4, 5};
    std::vector<double> y = {1, 8, 27, 64, 125};
    double targetY = 10;

    auto start_time = std::chrono::high_resolution_clock::now();
    double result = inverseLagrangeInterpolation(x, y, targetY);
    auto end_time = std::chrono::high_resolution_clock::now();

    std::cout << "Inverse Lagrange Interpolation at y="<<targetY <<": " << result << std::endl;

    auto execution_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Execution Time: " << execution_time.count() << " microseconds" << std::endl;

    return 0;
}
