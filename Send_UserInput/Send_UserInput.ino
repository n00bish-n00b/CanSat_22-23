#include <XBee.h>

XBee xbee = XBee();
XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x41F4267C);

void setup() {
  Serial.begin(9600);
  xbee.begin(Serial);
}
void loop() {
  
  while(Serial.available() == 0){}
  
  String data = Serial.readString();
  
  int data_len = data.length()+1; //Declare data_len var
  
  char temp[data_len]; //Create a temporary Character array
  
  uint8_t payload[data_len]; // Create the payload array
  
  data.toCharArray(temp,data_len); //Convert string(data) to char array(temp)
  
  for(int i=0;i<data_len;i++)
  {
    payload[i] = (uint8_t)temp[i]; //typecast char to uint8_t
  }
  

  
  ZBTxRequest zbTx = ZBTxRequest(addr64, payload, sizeof(payload));
  
  xbee.send(zbTx);
  
  delay(1000);

//for(int i=0;i<data_len;i++)
//  {
//    Serial.print(payload[i]);
//  }
//  Serial.println();

}
