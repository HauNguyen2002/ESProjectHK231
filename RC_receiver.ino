#include <AFMotor.h>
#include <SPI.h>
#include <Arduino.h>
#include <nRF24L01.h>
#include <RF24.h>

AF_DCMotor motor1(1); 
AF_DCMotor motor2(2); 
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

RF24 radio(9,10); //Create a transceiver object that has CE and CSE pins at 9 and 10
const byte addr[6]="12345";//Tranmission address, must be identical to the transmitter
char Message[2];//Initialize a char array for storing data
uint8_t motorSpeed[]={255,255,255,255}; // Initialize the motor speed(0-255)

//-----------------Transform the command to motor control-----------
void stopMotor(){
    motor1.run(RELEASE);
    motor1.setSpeed(0); 
    motor2.run(RELEASE);
    motor2.setSpeed(0); 
    motor3.run(RELEASE); 
    motor3.setSpeed(0); 
    motor4.run(RELEASE); 
    motor4.setSpeed(0);
    delay(500);
}
void checkCmd(){
  if(Message[0]=='U'){
    motor1.run(FORWARD);
    motor1.setSpeed(motorSpeed[0]); 
    motor2.run(FORWARD);
    motor2.setSpeed(motorSpeed[1]); 
    motor3.run(FORWARD); 
    motor3.setSpeed(motorSpeed[2]); 
    motor4.run(FORWARD); 
    motor4.setSpeed(motorSpeed[3]); 
  }
  if(Message[0]=='D'){
    motor1.run(BACKWARD); 
    motor1.setSpeed(motorSpeed[0]); 
    motor2.run(BACKWARD); 
    motor2.setSpeed(motorSpeed[1]); 
    motor3.run(BACKWARD); 
    motor3.setSpeed(motorSpeed[2]); 
    motor4.run(BACKWARD); 
    motor4.setSpeed(motorSpeed[3]); 
  }
  if(Message[0]=='L'){
    motor1.run(FORWARD);
    motor1.setSpeed(motorSpeed[0]); 
    motor2.run(BACKWARD); 
    motor2.setSpeed(motorSpeed[1]); 
    motor3.run(FORWARD);  
    motor3.setSpeed(motorSpeed[2]); 
    motor4.run(BACKWARD);
    motor4.setSpeed(motorSpeed[3]); 
  }
  if(Message[0]=='R'){
    motor1.run(BACKWARD); 
    motor1.setSpeed(motorSpeed[0]); 
    motor2.run(FORWARD); 
    motor2.setSpeed(motorSpeed[1]); 
    motor3.run(BACKWARD);
    motor3.setSpeed(motorSpeed[2]); 
    motor4.run(FORWARD); 
    motor4.setSpeed(motorSpeed[3]);
  }
  if(Message[0]=='1'){
    
  }
  if(Message[0]=='2'){
    
  }
  if(Message[0]=='3'){
    
  }
  if(Message[0]=='C'){
    motor1.run(FORWARD);
    motor1.setSpeed(motorSpeed[0]); 
    motor2.run(BACKWARD); 
    motor2.setSpeed(motorSpeed[1]); 
    motor3.run(BACKWARD);  
    motor3.setSpeed(motorSpeed[2]); 
    motor4.run(FORWARD);
    motor4.setSpeed(motorSpeed[3]); 
  }
  if(Message[0]=='V'){
    motor1.run(BACKWARD);
    motor1.setSpeed(motorSpeed[0]); 
    motor2.run(FORWARD); 
    motor2.setSpeed(motorSpeed[1]); 
    motor3.run(FORWARD);  
    motor3.setSpeed(motorSpeed[2]); 
    motor4.run(BACKWARD);
    motor4.setSpeed(motorSpeed[3]);
  }
}
//--------------------------------------------------------

void setup() {
  Serial.begin(9600);//Set baud rate for virtual terminal 
  radio.begin();//Start the transceiver
  radio.openReadingPipe(1, addr);// Open pipe 1 for reading, choose pipe from 1-5 (pipe 0 is for writing)
  radio.setPALevel(RF24_PA_MAXr;;;;;;;;;;;;;;;;;;;;;;;;;;;rfr);// Set power level
  radio.setChannel(108);//Set channel, choose one in 0-125, must be identical to the transmitter
  radio.setDataRate(RF24_250KBPS);//Set data transfer rate
  radio.startListening();//Set the transceiver as the transmitter
  if (!radio.available())
  {
    Serial.println("Connecting the TX.......");
  }

}
void loop() { 
  if (radio.available()) {//Start reading if the transceivers are connected
      radio.read(&Message, sizeof(Message));// Read the data from the pipe and savee it to the char array
      if(Message[0]!=' '){
        Serial.println(Message);
            stopMotor();//Stop all motors before processing another command
          checkCmd();//Process the command
      }
    }
}
