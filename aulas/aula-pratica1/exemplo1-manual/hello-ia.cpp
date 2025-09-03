#include <stdio.h>

int main() {
    printf("Celsius\tFahrenheit\tKelvin\n");
    for (int celsius = 0; celsius <= 100; celsius += 10) {
        double fahrenheit = (celsius * 9.0 / 5.0) + 32.0;
        double kelvin = celsius + 273.15;
        printf("%d\t%.2f\t\t%.2f\n", celsius, fahrenheit, kelvin);
    }
    return 0;
}
