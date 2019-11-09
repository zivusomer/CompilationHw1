#include <string>
#include <iostream>

using namespace std;
int main() {
    char a = '3', b = '0';
    a -= 48;
    b -= 48;
    int sum = (int)a*16 + (int)b;
    printf("%c", sum);

    return 0;
}
