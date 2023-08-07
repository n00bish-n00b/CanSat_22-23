#include <XBee.h>
#include <SoftwareSerial.h>

long int t1,t2;

XBee xbee = XBee();
XBeeResponse response = XBeeResponse();
ZBRxResponse rx = ZBRxResponse();
ModemStatusResponse msr = ModemStatusResponse();
XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x41F4267C);
bool gotResponse,ack,associated,errorAfterPacketRecieved,errorReadingPacket,errorAfterResponseRecieved;

const byte rxPin = 5;
const byte txPin = 6;

// Set up a new SoftwareSerial object
SoftwareSerial SoftSerial (rxPin, txPin);


void sendPacket()
{
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
}






void checkForRxPacket()
{
  xbee.readPacket();
  if (xbee.getResponse().isAvailable()) 
  {
      // got something
      gotResponse = true;
     
      
      if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE)
      {
        // got a zb rx packet
        // now fill our zb rx classx`
        xbee.getResponse().getZBRxResponse(rx);
        associated = true;
            
          if (rx.getOption() == ZB_PACKET_ACKNOWLEDGED)
          {
            ack = true;
          }
           else 
          {
            // we got it (obviously) but sender didn't get an ACK
            ack = false;
          }
          char temp[rx.getDataLength() +1];
          for (int i = 0; i <( rx.getDataLength()); i++) 
          { 
            temp[i] = rx.getData(i);
          } 
          String recievedData = String(temp);
          unsigned int index;
          index = recievedData.indexOf("\n");
          recievedData.remove(index);
          Serial.println(recievedData);
      } 
      else if (xbee.getResponse().getApiId() == MODEM_STATUS_RESPONSE) 
      {
        xbee.getResponse().getModemStatusResponse(msr);
       
        
        if (msr.getStatus() == ASSOCIATED)
        {
          associated = true;
        }
        else if (msr.getStatus() == DISASSOCIATED) 
        {
          associated = false;
        }
        else 
        {
          errorAfterResponseRecieved = true;
        }
      }
      else 
      {
        gotResponse = false;
        errorAfterPacketRecieved = true;
        //Serial.println("There is some unexpected error");  
      }
    } 
    else if (xbee.getResponse().isError()) 
    {
      gotResponse = false;
      errorReadingPacket = true;
      Serial.print("Error reading packet.  Error code: ");  
      Serial.println(xbee.getResponse().getErrorCode());
    }
}

void setup() {

  Serial.begin(9600);
  SoftSerial.begin(9600);
  xbee.begin(SoftSerial); 
}
void loop() {
    t1 = millis(); 
  checkForRxPacket();
  if((t1 - t2) >= 1000)
  {
    t2 = t1;
    sendPacket();
  }
}
