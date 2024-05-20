#include <Servo.h>
#include <AFMotor.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
AF_DCMotor motor1(1); // Motor esquerdo
AF_DCMotor motor2(2); // Motor direito

int pin_servo1 = 2;  // Pino do servo 1
int pin_servo2 = 13; // Pino do servo 2
int pin_servo3 = 10; // Pino do servo 3
int pin_servo4 = 9;  // Pino do servo 4

int angle1 = 90; // Posição inicial do servo 1
int angle2 = 90; // Posição inicial do servo 2
int angle3 = 90; // Posição inicial do servo 3
int angle4 = 150; // Posição inicial do servo 4

void setup() {
  servo1.attach(pin_servo1);
  servo2.attach(pin_servo2);
  servo3.attach(pin_servo3);
  servo4.attach(pin_servo4);

  servo1.write(angle1);
  servo2.write(angle2);
  servo3.write(angle3);
  servo4.write(angle4);

  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    int newAngle;

    switch (command) {
      case '1':
        newAngle = angle1 + 10;
        servo1.write(newAngle);
        angle1 = newAngle;
        break;
      case '2':
        newAngle = angle1 - 10;
        servo1.write(newAngle);
        angle1 = newAngle;
        break;
      case '3':
        newAngle = angle2 + 10;
        servo2.write(newAngle);
        angle2 = newAngle;
        break;
      case '4':
        newAngle = angle2 - 10;
        servo2.write(newAngle);
        angle2 = newAngle;
        break;
      case '5':
        newAngle = angle3 + 10;
        servo3.write(newAngle);
        angle3 = newAngle;
        break;
      case '6':
        newAngle = angle3 - 10;
        servo3.write(newAngle);
        angle3 = newAngle;
        break;
      case '7':
        newAngle = angle4 + 10;
        servo4.write(newAngle);
        angle4 = newAngle;
        break;
      case '8':
        newAngle = angle4 - 10;
        servo4.write(newAngle);
        angle4 = newAngle;
        break;
      case 'F':
        // Mover para frente
        motor1.setSpeed(255);
        motor2.setSpeed(255);
        motor1.run(FORWARD);
        motor2.run(FORWARD);
        break;
      case 'B':
        // Mover para trás
        motor1.setSpeed(255);
        motor2.setSpeed(255);
        motor1.run(BACKWARD);
        motor2.run(BACKWARD);
        break;
      case 'L':
        // Virar à esquerda
        motor1.setSpeed(150);
        motor2.setSpeed(150);
        motor1.run(BACKWARD);
        motor2.run(FORWARD);
        break;
      case 'R':
        // Virar à direita
        motor1.setSpeed(150);
        motor2.setSpeed(150);
        motor1.run(FORWARD);
        motor2.run(BACKWARD);
        break;
      case 'S':
        // Parar
        motor1.setSpeed(0);
        motor2.setSpeed(0);
        motor1.run(RELEASE);
        motor2.run(RELEASE);
        break;
      // Adicione mais comandos para outros servos, se necessário
    }
  }
}
