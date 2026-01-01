#include <stdio.h>
#include "pico/stdlib.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "hardware/i2c.h"
#include "lib/pico-ssd1306/ssd1306.h"

#ifdef __cplusplus
}
#endif

#define I2C_PORT i2c0
#define SDA_PIN 4
#define SCL_PIN 5

int main() {
    stdio_init_all();
    
    // 1. Wait for hardware to stabilize
    sleep_ms(250); 
    
    // 2. Initialize I2C
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    // 3. Initialize OLED
    ssd1306_t disp;
    disp.external_vcc = false;
    
    // If ssd1306_init fails, it usually returns false
    if (!ssd1306_init(&disp, 128, 64, 0x3C, I2C_PORT)) {
        printf("OLED Init Failed!\n");
    }

    // 4. Force Clear and Update
    ssd1306_clear(&disp);
    ssd1306_show(&disp);
    sleep_ms(100);

    while (true) {
        printf("Titan Spine: Running at 0x3C\n");

        ssd1306_clear(&disp);
        ssd1306_draw_string(&disp, 20, 10, 2, "TITAN");
        ssd1306_draw_string(&disp, 25, 35, 1, "S2T ROVER");
        ssd1306_show(&disp);

        static bool led_state = false;
        led_state = !led_state;
        gpio_put(PICO_DEFAULT_LED_PIN, led_state);

        sleep_ms(1000);
    }
    return 0;
}