#include <stdio.h>
#include <stdlib.h>
void add(double a, double b) {
    printf("%.2f + %.2f = %.2f\n", a, b, a + b);
}
void subtract(double a, double b) {
    printf("%.2f - %.2f = %.2f\n", a, b, a - b);
}
void multiply(double a, double b) {
    printf("%.2f * %.2f = %.2f\n", a, b, a * b);
}
void divide(double a, double b) {
    if (b == 0) {
        printf("Ошибка: деление на ноль!\n");
        return;
    }
    printf("%.2f / %.2f = %.2f\n", a, b, a / b);
}
int main() {
    double num1, num2;
    char operator;
    printf("Введите первое число: ");
    scanf("%lf", &num1);
    printf("Введите оператор (+, -, *, /): ");
    scanf(" %c", &operator);
    printf("Введите второе число: ");
    scanf("%lf", &num2);
    switch (operator) {
        case '+':
            add(num1, num2);
            break;
        case '-':
            subtract(num1, num2);
            break;
        case '*':
            multiply(num1, num2);
            break;
        case '/':
            divide(num1, num2);
            break;
        default:
            printf("Неверный оператор.\n");
    }
    return 0;
} 
