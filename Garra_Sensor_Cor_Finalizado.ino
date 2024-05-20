#include <Wire.h>
#include <Adafruit_TCS34725.h>
#include <VarSpeedServo.h>

// Inicializar o sensor de cor
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

// Inicializar os 4 servos usando VarSpeedServo
VarSpeedServo servoVermelho;
VarSpeedServo servoVerde;
VarSpeedServo servoAzul;
VarSpeedServo servoOutraCor;

void setup() {
  Serial.begin(9600);
  
  // Inicializar o sensor de cor
  if (!tcs.begin()) {
    Serial.println("Não foi possível encontrar o sensor de cor. Verifique as conexões!");
    while (1);
  }

  // Inicializar os 4 servos
  servoVermelho.attach(13);   // Pino de controle do servoVermelho
  servoVerde.attach(2);      // Pino de controle do servoVerde
  servoAzul.attach(9);       // Pino de controle do servoAzul
  servoOutraCor.attach(10);   // Pino de controle do servoOutraCor
}

void loop() {

  //posição para pegar a caixa
  moverServos(15, 90, 130, 90); // Pegar caixa
  delay(2000);
  moverServos(15, 120, 130, 90); // Pegar caixa
  delay(3000);
  moverServos(15, 120, 180, 90); // Pegar caixa


  // Ler dados do sensor de cor
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);

  // Exibir valores lidos
  Serial.print("Red: "); Serial.print(r);
  Serial.print(" Green: "); Serial.print(g);
  Serial.print(" Blue: "); Serial.print(b);
  Serial.print(" Clear: "); Serial.println(c);

  // Determinar a posição de cada servo com base na cor
  if (r > b && r > g) {
    // Vermelho
    moverServos(100, 135, 130, 90); // Pegar caixa
    delay(5000);
    moverServos(100, 135, 180, 180); // Mover todos os servos para a posição 90
    delay(5000);
    moverServos(0, 135, 180, 180); // soltar caixa

    Serial.println("Cor detectada: Vermelho");
  } else if (g > r && g > b) {
    // Verde
    moverServos(15, 90, 130, 90); // inicial
    delay(2000);

    Serial.println("Cor detectada: Verde");
  } else if (b > r && b > g) {
    moverServos(100, 135, 130, 90); // Pegar caixa
    delay(5000);
    moverServos(100, 135, 180, 0); // Mover todos os servos para a posição 90
    delay(5000);
    moverServos(0, 135, 180, 0); // soltar caixa

    // Azul
    Serial.println("Cor detectada: Azul");
  } else {
    // Outra cor
    moverServos(15, 90, 130, 90); // inicial
    delay(2000);
    Serial.println("Cor detectada: Outra cor");
  }

  delay(5000); // Aguardar um curto período antes de ler novamente os dados do sensor
}

// Função para mover os 4 servos para posições específicas
void moverServos(int posServoVermelho, int posServoVerde, int posServoAzul, int posServoOutraCor) {
  servoVermelho.slowmove(posServoVermelho, 20); // 10 é a velocidade, ajuste conforme necessário
  servoVerde.slowmove(posServoVerde, 10);
  servoAzul.slowmove(posServoAzul, 10);
  servoOutraCor.slowmove(posServoOutraCor, 10);
}
