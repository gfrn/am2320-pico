#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "am2320.h"

#define I2C_PORT i2c0
#define I2C_SDA 4
#define I2C_SCL 5

int main() {
    stdio_init_all();

    i2c_init(I2C_PORT, 100 * 1000);

    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    float humidity, temperature;

    read_sensors(&temperature, &humidity);
    printf("%.2fC, %.2f$\n", temperature, humidity);

    return 0;
}
