#include <XBee.h>

XBee xbee = XBee();
XBeeResponse response = XBeeResponse();
ZBRxResponse rx = ZBRxResponse();
ModemStatusResponse msr = ModemStatusResponse();


char *payload;

// SH + SL Address of receiving XBee
XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x41F4267C);
ZBTxRequest zbTx = ZBTxRequest(addr64, payload, sizeof(payload));
ZBTxStatusResponse txStatus = ZBTxStatusResponse();

int i=0;


void setup() {

  Serial.begin(9600);
  xbee.begin(Serial);
  
}
void loop() {
char *payload = i;
  xbee.send(zbTx);
  delay(1000);
  i++;
}
