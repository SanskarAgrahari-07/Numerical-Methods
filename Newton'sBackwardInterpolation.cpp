#include <iostream>
#include <vector>
#include <chrono>

void print_difference_table(const std::vector<std::vector<double>>& table, const std::vector<double>& data_x) {
    int n = table.size();
    for (int i = 0; i < n; ++i) {
        std::cout << data_x[i] << "\t";
        for (int j = 0; j < n - i; ++j) {
            std::cout << table[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

double newton_backward_interpolation(double x, const std::vector<double>& data_x, const std::vector<double>& data_y, std::vector<std::vector<double>>& difference_table) {
    int n = data_x.size();
    if (n != data_y.size()) {
        throw std::invalid_argument("Data lists must have the same length");
    }

    for (int i = 0; i < n; ++i) {
        difference_table[i][0] = data_y[i];
    }

    for (int j = 1; j < n; ++j) {
        for (int i = n - 1; i >= j; --i) {
            difference_table[i][j] = difference_table[i][j - 1] - difference_table[i - 1][j - 1];
        }
    }

    double h = data_x[1] - data_x[0];
    double u = (x - data_x[n - 1]) / h;

    double result = difference_table[n - 1][0];
    double product_term = 1.0;

    for (int i = 1; i < n; ++i) {
        product_term *= (u + i - 1) / i;
        result += product_term * difference_table[n - 1][i];
    }

    return result;
}

int main() {
    std::vector<double> data_x = {0, 5, 10, 15, 20};
    std::vector<double> data_y = {20, 25, 30, 35, 40};
    std::vector<std::vector<double>> difference_table(data_x.size(), std::vector<double>(data_x.size(), 0.0));

    double x_to_interpolate = 18;

    auto start_time = std::chrono::high_resolution_clock::now();
    double result_backward = newton_backward_interpolation(x_to_interpolate, data_x, data_y, difference_table);
    auto end_time = std::chrono::high_resolution_clock::now();

    std::chrono::microseconds elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    std::cout << "Newton's Backward Interpolation at x=" << x_to_interpolate << ": " << result_backward << std::endl;
    std::cout << "Execution Time: " << elapsed_time.count() << " microseconds" << std::endl;

    std::cout << "Difference Table:" << std::endl;
    print_difference_table(difference_table, data_x);

    return 0;
}
