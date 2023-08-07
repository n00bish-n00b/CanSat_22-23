#include <XBee.h>

XBee xbee = XBee();
XBeeResponse response = XBeeResponse();
ZBRxResponse rx = ZBRxResponse();
ModemStatusResponse msr = ModemStatusResponse();
bool gotResponse,ack,associated,errorAfterPacketRecieved,errorReadingPacket,errorAfterResponseRecieved;


void setup() {

 
  Serial.begin(9600);
  xbee.begin(Serial);
  
 
}


void loop() {
    
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
          for (int i = 0; i < rx.getDataLength(); i++) 
          { 
            temp[i] = rx.getData(i);
          } 
          String recievedData = String(temp);
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
        errorAfterPacketRecieved = true;
        //Serial.println("There is some unexpected error");  
      }
    } 
    else if (xbee.getResponse().isError()) 
    {
      errorReadingPacket = true;
      Serial.print("Error reading packet.  Error code: ");  
      Serial.println(xbee.getResponse().getErrorCode());
    }
}
