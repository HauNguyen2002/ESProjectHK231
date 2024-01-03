#include <RevEng_PAJ7620.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

RF24 radio(9,10); //Create a transceiver object that has CE and CSE pins at 9 and 10

RevEng_PAJ7620 sensor = RevEng_PAJ7620(); //Create a sensor oprating object

const byte addr[6]="12345"; //Tranmission address
char SentMessage[1]="";// Initialize a char array for storing data

//----------Detect gestures and put the result in the char array--------------------
void gesMode(){
  Gesture gesture=sensor.readGesture();
  int obj_size=sensor.getObjectSize();
    switch(gesture){
      case GES_UP:
      strcpy(SentMessage,"U");
      Serial.println("UP");
      break;
      case GES_DOWN:
      strcpy(SentMessage,"D");
      Serial.println("DOWN");
      break;
      case GES_LEFT:
      strcpy(SentMessage,"L");
      Serial.println("LEFT");
      break;
      case GES_RIGHT:
      strcpy(SentMessage,"R");
      Serial.println("RIGHT");
      break;
      case GES_FORWARD:
      strcpy(SentMessage,"S");
        Serial.println("FORWARD");
      break;
      case GES_BACKWARD:
      strcpy(SentMessage,"S");
        Serial.println("BACKWARD");
      break;
      case GES_CLOCKWISE:
      strcpy(SentMessage,"C");
      Serial.println("CLOCKWISE");
      break;
      case GES_ANTICLOCKWISE:
      strcpy(SentMessage,"V");
      Serial.println("ANTICLOCKWISE");
      break;
      case GES_WAVE:
      Serial.println("Wave");
      break;
      case GES_NONE:
      strcpy(SentMessage," ");
      break;
    }
}
//-----------------------------------
//void curMode(){
//  if(sensor.isCursorInView()){
//    Serial.print("X: ");
//    Serial.print(sensor.getCursorX());
//    Serial.print(" Y: ");
//    Serial.println(sensor.getCursorY());
//  }
//}
//void proxMode(int obj){
//    if(obj<300) strcpy(SentMessage,"1");
//    if(obj>=300 && obj<800) strcpy(SentMessage,"2");
//    if(obj>=800) strcpy(SentMessage,"3");
//    Serial.print("Size: ");
//    Serial.println(obj);
//}

void setup() {
  Serial.begin(9600); //Set baud rate for virtual terminal 
  sensor.begin(); //Start the sensor
  sensor.setNormalSpeed();//Set normal scan speed (60-600o)
  sensor.setGestureMode();//Set mode to Gesture mode
  sensor.setGestureEntryTime(0);//The wait time before a gesture is process
  sensor.setGestureExitTime(200);//The wait time before receiving a new gesture
    //------------------

    radio.begin();//Start the transceiver
  radio.openWritingPipe(addr);// Open the pipe for writing, choose pipe 0 be default
  radio.setPALevel(RF24_PA_MAX); //Set power level
  radio.setChannel(108); // Set channel, choose one in 0-125, , must be identical to the receiver
  radio.setDataRate(RF24_250KBPS); //Set data transfer rate
  radio.stopListening();//Set the transceiver as the transmitter
  if (!radio.available())
  {
    Serial.println("Connecting the RX.......");
  }
}
void loop() {
      gesMode();
      if(SentMessage[0]!=' '){
        radio.write(&SentMessage,sizeof(SentMessage)); // Write the data to the pipe and start sending the package
      }
}
