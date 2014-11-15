
#include <SoftwareSerial.h>   //Software Serial Port

#define RxD 6
#define TxD 7
#define LED 13

String valRead = "";
boolean LEDstatus = false;

SoftwareSerial blueToothSerial(RxD,TxD);

void setup() 
{ 
  Serial.begin(9600);
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  pinMode(LED, OUTPUT);
  setupBlueToothConnection();
  digitalWrite(LED, LEDstatus);
} 

void loop() 
{ 
  while(1){
    if(blueToothSerial.available()) {
      valRead = blueToothSerial.readStringUntil('\n');
      Serial.println(valRead);
      LEDstatus = !LEDstatus;
      digitalWrite(LED, LEDstatus);
    }
  }
}


void setupBlueToothConnection()
{
  blueToothSerial.begin(38400); //Set BluetoothBee BaudRate to default baud rate 38400
  blueToothSerial.print("\r\n+STWMOD=0\r\n"); //set the bluetooth work in slave mode
  blueToothSerial.print("\r\n+STNA=BigRedButton\r\n"); //set the bluetooth name as "BTLights"
  blueToothSerial.print("\r\n+STOAUT=1\r\n"); // Permit Paired device to connect me
  blueToothSerial.print("\r\n+STAUTO=0\r\n"); // Auto-connection should be forbidden here
  delay(2000); // This delay is required.
  blueToothSerial.print("\r\n+INQ=1\r\n"); //make the slave bluetooth inquirable 
  Serial.println("The slave bluetooth is inquirable!");
  delay(2000); // This delay is required.
  blueToothSerial.flush();
}


