#include <stdio.h>
#define RED   "\033[1;31m"
#define GREEN "\033[1;32m"
#define RESET "\033[0m"

int main() {
    int a, b;
    printf(GREEN "Enter two numbers: " RESET);
    scanf("%d %d", &a, &b);
    printf(RED "Sum = %d\n" RESET, a + b);
    return 0;
}
