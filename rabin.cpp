#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cstring>
using namespace std;
int p = 167, q = 151;
int n = p * q;
int mod(int k, int b, int m)
{
    int i = 0;
    int a = 1;
    vector<int> t;
    while (k > 0)
    {
        t.push_back(k % 2);
        k = (k - t[i]) / 2;
        i++;
    }
    for (int j = 0; j < i; j++)
    {
        if (t[j] == 1)
        {
            a = (a * b) % m;
            b = (b * b) % m;
        }
        else
        {
            b = (b * b) % m;
        }
    }
    return a;
}
void encode(string s)
{
    vector<int> l;
    for (int i = 0; i < strlen(s.c_str()); i++)
    {
        l.push_back((int)s[i]);
    }
    copy(l.begin(), l.end(), ostream_iterator<int>(cout, ""));
}
int modulo(int a, int b)
{
    return a >= 0 ? a % b : (b - abs(a % b)) % b;
}
void decoding(vector<int> s)
{
    vector<char> l;
    for (int i = 0; i < s.size(); i++)
    {
        l.push_back(char(s[i]));
    }
    copy(l.begin(), l.end(), ostream_iterator<char>(cout, ""));
}
int encryption(int m, int n)
{
    int c = (m * m) % n;
    return c;
}
vector<int> eea(int a, int b)
{
    if (b > a)
    {
        int temp = a;
        a = b;
        b = temp;
    }
    int x = 0;
    int y = 1;
    int lastx = 1;
    int lasty = 0;
    while (b != 0)
    {
        int q = a / b;
        int temp1 = a % b;
        a = b;
        b = temp1;
        int temp2 = x;
        x = lastx - q * x;
        lastx = temp2;
        int temp3 = y;
        y = lasty - q * y;
        lasty = temp3;
    }
    vector<int> arr(3);
    arr[0] = lastx;
    arr[1] = lasty;
    arr[2] = 1;
    return arr;
}
int decryption(int c, int p, int q)
{
    int mp = mod((p + 1) / 4, c, p);
    int mq = mod((q + 1) / 4, c, q);
    vector<int> arr = eea(p, q);
    int pp = arr[0] * p * mq;
    int qq = arr[1] * q * mp;
    double r = modulo((pp + qq), n);
    if (r < 128)
        return r;
    int negative_r = n - r;
    if (negative_r < 128)
        return negative_r;
    int s = modulo((pp - qq), n);
    if (s < 128)
        return s;
    int negative_s = n - s;
    if (negative_s < 128)
        return negative_s;
    return 0;
}
int main()
{
    cout << "\n Implementation of Rabin Cryptosystem \n\n";
    cout << " Public Key is: " << n;
    string msg = "abcdefgh";
    cout << "\n Message: " << msg << endl;
    int len = strlen(msg.c_str());
    vector<int> li;
    for (int i = 0; i <= len; i++)
    {
        li.push_back(encryption(msg[i], n));
    }
    cout << " Cipher Text: ";
    copy(li.begin(), li.end(), ostream_iterator<int>(cout, ""));
    vector<int> des;
    for (int i = 0; i < len; i++)
    {
        des.push_back(decryption(li[i], p, q));
    }
    cout << "\n Plain Text: ";
    decoding(des);
    return 0;
}
