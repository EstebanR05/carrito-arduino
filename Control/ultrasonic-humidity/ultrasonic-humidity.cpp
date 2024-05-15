#include "DHTesp.h"                  // Incluir la librería para el sensor DHT
#include <Adafruit_Sensor.h>         // Incluir la librería para los sensores Adafruit
#include <ESP32Servo.h>              // Incluir la librería para el control de servos en ESP32
#include <BluetoothSerial.h>         // Incluir la librería para la comunicación Bluetooth

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to enable it
#endif

int pinDHT = 4;                      // Pin al que está conectado el sensor DHT
int LED_BUILTIN = 2;                 // Pin del LED integrado
char ejemplo;                        // Variable para almacenar un carácter recibido por Bluetooth

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
//#define DHTPIN 4
#define DHTTYPE DHT11

// Crear instancia del sensor de humedad y temperatura
DHTesp dht;

// Crear instancia del servo
Servo servo;

// Definición de variables
long duration;
int distance;
float humedad;

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
  
  // Configurar pines del sensor de ultrasonido
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Inicializar el sensor de humedad y temperatura
  dht.setup(pinDHT, DHTesp::DHT11);
  
  // Inicializar el servo
  servo.attach(21);                 // Conectar el servo al pin 21
  servo.write(90);                  // Posición inicial del servo
  
  // Inicializar la comunicación serial
  Serial.begin(115200);
  
  // Inicializar la comunicación Bluetooth
  SerialBT.begin("ESP32test");       // Establecer el nombre del dispositivo Bluetooth
}

void Temp() {
  // Obtener los datos de temperatura y humedad del sensor DHT
  TempAndHumidity data = dht.getTempAndHumidity();
  
  // Crear las cadenas de texto con los valores de temperatura y humedad
  String temperatureString = "Temperatura: " + String(data.temperature, 2) + "°C";
  String humidityString = "Humedad: " + String(data.humidity, 1) + "%";

  // Imprimir los valores de temperatura y humedad en el monitor serial
  Serial.println(temperatureString);
  Serial.println(humidityString);
  
  // Si hay una conexión Bluetooth establecida, enviar los datos también por Bluetooth
  if (SerialBT.connected()) {
    SerialBT.println(temperatureString);
    SerialBT.println(humidityString);
  }
  
  delay(2000);
}

void loop() {
  Temp();                           // Llamar a la función Temp para obtener y enviar los datos de temperatura y humedad
  
  // Medir la distancia con el sensor de ultrasonido
  distance = measureDistance();
  
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

void moveForward() {
  // Mover el motor hacia adelante
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(enable1Pin, HIGH);
  digitalWrite(motor2Pin3, HIGH);
  digitalWrite(motor2Pin4, LOW);
  digitalWrite(enable2Pin, HIGH);
  
  delay(2000);
  
  // Detener el motor
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(enable1Pin, LOW);
  digitalWrite(motor2Pin3, LOW);
  digitalWrite(motor2Pin4, LOW);
  digitalWrite(enable2Pin, LOW);
}

void moveBackward() {
  // Mover el motor hacia atrás
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(enable1Pin, HIGH);
  digitalWrite(motor2Pin3, LOW);
  digitalWrite(motor2Pin4, HIGH);
  digitalWrite(enable2Pin, HIGH);
  
  delay(2000);
  
  // Detener el motor
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(enable1Pin, LOW);
  digitalWrite(motor2Pin3, LOW);
  digitalWrite(motor2Pin4, LOW);
  digitalWrite(enable2Pin, LOW);
}

void turnRight() {
  // Girar a la derecha
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(enable1Pin, HIGH);
  digitalWrite(motor2Pin3, HIGH);
  digitalWrite(motor2Pin4, LOW);
  digitalWrite(enable2Pin, HIGH);
  
  delay(400);
  
  // Detener el motor
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(enable1Pin, LOW);
  digitalWrite(motor2Pin3, LOW);
  digitalWrite(motor2Pin4, LOW);
  digitalWrite(enable2Pin, LOW);
}

void turnLeft() {
  // Girar a la izquierda
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(enable1Pin, HIGH);
  digitalWrite(motor2Pin3, LOW);
  digitalWrite(motor2Pin4, HIGH);
  digitalWrite(enable2Pin, HIGH);
  
  delay(400);
  
  // Detener el motor
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(enable1Pin, LOW);
  digitalWrite(motor2Pin3, LOW);
  digitalWrite(motor2Pin4, LOW);
  digitalWrite(enable2Pin, LOW);
}

int measureDistance() {
  // Enviar un pulso al sensor ultrasónico para medir la distancia
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Medir la duración del pulso de eco
  duration = pulseIn(echoPin, HIGH);
  
  // Calcular la distancia en base a la duración del pulso
  int distance = duration * 0.034 / 2;
  
  return distance;
}

void rotateServo() {
  // Rotar el servo en base a la distancia medida
  int angle = map(distance, 0, 100, 50, 150);
  servo.write(angle);
  delay(15);
}