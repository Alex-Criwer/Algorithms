#include <iostream>
#include <cstring>

using namespace std;

bool substr(char* str1, char* str2, int index, int size1, int size2)
{
    bool flag = true;
    for (int i = index; i < index + size1; i++) {
        if (str2[i] != str1[i - index]) {
            flag = false;
        }
    }
    return flag;
}

int main()
{
    char* str1 = new char[10001];
    char* str2 = new char[10001];
    cin.getline(str1, 10001);
    cin.getline(str2, 10001);
    int size1 = strlen(str1);
    int size2 = strlen(str2);
    bool check = false;
    for (int i = 0; i < size2; i++) {
        if (str2[i] == str1[0]) {
            check = substr(str1, str2, i, size1, size2);
            if (check) {
                break;
            }
        }
    }
    if (check) {
        cout << "yes";
    }
    else {
        cout << "no";
    }
    delete[] str1;
    delete[] str2;
    return 0;
}