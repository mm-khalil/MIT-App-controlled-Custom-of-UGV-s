#include <esp_now.h>
#include <WiFi.h>

HardwareSerial Receiver(2);
char received_data;


//------------------------------code to send data to FOLLOWERS-------------------------------//
#include <esp_now.h>
// REPLACE WITH YOUR ESP RECEIVER'S MAC ADDRESS
uint8_t broadcastAddress1[] = {0xFC, 0xF5, 0xC4, 0x27, 0xCD, 0x30};//F2 MAC address

typedef struct test_struct {
  char x;
} test_struct;

test_struct test;

 /*callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  char macStr[18];
  Serial.print("Packet to: ");
  // Copies the sender mac address to a string
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print(macStr);
  Serial.print(" send status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}*/

void setup() {
  //Serial.begin(Baud Rate, Data Protocol, Txd pin, Rxd pin);
  Serial.begin(115200);                                                   // Define and start serial monitor
  Receiver.begin(115200, SERIAL_8N1, 22, 23); // Define and start Receiver serial port


//------follower code
  WiFi.mode(WIFI_STA);
 
  if (esp_now_init() != ESP_OK) { 
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
//  esp_now_register_send_cb(OnDataSent);
   
  // register peer
  esp_now_peer_info_t peerInfo;
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // register first peer  
  memcpy(peerInfo.peer_addr, broadcastAddress1, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }


}
void loop() {
 while (Receiver.available()) {                         // Wait for the Receiver to get the characters
     received_data= char(Receiver.read()); // Display the Receivers characters
    Serial.print(received_data);               // Display the result on the serial monitor


//send to follower
   test.x =  received_data; //ASCII 70 = F
   esp_err_t result = esp_now_send(0, (uint8_t *) &test, sizeof(test_struct));
   /*if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }*/

  }



  
}
