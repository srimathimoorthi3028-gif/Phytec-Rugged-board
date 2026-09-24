#include <stdio.h>
#include <mraa/gpio.h>
#include <unistd.h>

int main()
{
    mraa_gpio_context switch_pin;
    mraa_gpio_context led_pin;

    switch_pin = mraa_gpio_init(35);
    led_pin = mraa_gpio_init(61);

    mraa_gpio_dir(switch_pin, MRAA_GPIO_IN);
    mraa_gpio_dir(led_pin, MRAA_GPIO_OUT);

    int count = 0;
    int previous_switch = 1;
    int led_state = 1;

    // Initially LED OFF
    mraa_gpio_write(led_pin, 1);

    while(1)
    {
        int switch_state = mraa_gpio_read(switch_pin);

        // Detect a new press
        if(switch_state == 0 && previous_switch == 1)
        {
            count++;

            printf("Switch pressed %d time(s)\n", count);
            fflush(stdout);

            // Toggle LED according to press count
            for(int i = 0; i < count; i++)
            {
                if(led_state == 1)
                {
                    led_state = 0;
                }
                else
                {
                    led_state = 1;
                }

                mraa_gpio_write(led_pin, led_state);

                usleep(300000);
            }
        }

        previous_switch = switch_state;

        usleep(10000);
    }

    return 0;
}
