#include <stdio.h>
#include "driver/gpio.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "rtc_wdt.h"
// #include "esp_task_wdt.h"

static const char *TAG = "example";
const int BLINK_GPIO_1 = 15;
const int BLINK_GPIO_2 = 2;
const int BLINK_GPIO_3 = 4;

bool r_led_state=1;
bool s_led_state=1;
bool t_led_state=1;

static void delays(int s) {
    bool dummy_state=0;
    for (int i=0; i<s; i++) {
        ESP_LOGI(TAG, "1 sec mark");
        for (int j=0; j<20000000; j++){
            dummy_state = !dummy_state;
            // esp_task_wdt_reset();
        }
    }
}

static void blink_led(void)
{
    /* Set the GPIO level according to the state (LOW or HIGH)*/
    gpio_set_level(BLINK_GPIO_1, r_led_state);
    gpio_set_level(BLINK_GPIO_2, s_led_state);
    gpio_set_level(BLINK_GPIO_3, t_led_state);
    // esp_task_wdt_reset();
}

static void configure_led(void)
{
    ESP_LOGI(TAG, "Example configured to blink GPIO LED!");
    gpio_reset_pin(BLINK_GPIO_1);
    gpio_reset_pin(BLINK_GPIO_2);
    gpio_reset_pin(BLINK_GPIO_3);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO_1, GPIO_MODE_OUTPUT);
    gpio_set_direction(BLINK_GPIO_2, GPIO_MODE_OUTPUT);
    gpio_set_direction(BLINK_GPIO_3, GPIO_MODE_OUTPUT);
    // esp_task_wdt_reset();
}

void app_main(void)
{
    rtc_wdt_disable();
    /* Configure the peripheral according to the LED type */
    configure_led();

    int counter=0;
    while (1) {
        /* Toggle the LED state */
        delays(1);

        if (counter==100) counter=1;
        else counter++;

        r_led_state = !r_led_state;
        if ((counter % 2) == 0) s_led_state = !s_led_state;
        if ((counter % 3) == 0) t_led_state = !t_led_state;
        blink_led();
    }
}
