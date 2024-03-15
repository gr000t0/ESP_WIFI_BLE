idf_component_register(SRCS "my_wifi.cpp" "main.cpp" "LED.cpp"
                    INCLUDE_DIRS "."
                    REQUIRES freertos esp_common esp_event esp_wifi nvs_flash esp_netif) 

