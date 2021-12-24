#include<bits/stdc++.h>
using namespace std;

string encrypt(string text, int key) {
    string result = "";
    for(int i = 0; i < text.length(); ++i) {
        if(isupper(text[i])) {
            result += char(int((text[i] - 65) * key) % 26 + 65);
        } else {
            result += char(int((text[i] - 97) * key) % 26 + 97);
        }
    }
    return result;
}

int main() {
    string text;
    int key;
    cout << "\nEnter Plain text:\n";
    cin >> text;
    cout << "\nEnter key:\n";
    cin >> key;
    cout << "\nPlain text: " << text;
    cout << "\nKey: " << key;
    cout << "\nCipher text: " << encrypt(text, key);
    return 0;
}
