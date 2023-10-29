#include <iostream>
#include <vector>
#include <chrono>

double newton_forward_divided_difference_interpolation(double x, const std::vector<double>& data_x, const std::vector<double>& data_y) {
    if (data_x.size() != data_y.size()) {
        throw std::invalid_argument("Data lists must have the same length");
    }

    int n = data_x.size();
    double result = 0.0;

    auto start_time = std::chrono::high_resolution_clock::now();

    // Create the divided difference table
    std::vector<std::vector<double>> divided_differences(n, std::vector<double>(n, 0.0));
    for (int i = 0; i < n; i++) {
        divided_differences[i][0] = data_y[i];
    }
    for (int j = 1; j < n; j++) {
        for (int i = j; i < n; i++) {
            divided_differences[i][j] = (divided_differences[i][j - 1] - divided_differences[i - 1][j - 1]) /
                (data_x[i] - data_x[i - j]);
        }
    }

    // Calculate the interpolation using the divided differences
    double product_term = 1.0;
    for (int j = 0; j < n; j++) {
        result += divided_differences[j][j] * product_term;
        product_term *= (x - data_x[j]);
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::microseconds elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    // Print the results
    std::cout << "Newton's Forward Divided Difference Interpolation at x=" << x << ": " << result << std::endl;
    std::cout << "Execution Time: " << elapsed_time.count() << " microseconds" << std::endl;

    // Print the difference table
    std::cout << "Difference Table:" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << data_x[i] << "\t";
        for (int j = 0; j <= i; j++) {
            std::cout << divided_differences[i][j] << "\t";
        }
        std::cout << std::endl;
    }

    return result;
}

int main() {
    std::vector<double> data_x = {0, 3, 6, 8, 11};
    std::vector<double> data_y = {1, 2, 4, 7, 11};
    double x_to_interpolate = 5;

    newton_forward_divided_difference_interpolation(x_to_interpolate, data_x, data_y);

    return 0;
}
