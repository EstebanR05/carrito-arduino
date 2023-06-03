#include <DHT.h>        // Incluir la librería DHT para el sensor de humedad y temperatura
#include <ESP32Servo.h> // Incluir la librería ESP32Servo para controlar el servo

// Definición de pines del controlador de motor L298N
int motor1Pin1 = 27;
int motor1Pin2 = 26;
int enable1Pin = 14;
int motor2Pin3 = 33;
int motor2Pin4 = 32;
int enable2Pin = 25;

// Definición de pines del sensor de ultrasonido
int trigPin = 18;
int echoPin = 19;

// Definición de pines del sensor de humedad y temperatura (DHT11 o DHT22)
#define DHTPIN 4
#define DHTTYPE DHT11

// Crear instancia del sensor de humedad y temperatura
DHT dht(DHTPIN, DHTTYPE);

// Crear instancia del servo
Servo servo;

// Definición de variables
long duration;
int distance;
float humedad;

void setup() {
  // Configurar pines de salida para el controlador de motor L298N
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  pinMode(motor2Pin3, OUTPUT);
  pinMode(motor2Pin4, OUTPUT);
  pinMode(enable2Pin, OUTPUT);
  
  // Configurar pines del sensor de ultrasonido
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Inicializar el sensor de humedad y temperatura
  dht.begin();
  
  // Inicializar el servo
  servo.attach(21); // Pin 21 para el servo
  servo.write(90); // Posición inicial del servo
}

void loop() {
  // Medir la distancia con el sensor de ultrasonido
  distance = measureDistance();
  
  // Leer la humedad
  humedad = dht.readHumidity();
  
  // Si la distancia es menor a 20 cm, retroceder y girar hasta que la distancia sea mayor a 20 cm
  if (distance < 20) {
    // Retroceder
    moveBackward();
    delay(1000);
    
    // Girar a la derecha
    turnRight();
    delay(1000);
    
    // Girar a la izquierda
    // turnLeft();
    // delay(1000);
  }
  
  // Avanzar
  moveForward();
  
  // Controlar el servo
  rotateServo();
  
  // Guardar los datos en un archivo Excel o en la nube
  saveDataToCloud();
}

void moveForward() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(enable1Pin, HIGH);
  digitalWrite(motor2Pin3, HIGH);
  digitalWrite(motor2Pin4, LOW);
  digitalWrite(enable2Pin, HIGH);
}

void moveBackward() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(enable1Pin, HIGH);
  digitalWrite(motor2Pin3, LOW);
  digitalWrite(motor2Pin4, HIGH);
  digitalWrite(enable2Pin, HIGH);
}

void turnRight() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(enable1Pin, HIGH);
  digitalWrite(motor2Pin3, HIGH);
  digitalWrite(motor2Pin4, LOW);
  digitalWrite(enable2Pin, HIGH);
}

void turnLeft() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(enable1Pin, HIGH);
  digitalWrite(motor2Pin3, LOW);
  digitalWrite(motor2Pin4, HIGH);
  digitalWrite(enable2Pin, HIGH);
}

int measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  
  return distance;
}

void rotateServo() {
  int angle = map(distance, 0, 100, 50, 150);
  servo.write(angle);
  delay(15);
}

void saveDataToCloud() {
  // Aquí puedes agregar el código para enviar los datos de humedad a la nube o guardarlos en un archivo Excel
  // Por ejemplo, podrías enviar los datos a través de WiFi utilizando protocolos como MQTT o HTTP
  // También podrías guardar los datos en una tarjeta SD si tu ESP32 tiene una ranura para tarjetas SD
  // Dependiendo de la plataforma o servicio en la nube que utilices, el código específico puede variar
}