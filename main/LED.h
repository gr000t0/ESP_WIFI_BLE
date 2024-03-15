#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"


class LED{
private:
    gpio_num_t red;
    gpio_num_t green;
    gpio_num_t blue;
    void init(gpio_num_t pin);
public:
    LED();
    void blink(const char* colour, int times);
    void on(const char* colour);
    void off(const char* colour);
    
};