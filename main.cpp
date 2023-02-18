#include <iostream>
#include <iomanip>
#include <cmath>

int main()
{
    std::cout.precision(2);          // 2 digits after comma
    std::cout.setf(std::ios::fixed); // fixed digits format after comma
    int n, i, j, k, flag = 0, count = 0;

    std::cout << "Enter the number of equations:\n";
    std::cin >> n;
    double a[n][n + 1]; // the elements of the augmented matrix
    double x[n];        // the values of variables
    double eps, y;      // epsilon & y

    std::cout << "Enter the elements of the matrix:\n";
    for (i = 0; i < n; i++)
    {
        for (j = 0; j <= n; j++)
        {
            std::cin >> a[i][j];
        }
    }

    std::cout << "Enter the initial values of the variables:\n";
    for (i = 0; i < n; i++)
    {
        std::cin >> x[i];
    }

    std::cout << "Enter the accuracy upto which you want the solution:\n";
    std::cin >> eps;

    for (i = 0; i < n; i++)
    { // partial pivotisation to make the equations diagonally dominant
        for (k = i + 1; k < n; k++)
        {
            if (abs(a[i][i]) < abs(a[k][i])) // compare absolute values
            {
                for (j = 0; j <= n; j++)
                {
                    double temp = a[i][j];
                    a[i][j] = a[k][j];
                    a[k][j] = temp;
                }
            }
        }
    }
    std::cout << "Iteration" << std::setw(10);
    for (i = 0; i < n; i++)
    {
        std::cout << "x" << i << std::setw(18);
    }
    std::cout << "\n";
    do // iterations to calculate the solution
    {
        std::cout << "\n"
                  << count + 1 << "." << std::setw(16);
        for (i = 0; i < n; i++)
        {
            y = x[i];
            x[i] = a[i][n];
            for (j = 0; j < n; j++)
            {
                if (j != i)
                    x[i] = x[i] - a[i][j] * x[j];
            }
            x[i] = x[i] / a[i][i];
            if (abs(x[i] - y) <= eps) // Compare the ne value with the last value
                flag++;
            std::cout << x[i] << std::setw(18);
        }
        std::cout << "\n";
        count++;
    } while (flag < n); // If the values of all the variables don't differ from their previious values with error more than eps then flag must be n and hence stop the loop

    // print the solution
    std::cout << "\n The solution is as follows:\n";
    for (i = 0; i < n; i++)
    {
        std::cout << "x" << i << " = " << x[i] << std::endl;
    }

    return 0;
}