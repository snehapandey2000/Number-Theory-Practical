//time- O(nlogn)
//space- O(1)
// x % num[0] = rem[0]
#include <bits/stdc++.h>
using namespace std;
int inverse(int a, int m)
{
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1)
        return 0;
    while (a > 1)
    {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0)
        x1 += m0;

    return x1;
}
int chineseRemainderthm(vector<int> &num, vector<int> &rem, int k)
{
    int prod = 1;
    for (int i = 0; i < k; i++)
        prod *= num[i];

    int result = 0;
    for (int i = 0; i < k; i++)
    {
        int pp = prod / num[i];
        result += rem[i] * inverse(pp, num[i]) * pp;
    }
    return result % prod;
}
int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
bool checkprime(vector<int> &num)
{
    for (int i = 0; i < num.size(); i++)
    {
        for (int j = i + 1; j < num.size(); j++)
        {
            int x = gcd(num[i], num[j]);
            if (x != 1)
            {
                return false;
            }
        }
    }
    return true;
}
int main()
{
    int k;
    cout << "-----------------Sneha Pandey 2019UIT3033------------------------------------\n";
    cout << "Enter the number of equations\n";
    cin >> k;
    vector<int> num(k);
    vector<int> rem(k);
    cout << "Enter the values of modulos and remainder for the " << k << " equations to be solved:\n";
    for (int i = 0; i < k; i++)
    {
        cin >> num[i] >> rem[i];
    }
    if (!checkprime(num))
    {
        cout << "No solution exists as moduli are not relatively primes\n";
    }
    else
    {
        cout << "Your answer is " << chineseRemainderthm(num, rem, k);
    }
    return 0;
}

/**
3
3 2
5 3
7 2
23
**/