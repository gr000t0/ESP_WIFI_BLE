
#include "my_wifi.h"
#include "LED.h"
// Enabling C++ compile

 void eventHandlerAP(void* args, esp_event_base_t eventBase, int32_t eventID, void* event_data)
{

    LED led;


if(eventBase == WIFI_EVENT && eventID == WIFI_EVENT_AP_STACONNECTED){
    
     led.blink("green", 5);

    
}

else if (eventBase == WIFI_EVENT && eventID == WIFI_EVENT_AP_STADISCONNECTED){
    ESP_LOGI("wifi", "station disconnected");
    led.blink("red", 5);
    
}


}

void eventHandlerSTA(void* args, esp_event_base_t eventBase, int32_t eventID, void* event_data)
{


    LED led;
    if(eventBase == WIFI_EVENT && eventID == WIFI_EVENT_STA_CONNECTED){

    ESP_LOGI("wifi", "station connected");
        led.on("green");
    }
    else if(eventBase == WIFI_EVENT && eventID == WIFI_EVENT_STA_DISCONNECTED){
        esp_wifi_connect();
        ESP_LOGI("wifi", "try to reconnect...");

    wifi_event_sta_disconnected_t* disconnected = (wifi_event_sta_disconnected_t*) event_data;
        switch (disconnected->reason) {
            case WIFI_REASON_NO_AP_FOUND:
                ESP_LOGV("wifi", "Verbindung fehlgeschlagen: AP nicht gefunden");
                break;
            case WIFI_REASON_AUTH_FAIL:
                ESP_LOGI("wifi", "Verbindung fehlgeschlagen: Authentifizierung fehlgeschlagen");
                break;
            case WIFI_REASON_HANDSHAKE_TIMEOUT:
                ESP_LOGI("wifi", "Verbindung fehlgeschlagen: Handshake-Timeout");
                break;
            default:
                ESP_LOGI("wifi", "Verbindung fehlgeschlagen: Grund %d", disconnected->reason);
                break;
        }
        led.blink("red", 5);
    }

}

extern "C" void app_main(void)
{

    esp_log_level_set("wifi", ESP_LOG_VERBOSE);

   My_wifi myWifi;
   myWifi.setEventHandlerAP(eventHandlerAP);
    myWifi.setEventHandlerSTA(eventHandlerSTA);
    myWifi.setModus(STA);
    
   myWifi.init();
   myWifi.wifi_scan();
   vTaskDelay(5000 / portTICK_PERIOD_MS);
   myWifi.start();


}
