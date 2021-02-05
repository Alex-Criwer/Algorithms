#include <iostream>
#include <cstring>
using namespace std;

char* reverse(char* str)
{
    int size = strlen(str);
    for (int i = 0; i < size / 2; ++i) {
        char temp = str[i];
        str[i] = str[size - 1 - i];
        str[size - 1 - i] = temp;
    }
    return str;
}

int to_binary(char* dec_number)
{
    char binary_number[5000]{ 0 };
    int j = 0;
    while (strlen(dec_number) != 0) {
        int k = 0;
        char divide[256]{ 0 };
        bool first = false;
        int z = 0;
        int new_size = strlen(dec_number);
        for (int i = 0; i < new_size; ++i) {
            int current_num = dec_number[i] - '0';
            int pred = (k * 10 + current_num) / 2;
            if (pred != 0 || first) {
                divide[z++] = (pred) + '0';
                first = true;
            }
            k = current_num % 2;
        }
        binary_number[j++] = k + '0';
        strcpy(dec_number, divide);
    }
    reverse(binary_number);
    int size2 = strlen(binary_number);
    for (int i = 0; i < size2; ++i) {
        cout << binary_number[i];
    }

    return 0;
}

int main()
{
    char str[256];
    cin.getline(str, 256);
    int i = 0;
    while (str[i] != '\0') {
        char number[256]{ 0 };
        if (isdigit(str[i])) {
            int j = 0;
            while (isdigit(str[i])) {
                number[j++] = str[i++];
            }
            to_binary(number);
        }
        if (!isdigit(str[i]) && str[i] != '\0') {
            cout << str[i];
            ++i;
        }
    }
    return 0;
}
