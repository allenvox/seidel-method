#include <cmath>
#include <iostream>

using namespace std;

double okr(double X, double eps)
{
    int i = 0;
    while (eps != 1)
    {
        i++;
        eps *= 10;
    }
    int okr = pow(double(10), i);
    X = int(X * okr + 0.5) / double(okr);
    return X;
}

double normOfMatrix(double A[3][3], int N)
{
    // norm of matrix A
    double sum = 0;
    double sums[3];
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            sum += abs(A[i][j]);
        }
        sums[i] = sum;
        sum = 0;
    }
    double norm = sums[0];
    for (int i = 1; i < N; i++)
    {
        if (sums[i] > norm)
        {
            norm = sums[i];
        }
    }
    return norm;
}

double iterat(double A[3][3], double B[3], int N, double eps)
{
    double matrixNorm = normOfMatrix(A, N);
    double vectorNorm, coef;
    if (matrixNorm < 1)
    {
        cout << "\nНорма матрицы A = " << matrixNorm << " < 1  => сходится в Евклидовой метрике\n"
             << std::endl;

        int k = 0;
        int i, j;
        double X[N];
        double s, g, diff;
        do
        {
            s = 0;
            k++;
            for (i = 0; i < N; i++)
            {
                g = B[i];
                for (j = 0; j < N; j++)
                {
                    g += A[i][j] * X[j];
                }
                cout << "X" << i + 1 << " = " << g << endl;
                diff = X[i] - g; // delta x
                cout << "X" << i + 1 << "(прошлый) - X" << i + 1 << "(новый) = " << diff << "\n"
                     << endl;
                s += diff * diff; // (delta x) ^ 2
                X[i] = g;
            }
            vectorNorm = sqrt(s); // norm of vector = sqrt(sum of X^2)
            cout << "Норма (X" << i + 1 << " - X" << i << ") = " << vectorNorm << endl;
            coef = (matrixNorm / (1 - matrixNorm));
            // int iter = (int)ceil(log(1e-2 * (1 - matrixNorm) / vectorNorm)) / log(matrixNorm);
            // int iter = (int)(log(eps * (1 - vectorNorm) / matrixNorm) / log(vectorNorm));
            // cout << "\nОсталось итераций: " << iter << "\n"
            // << endl;
        } while ((coef * vectorNorm) >= eps);

        cout << "\nРешение системы:" << endl;
        for (i = 0; i < N; i++)
        {
            cout << "X" << i << " = " << okr(X[i], eps) << endl;
        }
        cout << "\nЧисло итераций: " << k - 1 << "\n"
             << endl;
    }
    else
    {
        cerr << "Условие сходимости не выполняется!\n"
             << endl;
    }
    return 0;
}

int main()
{
    int N = 3, i, j;

    double A[3][3] = {
        {3.1, -1.5, 1},
        {0.8, -3, 1.4},
        {-1, 1.2, 2.7},
    };
    double B[3] = {-1, 0, 2};

    double C[3][4];
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N + 1; j++)
        {
            if (j != N)
            {
                C[i][j] = A[i][j];
            }
            else
            {
                C[i][j] = B[i];
            }
        }
    }

    cout.precision(5);     // 5 digits after comma
    cout.setf(ios::fixed); // fixed digits format after comma
    double eps;
    cout << "Введите точность вычислений: ";
    cin >> eps;

    /*cout << "Введите размер квадратной матрицы: ";
    cin >> N;
    double A[10][10], B[10], C[10][11];
    cout << "Заполните матрицу А (N x N): " << endl
         << endl;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            cout << "A[" << i << "][" << j << "] = ";
            cin >> A[i][j];
            C[i][j] = A[i][j];
        }
    }*/

    cout << "\nМатрица A:" << endl;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            cout << A[i][j] << "  ";
        }
        cout << endl;
    }

    /*cout << "\nЗаполните столбец свободных членов: " << endl;
    for (i = 0; i < N; i++)
    {
        cout << "B[" << i << "] = ";
        cin >> B[i];
        C[i][N - 1] = B[i];
    }*/

    cout << "\nСтолбец свободных членов:" << endl;
    for (i = 0; i < N; i++)
    {
        cout << "X" << i + 1 << " = " << B[i] << endl;
    }

    // triangulation
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < i; j++)
        {
            double ratio = C[i][j] / C[i][i];
            for (int k = j; k < N + 1; k++)
            {
                C[i][k] -= ratio * C[j][k];
            }
        }
    }

    // partial pivotisation to make the equations diagonally dominant
    for (i = 0; i < N; i++)
    {
        for (int k = 0; k < N + 1; k++)
        {
            if (abs(C[i][i]) < abs(C[k][i])) // compare absolute values
            {
                for (j = 0; j <= N; j++)
                { // swap
                    double temp = C[i][j];
                    C[i][j] = C[k][j];
                    C[k][j] = temp;
                }
            }
        }
    }

    // приведение к виду для итераций
    for (int i = 0; i < N; i++)
    {
        double ratio = C[i][i];
        for (int j = 0; j < N + 1; j++)
        {
            C[i][j] /= ratio;
        }
    }

    // divide C into A & B
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N + 1; j++)
        {
            if (j != N)
            {
                A[i][j] = C[i][j];
            }
            else
            {
                B[i] = C[i][j];
            }
        }
    }

    cout << "\nМатрица А, приведённая к нормальному виду:" << endl;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            cout << A[i][j] << "  ";
        }
        cout << endl;
    }

    // matrix E - A
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            A[i][j] = -A[i][j];
            if (i == j)
            {
                A[i][j] = A[i][j] + 1;
            }
        }
    }

    cout << "\nМатрица (E - А):" << endl;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            cout << A[i][j] << "  ";
        }
        cout << endl;
    }

    iterat(A, B, N, eps);
    return 0;
}