#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
// #include "hardware/gpio.h"
#include "hardware/adc.h"

int main() {
   stdio_init_all();
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    const uint PWM_PIN = 20;
    gpio_set_function(PWM_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(PWM_PIN);
    pwm_set_wrap(slice_num, 1249);
    pwm_set_chan_level(slice_num, PWM_CHAN_A, 0);
    pwm_set_enabled(slice_num, true);

    adc_init();
    adc_gpio_init(26);

    while (true) {
      const float conversion_factor = 3.3f / (1 << 12);
        uint16_t result = adc_read();
        
        printf("Raw value: 0x%03x, voltage: %f V\n", result, result * conversion_factor);

        pwm_set_chan_level(slice_num, PWM_CHAN_A, result);
        sleep_ms(1);
      // for(uint8_t i = 0; i < 256; i++){

      //   sleep_ms(10);
      // }
        

        // gpio_put(LED_PIN, 1);
        // sleep_ms(250);
        // gpio_put(LED_PIN, 0);
        // sleep_ms(250);
    }

}
