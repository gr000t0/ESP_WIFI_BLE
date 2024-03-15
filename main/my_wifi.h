#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_err.h"

enum mode {
    AP,
    STA
};


class My_wifi{

private:
wifi_init_config_t init_config;
wifi_config_t config;
esp_event_handler_t eventHandlerAP;
esp_event_handler_t eventHandlerSTA;
mode md;
char* ssid = "BORA-DEV";
char* password= "SCZd5Mryd9vGNcKm";

public: 
esp_err_t init();
void setEventHandlerAP(esp_event_handler_t eventHandler);
void setEventHandlerSTA(esp_event_handler_t eventHandler);
esp_err_t start();
void setModus(mode md);
void setSsidAndPassword(char* ssid, char* password);
void wifi_scan();
};

