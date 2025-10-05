#include <stdio.h>
#include <string.h>

int main() {
    char buffer[100];
    int age = 25;
    double height = 1.75;
    const char *name = "Alice";

    // Форматируем строку с использованием sprintf
    int n = sprintf(buffer, "Name: %s, Age: %d, Height: %.2f", name, age, height);

    // Выводим отформатированную строку
    printf("Formatted string: %s\n", buffer);
    printf("Number of characters written: %d\n", n);

    return 0;
}