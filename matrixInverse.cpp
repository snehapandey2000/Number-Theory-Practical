#include <bits/stdc++.h>
using namespace std;
#define N 4

int findInverseModulo(int b, int n)
{
    int t1 = 0;
    int t2 = 1;

    int r1 = n;
    int r2 = b;

    while (r2 > 0)
    {
        int q = r1 / r2;

        int r = r1 - q * r2;
        int t = t1 - q * t2;

        r1 = r2;
        r2 = r;

        t1 = t2;
        t2 = t;
    }

    if (r1 == 1)
    {
        t1 = t1 < 0 ? t1 + n : t1;
        return t1;
    }

    return -1;
}
void getCofactor(int A[N][N], int temp[N][N], int p, int q, int n)
{
    int i = 0, j = 0;

    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (row != p && col != q)
            {
                temp[i][j++] = A[row][col];

                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

int determinant(int A[N][N], int n)
{
    int D = 0;
    if (n == 1)
        return A[0][0];

    int temp[N][N];

    int sign = 1;

    for (int f = 0; f < n; f++)
    {
        getCofactor(A, temp, 0, f, n);
        D += sign * A[0][f] * determinant(temp, n - 1);

        sign = -sign;
    }

    return D;
}

void adjoint(int A[N][N], int adj[N][N])
{
    if (N == 1)
    {
        adj[0][0] = 1;
        return;
    }

    int sign = 1, temp[N][N];

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            getCofactor(A, temp, i, j, N);

            sign = ((i + j) % 2 == 0) ? 1 : -1;

            adj[j][i] = (sign) * (determinant(temp, N - 1));
        }
    }
}

bool inverseMatrix(int A[N][N], int inverse[N][N], int r)
{
    int det = determinant(A, N);
    if (det == 0)
        return false;
    if (__gcd(det, r) != 1)
        return false;

    int detInverse = findInverseModulo(det, r);

    int adj[N][N];
    adjoint(A, adj);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            inverse[i][j] = adj[i][j] * detInverse;
            if (inverse[i][j] < 0)
            {
                int q = abs(inverse[i][j]) / r;
                inverse[i][j] = inverse[i][j] + (q + 1) * r;
            }
            inverse[i][j] %= r;
        }

    return true;
}

void display(int A[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            cout << A[i][j] << " ";
        cout << endl;
    }
}

// Driver program
int main()
{
    int A[N][N] = {{5, -2, 2, 7},
                   {1, 0, 0, 3},
                   {-3, 1, 5, 0},
                   {3, -1, -9, 4}};

    int adj[N][N];
    int inv[N][N];

    cout << "Enter modulus n: ";
    int r;
    cin >> r;

    cout << "Input matrix is :\n";
    display(A);

    cout << "\nThe Inverse is :\n";
    if (inverseMatrix(A, inv, r))
        display(inv);

    return 0;
}
