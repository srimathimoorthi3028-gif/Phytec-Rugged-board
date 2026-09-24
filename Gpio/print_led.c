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

    int previous_state = -1;

    while(1)
    {
        int switch_state = mraa_gpio_read(switch_pin);

        if(switch_state == 1)
        {
            mraa_gpio_write(led_pin, 1);

            if(previous_state != 1)
            {
                printf("LED is ON\n");
                fflush(stdout);
                previous_state = 1;
            }
        }
        else
        {
            mraa_gpio_write(led_pin, 0);

            if(previous_state != 0)
            {
                printf("LED is OFF\n");
                fflush(stdout);
                previous_state = 0;
            }
       }

        usleep(10000);
    }

    return 0;
}
