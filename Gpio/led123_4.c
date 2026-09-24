#include <stdio.h>
#include <mraa/gpio.h>
#include <unistd.h>

int main()
{
    mraa_gpio_context switch_pin;
    mraa_gpio_context led1, led2, led3;

    switch_pin = mraa_gpio_init(35);

    led1 = mraa_gpio_init(61);
    led2 = mraa_gpio_init(62);
    led3 = mraa_gpio_init(63);

    mraa_gpio_dir(switch_pin, MRAA_GPIO_IN);

    mraa_gpio_dir(led1, MRAA_GPIO_OUT);
    mraa_gpio_dir(led2, MRAA_GPIO_OUT);
    mraa_gpio_dir(led3, MRAA_GPIO_OUT);

    
    mraa_gpio_write(led1, 1);
    mraa_gpio_write(led2, 1);
    mraa_gpio_write(led3, 1);

    int count = 0;
    int previous_switch = 1;

    while(1)
    {
        int switch_state = mraa_gpio_read(switch_pin);

        
        if(switch_state == 0 && previous_switch == 1)
        {
            count++;

            printf("Switch pressed %d time(s)\n", count);

            
            mraa_gpio_write(led1, 1);
            mraa_gpio_write(led2, 1);
            mraa_gpio_write(led3, 1);

            if(count % 3 == 1)
            {
                mraa_gpio_write(led1, 0);
                printf("LED 1 ON\n");
            }
            else if(count % 3 == 2)
            {
                mraa_gpio_write(led2, 0);
                printf("LED 2 ON\n");
            }
            else
            {
                mraa_gpio_write(led3, 0);
                printf("LED 3 ON\n");
            }

            fflush(stdout);
        }

        
        if(switch_state == 1)
        {
            mraa_gpio_write(led1, 1);
            mraa_gpio_write(led2, 1);
            mraa_gpio_write(led3, 1);
        }

        previous_switch = switch_state;

        usleep(10000);
    }

    return 0;
}
