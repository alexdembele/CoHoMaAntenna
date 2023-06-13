//-------------Code Arduino-----------------

//Pour tester les servos, il faut  modifier les delay et les consignes selon les tests à effectuer
//Extension de l'exemple d'arduino pour prendre en charge 2 moteurs. Il faut faire attention aux branchements pour avoir la puissance nécessaire au fonctionnement

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
Servo myservo2; // There are 2 motors



void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(10); // attaches the other on pin 10
  pinMode(LED_BUILTIN, OUTPUT); //We use the led to check if the programm runs correctly
}

void loop() {
             // reads the value of the potentiometer (value between 0 and 1023)
  
  myservo2.write(10); // sets the servo position according to the scaled value
  myservo.write(120) ;          
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(2000);     // wait for 2 seconds             // waits for the servo to get there

  myservo2.write(140);   
  myservo.write(120);   
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(2000);                      // wait for 2 seconds               
}
