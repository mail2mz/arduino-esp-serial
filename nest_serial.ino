
#include <Wire.h>

#include <ArduinoJson.h>



#include <SoftwareSerial.h>

SoftwareSerial s(5,6);

void setup() {

 Wire.begin(8);                /* join i2c bus with address 8 */

 Wire.onReceive(receiveEvent); /* register receive event */

 Serial.begin(9600);           /* start serial for debug */



  pinMode(3, OUTPUT);

 s.begin(9600);
   Serial.println("Setup complete\n");;           /* print the request data */
}



void loop() {
   int data;
 //delay(100);
   s.write("s");
  if (s.available()>0)
  {
    data=s.read();
    Serial.println("receive data\n");
    Serial.println(data);
  }

}



void processCall(String command){

      DynamicJsonBuffer jsonBuffer;

      JsonObject& root= jsonBuffer.parseObject(command);

      

       if (root.success()) {

          int gpio = atoi(root["gpio"]);

          Serial.println(gpio);

          int state = atoi(root["state"]);

          Serial.println(state);



          //set GPIO state  

          digitalWrite(gpio, state);

       }

}





// function that executes when data is received from master

void receiveEvent(int howMany) {

  String data="";

 while (0 <Wire.available()) {

    char c = Wire.read();      /* receive byte as a character */

    data += c;

    

  }

    Serial.println(data);           /* print the request data */

    processCall(data);         /* to newline */

}
