#include <bits/stdc++.h>
using namespace std;

vector<string> split(string str, char by)
{
    vector<string> ans;
    string curr;

    for (char c : str) {
        if (c == by) {
            ans.push_back(curr);
            curr = "";
        } else {
            curr += c;
        }
    }
    ans.push_back(curr);

    return ans;
}

string removeSpaces(string str)
{
    string ans;
    for (auto c : str) {
        if (c != ' ') {
            ans += c;
        }
    }
    return ans;
}

bitset<32> formattedStrToBitset(string str)
{
    bitset<32> bits;

    for (auto& term : split(removeSpaces(str), '+')) {
        if (term == "0") {
            continue;
        }
        if (term == "1") {
            bits[0] = !bits[0];
            continue;
        }
        if (term == "x") {
            bits[1] = !bits[1];
            continue;
        }
        int pos = stoi(term.substr(2));
        bits[pos] = !bits[pos];
    }

    return bits;
}

string bitsetToFormattedString(bitset<32> bits)
{
    string ans;
    for (int i = 31; i >= 0; --i) {
        if (bits[i]) {
            if (ans != "") {
                ans += " + ";
            }
            if (i == 0) {
                ans += "1";
            } else if (i == 1) {
                ans += "x";
            } else {
                ans += "x^" + to_string(i);
            }
        }
    }

    if (ans == "") {
        return "0";
    }

    return ans;
}

class Polynomial {
public:
    bitset<32> bits;
    Polynomial()
        : bits {}
    {
    }
    Polynomial(bitset<32> _bits)
        : bits { _bits }
    {
    }
    Polynomial(string str)
        : bits { formattedStrToBitset(str) }
    {
    }

    Polynomial operator+(Polynomial rhs)
    {
        return Polynomial(bits ^ rhs.bits);
    }

    Polynomial operator-(Polynomial rhs)
    {
        return Polynomial(bits ^ rhs.bits);
    }

    Polynomial operator*(Polynomial rhs)
    {
        Polynomial ans;
        for (int i = 0; i < 32; ++i) {
            for (int j = 0; j < 32; ++j) {
                if (i + j >= 32)
                    continue;

                if (bits[i] && rhs.bits[j]) {
                    ans.bits[i + j] = !ans.bits[i + j];
                }
            }
        }
        return ans;
    }

    Polynomial operator/(Polynomial rhs)
    {
        return this->divide(rhs).first;
    }

    Polynomial operator%(Polynomial rhs)
    {
        return this->divide(rhs).second;
    }

    int righmostSetbit()
    {
        for (int i = 31; i >= 0; --i) {
            if (bits[i]) {
                return i;
            }
        }
        return -1;
    }

    pair<Polynomial, Polynomial> divide(Polynomial divisor)
    {
        Polynomial quotient, remainder(bits);
        int divisorOrder = divisor.righmostSetbit();

        for (int i = 31 - divisorOrder; i >= 0; --i) {
            if (remainder.bits[i + divisorOrder]) {
                quotient.bits[i] = 1;
                remainder.bits ^= (divisor.bits << i);
            }
        }

        return { quotient, remainder };
    }

    Polynomial inverse(Polynomial mod)
    {
        Polynomial r1 = mod, r2 = *this;
        Polynomial t1 { "0" }, t2 { "1" };

        while (r2.bits.any()) {
            Polynomial q = r1 / r2;
            Polynomial r = r1 - q * r2;
            r1 = r2, r2 = r;

            Polynomial t = t1 - q * t2;
            t1 = t2, t2 = t;
        }

        return t1;
    }

    string getFormatted()
    {
        return bitsetToFormattedString(bits);
    }
};

int main()
{
    string polStr, modStr;
    cout << "Enter Polynomial: ";
    getline(cin, polStr);
    cout << "Enter Mod: ";
    getline(cin, modStr);

    Polynomial pol(polStr), mod(modStr);
    Polynomial inv = pol.inverse(mod);

    cout << "Inverse of (" << pol.getFormatted() << ") modulo (" << mod.getFormatted() << ") is : (" << inv.getFormatted() << ")" << endl;

    return 0;
}