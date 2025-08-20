// 19.1s

#include <Servo.h>
#include <AccelStepper.h>
#include <AccelStepperWithDistance.h>
int pos = 0;

float pi = 3.14;
int enaPinL = 13;
int dirPinL = 12;
int stepPinL = 11;

int enaPinR = 5;
int dirPinR = 6;
int stepPinR = 7;

int enaPinScoop = 2;
int dirPinScoop = 3;
int stepPinScoop = 4;

int servoPin = 10;
int servoPosition = 0;
Servo servo;

int ledPin = 8;

int switchPin = 9;
bool switchStep;

AccelStepperWithDistance Lstepper(AccelStepperWithDistance::DRIVER, stepPinL, dirPinL);
AccelStepperWithDistance Rstepper(AccelStepperWithDistance::DRIVER, stepPinR, dirPinR);
AccelStepperWithDistance Sstepper(AccelStepperWithDistance::DRIVER, stepPinScoop, dirPinScoop);

bool moved = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(enaPinL, OUTPUT);
  pinMode(dirPinL, OUTPUT);
  pinMode(stepPinL, OUTPUT);

  pinMode(enaPinR, OUTPUT);
  pinMode(dirPinR, OUTPUT);
  pinMode(stepPinR, OUTPUT);

  pinMode(enaPinScoop, OUTPUT);
  pinMode(dirPinScoop, OUTPUT);
  pinMode(stepPinScoop, OUTPUT);

  pinMode(switchPin, INPUT_PULLUP);

  pinMode(ledPin, OUTPUT);

  digitalWrite(enaPinL,LOW);
  digitalWrite(enaPinR, LOW);
  digitalWrite(enaPinScoop, LOW);

  

  Lstepper.setMaxSpeed(200);
  Lstepper.setAcceleration(1000);
  Lstepper.setStepsPerRotation(200);   // 1.8° stepper motor
  Lstepper.setMicroStep(1);           // 1 microstepping
  Lstepper.setDistancePerRotation(267);  // 8mm per rotation
  Lstepper.setAnglePerRotation(360);   // Standard 360° per rotation

  Rstepper.setMaxSpeed(200);
  Rstepper.setAcceleration(1000);
  Rstepper.setStepsPerRotation(200);   // 1.8° stepper motor
  Rstepper.setMicroStep(1);           // 1 microstepping
  Rstepper.setDistancePerRotation(267);  // 8mm per rotation
  Rstepper.setAnglePerRotation(360);   // Standard 360° per rotation

  Sstepper.setMaxSpeed(3500);
  Sstepper.setAcceleration(1300);
  Sstepper.setStepsPerRotation(200);   // 1.8° stepper motor
  Sstepper.setMicroStep(1);           // 1 microstepping
  Sstepper.setDistancePerRotation(60);  // 8mm per rotation
  Sstepper.setAnglePerRotation(360);   // Standard 360° per rotation
  // TODO: Invert dir pin for Sstepper
}

int servoDeg(int degrees){
  return 500 + degrees * (2000.0/270.0);
}

void loop() {
  // servo.writeMicroseconds(servoDeg(45));
  
  while (digitalRead(switchPin) == HIGH){}
  // if (!moved){
    servo.attach(servoPin, 500, 2500);
    // servo.writeMicroseconds(servoDeg(140));
    
    Sstepper.moveRelative(-170);
    Lstepper.moveRelative(460);
    Rstepper.moveRelative(460);

    while (Lstepper.distanceToGo() != 0 || Rstepper.distanceToGo() != 0){
      Lstepper.run();
      Rstepper.run();
      Sstepper.run();
    }

    // Robot in front of balls

    for (int pos = 140; pos >= 40; pos --) {
      servo.writeMicroseconds(servoDeg(pos));
      delay(5);
    }

    Sstepper.moveRelative(120);
    while (Sstepper.distanceToGo() != 0){
      Sstepper.run();
    }

    servo.writeMicroseconds(servoDeg(0));
    Sstepper.moveRelative(-70);
    while(Sstepper.distanceToGo() != 0){
      Sstepper.run();
    }
    // Robot has balls

    Lstepper.moveRelative(-352);
    Rstepper.moveRelative(352);
    while (Lstepper.distanceToGo() != 0 || Rstepper.distanceToGo() != 0){
      Lstepper.run();
      Rstepper.run();
    }
    // Robot ready to go over ramp

    // Lstepper.setMaxSpeed(200);
    // Rstepper.setMaxSpeed(200);

    Lstepper.moveRelative(1200);
    Rstepper.moveRelative(1200);
    while (Lstepper.distanceToGo() != 0 || Rstepper.distanceToGo() != 0){
      Lstepper.run();
      Rstepper.run();]
    }

    // Robot starts to tip ramp

    delay(125);
    Lstepper.setMaxSpeed(1500);
    Rstepper.setMaxSpeed(1500);
    Lstepper.moveRelative(-170);
    Rstepper.moveRelative(-170);
    while (Lstepper.distanceToGo() != 0 || Rstepper.distanceToGo() != 0){
      Lstepper.run();
      Rstepper.run();
    }
    // Robot backed off
    delay(40); // TODO: Increase delay?

    Lstepper.setMaxSpeed(300);
    Rstepper.setMaxSpeed(300);

    Lstepper.moveRelative(835);
    Rstepper.moveRelative(835);
    while (Lstepper.distanceToGo() != 0 || Rstepper.distanceToGo() != 0){
      Lstepper.run();
      Rstepper.run();
    }

  // Robot is at the end of the ramp
  // TODO: tune numbers for end 

    Lstepper.moveRelative(-355);
    Rstepper.moveRelative(355);
    while (Lstepper.distanceToGo() != 0 || Rstepper.distanceToGo() != 0){
      Lstepper.run();
      Rstepper.run();
    }

    Lstepper.moveRelative(60);
    Rstepper.moveRelative(60);
    Sstepper.moveRelative(-50);
    while (Lstepper.distanceToGo() != 0 || Rstepper.distanceToGo() != 0 || Sstepper.distanceToGo() != 0){
      Lstepper.run();
      Rstepper.run();
      Sstepper.run();
    }
    servo.writeMicroseconds(servoDeg(235));
    delay(300);
    // Robot drops balls
    Lstepper.setMaxSpeed(1000);
    Rstepper.setMaxSpeed(1000);
    Lstepper.moveRelative(-150);
    Rstepper.moveRelative(-150);

    Sstepper.setMaxSpeed(5000);
    Sstepper.setAcceleration(2500);
    Sstepper.moveRelative(170);
    while (Lstepper.distanceToGo() != 0 || Rstepper.distanceToGo() != 0 || Sstepper.distanceToGo() != 0){
      
      Lstepper.run();
      Rstepper.run();
      Sstepper.run();
    }
    // End run
  //   moved = 1;
  // }
  delay(150);

  while (1) {
    digitalWrite(ledPin, HIGH);
  }

}
