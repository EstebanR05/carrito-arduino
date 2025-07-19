#include <Adafruit_Sensor.h>  // Incluir la librería para los sensores Adafruit
#include <ESP32Servo.h>       // Incluir la librería para el control de servos en ESP32
#include <BluetoothSerial.h>  // Incluir la librería para la comunicación Bluetooth

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run make menuconfig to enable it
#endif

int LED_BUILTIN = 2;  // Pin del LED integrado
char ejemplo;         // Variable para almacenar un carácter recibido por Bluetooth
#define sensorPin 18  // Pin del sensor

// Definición de pines del controlador de motor L298N
int motor1Pin1 = 27;
int motor1Pin2 = 26;
int enable1Pin = 14;
int motor2Pin3 = 33;
int motor2Pin4 = 32;
int enable2Pin = 25;

// Crear instancia del servo
Servo servo;

// Variable para la comunicación Bluetooth
BluetoothSerial SerialBT;

void setup() {
  // Configurar pines de salida para el controlador de motor L298N
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  pinMode(motor2Pin3, OUTPUT);
  pinMode(motor2Pin4, OUTPUT);
  pinMode(enable2Pin, OUTPUT);

  pinMode(sensorPin, INPUT);  // Configurar el pin del sensor como entrada

  // Inicializar el servo
  servo.attach(21);  // Conectar el servo al pin 21
  servo.write(90);   // Posición inicial del servo

  // Inicializar la comunicación serial
  Serial.begin(115200);

  // Inicializar la comunicación Bluetooth
  SerialBT.begin("ESP32test");  // Establecer el nombre del dispositivo Bluetooth
}

void inductiveSensor() {
  if (digitalRead(sensorPin) == 1) {
    //move the servo
    for (int pos = 0; pos <= 180; pos += 1) {
      servo.write(pos);
      delay(15);
    }
  }

  delay(15);
}

void loop() {
  //acceder a la funcinalidad para que detecte o no los metales
  inductiveSensor();

  // Leer el carácter recibido por Bluetooth, si hay alguno disponible
  if (SerialBT.available()) {
    char receivedChar = SerialBT.read();
    Serial.print("Received: ");
    Serial.println(receivedChar);
    ejemplo = receivedChar;

    // Realizar acciones en base al carácter recibido
    if (ejemplo == 'A') {
      moveForward();
    } else if (ejemplo == 'B') {
      moveBackward();
    } else if (ejemplo == 'C') {
      turnLeft();
    } else if (ejemplo == 'D') {
      turnRight();
    }
  }
}

void stopMotors() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(enable1Pin, LOW);
  digitalWrite(motor2Pin3, LOW);
  digitalWrite(motor2Pin4, LOW);
  digitalWrite(enable2Pin, LOW);
}

void moveForward() {
  // Mover el motor hacia adelante
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(enable1Pin, HIGH);
  digitalWrite(motor2Pin3, HIGH);
  digitalWrite(motor2Pin4, LOW);
  digitalWrite(enable2Pin, HIGH);
  delay(1000);
  stopMotors();
}

void moveBackward() {
  // Mover el motor hacia atrás
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(enable1Pin, HIGH);
  digitalWrite(motor2Pin3, LOW);
  digitalWrite(motor2Pin4, HIGH);
  digitalWrite(enable2Pin, HIGH);
  delay(1000);
  stopMotors();
}

void turnRight() {
  // Girar a la derecha
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(enable1Pin, HIGH);
  digitalWrite(motor2Pin3, HIGH);
  digitalWrite(motor2Pin4, LOW);
  digitalWrite(enable2Pin, HIGH);
  delay(600);
  stopMotors();
}

void turnLeft() {
  // Girar a la izquierda
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(enable1Pin, HIGH);
  digitalWrite(motor2Pin3, LOW);
  digitalWrite(motor2Pin4, HIGH);
  digitalWrite(enable2Pin, HIGH);
  delay(600);
  stopMotors();
}