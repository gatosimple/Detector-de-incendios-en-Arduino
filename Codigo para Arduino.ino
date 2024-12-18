#include <LiquidCrystal.h>

const int smokeSensorPin = A0; // Pin analógico para el sensor de humo
const int ledPin = 9; // Pin digital para el LED
const int piezoPin = 8; // Pin digital para el zumbador piezoeléctrico

// Configuración del LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Variable para el estado de detección de humo:
boolean smokeDetected = false; // Inicialmente se asume que no se ha detectado humo

// Variables para el parpadeo del LED:
unsigned long previousMillis = 0; // Se establece en 0 porque no ha ocurrido ningún evento aún
const long interval = 100; // Intervalo de 0.1 segundos para el parpadeo del LED

void setup() {
// Configuración de pines de salida:
pinMode(ledPin, OUTPUT);
pinMode(piezoPin, OUTPUT);
// Inicialización del LCD:
lcd.begin(16, 2);
lcd.clear(); // Borra cualquier mensaje anterior en el LCD
}
void loop() {
// Lectura del valor del sensor de humo:
int smokeLevel = analogRead(smokeSensorPin);

// Verificación del nivel de humo:
if (smokeLevel > 950) { // Ajusta este umbral según las características de tu sensor de humo
if (!smokeDetected) {
digitalWrite(ledPin, HIGH); // Enciende el LED si se detecta humo por primera vez
Proyecto Final 24

smokeDetected = true;
}
// Activa el zumbador
tone(piezoPin, 1000);

// Configuración y visualización en el LCD:
// Establecer la posición del cursor en la primera fila (fila 0) del LCD
lcd.setCursor(0, 0);
lcd.print("Alerta de humo:"); // Muestra el mensaje “Alerta de humo”
// Establecer la posición del cursor en la segunda fila (fila 1) del LCD
lcd.setCursor(0, 1);
lcd.print("EVACUAR"); // Muestra el mensaje "EVACUAR" en la segunda fila

// Parpadeo intermitente del LED:
unsigned long currentMillis = millis(); // Obtiene el tiempo actual en milisegundos

// Verifica si ha pasado el intervalo desde el último parpadeo:
if (currentMillis - previousMillis >= interval) {
previousMillis = currentMillis; // Actualiza el tiempo del último parpadeo
// Cambia el estado del LED en cada intervalo:
if (digitalRead(ledPin) == HIGH) { // Verifica si el LED está actualmente encendido
digitalWrite(ledPin, LOW); // Apaga el LED si estaba encendido
} else {
digitalWrite(ledPin, HIGH); // Enciende el LED si estaba apagado
}
}
} else {
// Apaga el LED y detiene el zumbador si no hay humo:
digitalWrite(ledPin, LOW); // Apaga el LED
noTone(piezoPin); // Detiene el zumbador
lcd.clear(); // Borra el mensaje en el LCD
smokeDetected = false; // Restablece la detección de humo a falso
}
}