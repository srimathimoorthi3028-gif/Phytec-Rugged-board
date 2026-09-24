#include <stdio.h>
#include <mraa/gpio.h>
#include <unistd.h>

int main()
{
    mraa_gpio_context switch_pin;
    mraa_gpio_context led1;
    mraa_gpio_context led2;

    switch_pin = mraa_gpio_init(35);

    led1 = mraa_gpio_init(61);
    led2 = mraa_gpio_init(62);

    mraa_gpio_dir(switch_pin, MRAA_GPIO_IN);

    mraa_gpio_dir(led1, MRAA_GPIO_OUT);
    mraa_gpio_dir(led2, MRAA_GPIO_OUT);

  
    mraa_gpio_write(led1, 1);
    mraa_gpio_write(led2, 1);

    int count = 0;
    int previous_switch = 1;

    int led1_state = 1;
    int led2_state = 1;

    while(1)
    {
        int switch_state = mraa_gpio_read(switch_pin);

        
        if(switch_state == 0 && previous_switch == 1)
        {
            count++;

            printf("Switch pressed %d time(s)\n", count);
            fflush(stdout);

           
            for(int i = 0; i < count; i++)
            {
                if(led1_state == 1)
                {
                    led1_state = 0;
                }
                else
                {
                    led1_state = 1;
                }

                mraa_gpio_write(led1, led1_state);

                usleep(300000);
            }

            
            for(int i = 0; i < count * 3; i++)
            {
                if(led2_state == 1)
                {
                    led2_state = 0;
                }
                else
                {
                    led2_state = 1;
                }

                mraa_gpio_write(led2, led2_state);

                usleep(300000);
            }
        }

        previous_switch = switch_state;

        usleep(10000);
    }

    return 0;
}
