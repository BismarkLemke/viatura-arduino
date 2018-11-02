/*
PROJETO VIATURA

BISMARK AND PATRICK

*/


//Libraries
#include <AFMotor.h>
#include <Servo.h>

//Objects
AF_DCMotor MOTORTRACAO(2, MOTOR12_64KHZ); // create motor #2, 64KHz pwm
Servo myservo;  // Servo ligaod na porta 9


//VARIAVEIS CONSTANTES
char dataIn = 'S';
char COMANDO;
char det;
int vel = 0; //Bluetooth Stuff
int frontLight = 13;
int backLight = 14;
int horn = 7;


void setup() {
Serial.begin(9600); // set up Serial library at 9600 bps

pinMode(frontLight, OUTPUT);
pinMode(horn, OUTPUT);

//Initalization messages
Serial.println("VIATURA - 01");

// Define que o servo esta ligado a porta 9
myservo.attach(10);

//turn off motors
MOTORTRACAO.setSpeed(0);
MOTORTRACAO.run(RELEASE);

digitalWrite(frontLight, LOW);
noTone(horn);

}

void loop() {
det = check(); //call check() subrotine to get the serial code

// Move o eixo do servo, de acordo com o angulo
myservo.write(110);

if(det == 'L'){
myservo.write(145);
delay(150);
det = 'S';
}else if(det == 'R'){
myservo.write(80);
delay(150);
det = 'S';
}

switch (det) {
case 'F': // F, move forward
MOTORTRACAO.setSpeed(vel);
MOTORTRACAO.run(FORWARD);
det = check();
break;

case 'I': // I, move forward and Right
MOTORTRACAO.setSpeed(vel);
MOTORTRACAO.run(FORWARD);
myservo.write(85);
delay(150);
det = check();
break;


case 'G': // G, move forward and Left
MOTORTRACAO.setSpeed(vel);
MOTORTRACAO.run(FORWARD);
myservo.write(140);
delay(150);
det = check();
break;

case 'B': // B, move back
MOTORTRACAO.setSpeed(vel);
MOTORTRACAO.run(BACKWARD);
det = check();
break;


case 'J': // J, move backward and Right
MOTORTRACAO.setSpeed(vel);
MOTORTRACAO.run(BACKWARD);
myservo.write(85);
delay(150);
det = check();
break;


case 'H': // H, move backward and Left
MOTORTRACAO.setSpeed(vel);
MOTORTRACAO.run(BACKWARD);
myservo.write(140);
delay(150);
det = check();
break;

case 'S': // S, stop
//turn off motors
MOTORTRACAO.setSpeed(0);
MOTORTRACAO.run(RELEASE);
det = check();
break;


case 'V': // V, BUZINA LIGADO
//Serial.println("BUZINA LIGADO");
tone(horn, 800, 100);
det = check();
break;

case 'v': //v, BUZINA DESLIGADO
//Serial.println("BUZINA DESLIGADO");
noTone(horn);
det = check();
break;

case 'W': //W, FAROL LIGADO
//Serial.println("FAROL LIGADO");
digitalWrite(frontLight, HIGH);
break;

case 'w': //w, FAROL DESLIGADO
//Serial.println("FAROL DESLIGADO");
digitalWrite(frontLight, LOW);
break;

}
}

//get bluetooth code received from serial port
int check() {
if (Serial.available() > 0) { // if there is valid data in the serial port
dataIn = Serial.read();// stores data into a varialbe

//check the code
if (dataIn == 'F') { //Forward
COMANDO = 'F';
}
else if (dataIn == 'B') { //Backward
COMANDO = 'B';
}
else if (dataIn == 'L') { //Left
COMANDO = 'L';
}
else if (dataIn == 'R') { //Right
COMANDO = 'R';
}
else if (dataIn == 'I') { //Froward Right
COMANDO = 'I';
}
else if (dataIn == 'J') { //Backward Right
COMANDO = 'J';
}
else if (dataIn == 'G') { //Forward Left
COMANDO = 'G';
}
else if (dataIn == 'H') { //Backward Left
COMANDO = 'H';
}
else if (dataIn == 'S') { //Stop
COMANDO = 'S';
}
else if (dataIn == '0') { //Speed 0
vel = 0;
}
else if (dataIn == '1') { //Speed 25
vel = 50;
}
else if (dataIn == '2') { //Speed 50
vel = 75;
}
else if (dataIn == '3') { //Speed 75
vel = 80;
}
else if (dataIn == '4') { //Speed 100
vel = 100;
}
else if (dataIn == '5') { //Speed 125
vel = 125;
}
else if (dataIn == '6') { //Speed 150
vel = 150;
}
else if (dataIn == '7') { //Speed 175
vel = 175;
}
else if (dataIn == '8') { //Speed 200
vel = 200;
}
else if (dataIn == '9') { //Speed 225
vel = 255;
}
else if (dataIn == 'q') { //Speed 255
vel = 255;
}
else if (dataIn == 'U') { //LUZ DE Re LIGADO
COMANDO = 'U';
}
else if (dataIn == 'u') { //LUZ DE Re DESLIGADO
COMANDO = 'u';
}
else if (dataIn == 'W') { //FAROL LIGADO
COMANDO = 'W';
}
else if (dataIn == 'w') { //FAROL DESLIGADO
COMANDO = 'w';
}
else if (dataIn == 'V') { //BUZINA LIGADO
COMANDO = 'V';
}
else if (dataIn == 'v') { //BUZINA DESLIGADO
COMANDO = 'v';
}
else if (dataIn == 'X') { //Extra On
COMANDO = 'X';
}
else if (dataIn == 'x') { //Extra Off
COMANDO = 'x';
}
}
return COMANDO;
}

