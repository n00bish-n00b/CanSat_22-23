#include <XBee.h>
#include <SoftwareSerial.h>

const byte rxPin = 5;
const byte txPin = 6;

// Set up a new SoftwareSerial object
SoftwareSerial mySerial (rxPin, txPin);
XBee xbee = XBee();
XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x41F4267C);

void setup() {
  mySerial.begin(9600);
  xbee.setSerial(mySerial);
}
void loop() {
  
  String data = "1062,08:17:40,00004,F,ascent,00100.1,N,N,N,00023.6,00003.6,00101.1,00:07:33,00100.1,17.5449,078.5718,00005,045.65,035.65,CXON";
  
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
