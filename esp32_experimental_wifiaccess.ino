   /*
  WiFiAccessPoint.ino creates a WiFi access point and provides a web server on it.

  Steps:
  1. Connect to the access point "yourAp"
  2. Point your web browser to http://192.168.4.1/H to turn the LED on or http://192.168.4.1/L to turn it off
     OR
     Run raw TCP "GET /H" and "GET /L" on PuTTY terminal with 192.168.4.1 as IP address and 80 as port

  Created for arduino-esp32 on 04 July, 2018
  by Elochukwu Ifediora (fedy0)
*/

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

#define LED_BUILTIN 2   // Set the GPIO pin where you connected your test LED or comment this line out if your dev board has a built-in LED

// Set these to your desired credentials.
const char *ssid = "yourAP";
const char *password = "yourPassword";

WiFiServer server(80);


HardwareSerial unit1(1);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  unit1.begin(9600,SERIAL_8N1,1,3);
  Serial2.begin(4800);
  
  Serial.println();
  Serial.println("Configuring access point...");

  // You can remove the password parameter if you want the AP to be open.
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

  Serial.println("Server started");
}

void loop() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client)
  {String req =client.readStringUntil('\r');
   Serial.println(req);
   client.flush();
   
   if (req.indexOf("/forward")!=-1) {
  
   digitalWrite(2,HIGH);
   Serial2.write('F');
   unit1.write('F');
   }
   else if(req.indexOf("/reverse")!=-1){
   
   Serial2.write('B');
   unit1.write('B');
  }
  else if(req.indexOf("/left")!=-1){
   Serial2.write('L');
   unit1.write('L');
  }
  else if(req.indexOf("/right")!=-1){
   Serial2.write('R');
   unit1.write('R');
  }
  else if(req.indexOf("/stop")!=-1){
   Serial2.write('S');
   unit1.write('S');
   digitalWrite(2,LOW);
  }
  
}
}
