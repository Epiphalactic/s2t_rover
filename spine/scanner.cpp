#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define I2C_PORT i2c0
#define SDA_PIN 4
#define SCL_PIN 5

int main() {
    stdio_init_all();
    sleep_ms(2000); 
    
    printf("\n--- I2C BUS SCANNER (GP4/GP5) ---\n");

    i2c_init(I2C_PORT, 100 * 1000);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    while (true) {
        int found = 0;
        printf("Scanning...\n");
        for (int addr = 0; addr < (1 << 7); ++addr) {
            uint8_t rxdata;
            if ((addr & 0x78) == 0 || (addr & 0x78) == 0x78) continue;
            
            int ret = i2c_read_blocking(I2C_PORT, addr, &rxdata, 1, false);
            if (ret >= 0) {
                printf("Device found at address: 0x%02X\n", addr);
                found++;
            }
        }
        if (found == 0) printf("No devices found...\n");
        sleep_ms(2000);
    }
}