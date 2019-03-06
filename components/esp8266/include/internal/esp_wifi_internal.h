// Copyright 2018-2019 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef _ESP_WIFI_INTERNAL_H
#define _ESP_WIFI_INTERNAL_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    WIFI_RX_PBUF_IRAM,   /** save rx buffer to iram and upload to tcpip*/
    WIFI_RX_PBUF_DRAM,   /** save rx buffer to dram and upload to tcpip */
} wifi_rx_pbuf_mem_type_t;

/**
  * @brief     Set WIFI received TCP/IP data cache ram type
  *
  * @param     type if use dram
  */
void esp_wifi_set_rx_pbuf_mem_type(wifi_rx_pbuf_mem_type_t type);

/**
  * @brief     get WIFI received TCP/IP data cache ram type
  *
  * @return    true if use dram or false
  */
wifi_rx_pbuf_mem_type_t esp_wifi_get_rx_pbuf_mem_type(void);

int8_t esp_wifi_get_ap_rssi(void);

/**
  * @brief The RX callback function when receive probe request packet. 
  *        When probe request packet is received, the callback function will be called.
  *
  * @param frame  Data of received probe request.
  * @param len  length of received probe request.
  * @param rssi  rssi of received probe request.
  */
typedef void (*wifi_sta_rx_probe_req_t)(const uint8_t *frame, int len, int rssi);

/**
  * @brief Register the RX callback function when receive probe request.
  *
  * When probe request packet is received, the registered callback function will be called.
  *
  * @param cb  callback
  *
  * @return
  *    - ESP_OK: succeed
  *    - ESP_ERR_WIFI_NOT_INIT: WiFi is not initialized by esp_wifi_init
  */
esp_err_t esp_wifi_set_sta_rx_probe_req(wifi_sta_rx_probe_req_t cb);

/**
  * @brief  free the rx buffer which allocated by wifi driver
  *
  * @param  void* buffer: rx buffer pointer
  */
void esp_wifi_internal_free_rx_buffer(void* buffer);

/**
  * @brief  transmit the buffer via wifi driver
  *
  * @param  wifi_interface_t wifi_if : wifi interface id
  * @param  void *buffer : the buffer to be tansmit
  * @param  uint16_t len : the length of buffer
  *
  * @return
  *    - ERR_OK  : Successfully transmit the buffer to wifi driver
  *    - ERR_MEM : Out of memory
  *    - ERR_IF : WiFi driver error
  *    - ERR_ARG : Invalid argument
  */
int esp_wifi_internal_tx(wifi_interface_t wifi_if, void *buffer, uint16_t len);

/**
  * @brief     The WiFi RX callback function
  *
  *            Each time the WiFi need to forward the packets to high layer, the callback function will be called
  */
typedef esp_err_t (*wifi_rxcb_t)(void *buffer, uint16_t len, void *eb);

/**
  * @brief     Set the WiFi RX callback
  *
  * @attention 1. Currently we support only one RX callback for each interface
  *
  * @param     wifi_interface_t ifx : interface
  * @param     wifi_rxcb_t fn : WiFi RX callback
  *
  * @return
  *     - ESP_OK : succeed
  *     - others : fail
  */
esp_err_t esp_wifi_internal_reg_rxcb(wifi_interface_t ifx, wifi_rxcb_t fn);

#ifdef __cplusplus
}
#endif

#endif /* _ESP_WIFI_INTERNAL_H */
