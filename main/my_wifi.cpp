#include "my_wifi.h"
#include "LED.h"
#include "cstring"
#include "esp_log.h"
#include <string.h>
#include <vector>
#include <string>
#include <cstdint>
#include <algorithm>
/*
void My_wifi::setSsidAndPassword(char* ssid, char* password){
    delete[] this->ssid;
    delete[] this->password;
    this->ssid = new char[strlen(ssid) + 1];
    this->password = new char[strlen(password) + 1];
    strcpy(this->ssid, ssid);
    strcpy(this->password, password); }

*/

void My_wifi::setEventHandlerAP(esp_event_handler_t eventHandler){
    this->eventHandlerAP = eventHandler;
}


void My_wifi::setEventHandlerSTA(esp_event_handler_t eventHandler){
    this->eventHandlerSTA = eventHandler;
}


void My_wifi::setModus(mode md){
    this->md = md;
}

esp_err_t My_wifi::init()
{

// initialize NVS and network-interface
ESP_ERROR_CHECK(nvs_flash_init());
ESP_ERROR_CHECK(esp_netif_init());

// create config for wifi 
if(this->md == AP) {
strcpy(reinterpret_cast<char*>(this->config.ap.ssid), this->ssid );
this->config.ap.ssid_len = strlen(reinterpret_cast<const char*>(this->config.ap.ssid));
strcpy(reinterpret_cast<char*>(this->config.ap.password), this->password);
this->config.ap.max_connection = 4;
this->config.ap.authmode = WIFI_AUTH_WPA_WPA2_PSK;
this->config.ap.channel = 1;
}

else{
 /*  std::string ssid_s = "BORA-DEV";
    std::string password_s = "SCZd5Mryd9vGNcKm";

    uint8_t ssid_u[32];
    std::copy(ssid_s.begin(), ssid_s.end(), std::begin(ssid_u));
    uint8_t password_u[64];
    std::copy(password_s.begin(), password_s.end(), std::begin(password_u));  */

   strcpy(reinterpret_cast<char*>(this->config.sta.ssid), "mywifi");
   strcpy(reinterpret_cast<char*>(this->config.sta.password), "internet333");
   
   
   
    this->config.sta.scan_method = WIFI_ALL_CHANNEL_SCAN;


}



wifi_init_config_t i_cfg = WIFI_INIT_CONFIG_DEFAULT();
this->init_config = i_cfg;


//create and assign config to AP wifi service
if(this->md == AP) esp_netif_create_default_wifi_ap();
if(this->md == STA) esp_netif_create_default_wifi_sta();
ESP_ERROR_CHECK(esp_wifi_init(&(this->init_config)));
ESP_ERROR_CHECK(esp_wifi_set_mode(this->md == AP ? WIFI_MODE_AP : WIFI_MODE_STA));
ESP_ERROR_CHECK(esp_wifi_set_config(static_cast<wifi_interface_t>(this->md == AP ? ESP_IF_WIFI_AP : ESP_IF_WIFI_STA), &(this->config)));



// register event handler
ESP_ERROR_CHECK(esp_event_loop_create_default());

if(this->md == AP)ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        this->eventHandlerAP,
                                                        NULL,
                                                        NULL));

if(this->md == STA)ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        this->eventHandlerSTA,
                                                        NULL,
                                                        NULL));                         




return ESP_OK;


}

void My_wifi::wifi_scan(){
    esp_wifi_start();
    wifi_scan_config_t scan_config = {
        .ssid = NULL,
        .bssid = NULL,
        .channel = 0,
        .show_hidden = true
    };
    ESP_LOGI("wifi_scan", "Starte Scan");
    ESP_ERROR_CHECK(esp_wifi_scan_start(&scan_config, true));

    uint16_t ap_num = 20;  // Max. Anzahl der APs, die zurückgegeben werden sollen
    wifi_ap_record_t ap_records[20];  // Array zum Speichern der AP-Daten

    // Hole die Scan-Ergebnisse
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&ap_num, ap_records));

    // Gebe die Ergebnisse aus
    for (int i = 0; i < ap_num; i++) {
        ESP_LOGI("wifi_scan", "SSID: %s, RSSI: %d", ap_records[i].ssid, ap_records[i].rssi);
    }
}

esp_err_t My_wifi::start(){

    
    esp_err_t ret = esp_wifi_start();
    if(this->md == STA) ret = esp_wifi_connect();
    ESP_LOGI("wifi", "connecting to %s with passwd: %s", this->ssid, this->password);
    ESP_LOGI("wifi", "connecting to %s with passwd: %s", this->config.sta.ssid, this->config.sta.password);
   
    return ret;
}