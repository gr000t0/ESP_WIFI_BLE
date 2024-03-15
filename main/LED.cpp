#include <cstring>
#include "LED.h"

LED::LED(){
    this->red = GPIO_NUM_0;
    this->green = GPIO_NUM_2;
    this->blue = GPIO_NUM_4;

    init(this->red);
    init(this->green);
    init(this->blue);

}

void LED::init(gpio_num_t pin){
    gpio_pad_select_gpio(pin);
    gpio_set_direction(pin, GPIO_MODE_OUTPUT);
    gpio_set_level(pin, 0);
}


void LED::blink(const char* colour, int times){
    gpio_num_t pin = GPIO_NUM_NC;
       if (strcmp(colour, "red") == 0) {
        pin = this->red;
    } else if (strcmp(colour, "green") == 0) {
        pin = this->green;
    } else if (strcmp(colour, "blue") == 0) {
        pin = this->blue;
    }


    for(int i = 0; i < times; i++){
        gpio_set_level(pin, 1);
        vTaskDelay(500 / portTICK_PERIOD_MS);
        gpio_set_level(pin, 0);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }

}
    
    void LED::on(const char* colour){
        gpio_num_t pin = GPIO_NUM_NC;
        if (strcmp(colour, "red") == 0) {
            pin = this->red;
        } else if (strcmp(colour, "green") == 0) {
            pin = this->green;
        } else if (strcmp(colour, "blue") == 0) {
            pin = this->blue;
        }

        gpio_set_level(pin, 1);

}

void LED::off(const char* colour){
    gpio_num_t pin = GPIO_NUM_NC;
    if (strcmp(colour, "red") == 0) {
        pin = this->red;
    } else if (strcmp(colour, "green") == 0) {
        pin = this->green;
    } else if (strcmp(colour, "blue") == 0) {
        pin = this->blue;
    }

    gpio_set_level(pin, 0);
}
