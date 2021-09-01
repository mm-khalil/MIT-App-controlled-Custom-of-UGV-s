#include <esp_now.h>
#include <WiFi.h>

String com;
int i=0;
String arr[19];
//Structure example to receive data
//Must match the sender structure
typedef struct test_struct {
  String x; 
  //String x;
} 
test_struct;

//Create a struct_message called myData
test_struct myData;

//callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  //Serial.print("data received: ");
  //Serial.println(   len);
  //Serial.print("x: ");
  //Serial.print(myData.x);
  //Serial2.write(myData.x);

   
   arr[i]=String(myData.x);
   
    //Serial.print(arr[5]);
    i=i+1;
    //Serial.println();
if (arr[19] == "GET /forwad HTTP/1.1")
  {   
      Serial2.write('F');
      i=0;
      //Serial.print("F-in");   
       }

   if (arr[5] == 's') 
    {  
      Serial2.write('S');
      Serial.print("S-in");  
        }
        


        
    /*    
    else if (myData.x="GET /reverse HTTP/1.1") 
    {   Serial2.write('B');
        Serial.print("B");   }
        
    else if (myData.x="GET /left HTTP/1.1") 
    {   Serial2.write('L');
        Serial.print("L");   }
        
    else if (myData.x="GET /right HTTP/1.1") 
    {   Serial2.write('R');
        Serial.print("R");   }
    */   




    
    
    
  
}
 
void setup() {
  //Initialize Serial Monitor
  Serial.begin(115200);
  Serial2.begin(4800);
  
  //Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  //Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
} 
 
void loop() {
  

}
