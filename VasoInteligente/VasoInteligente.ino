// Vaso Inteligente
// C++ code
//
#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

const int oneWirePin = 8;
const int ledrojo = 7;
const int ledazul = 5;
const int ledverde = 6;
const int analogInPin = A0; 
int sensorValue = 0;
byte salida = 10;
const int pinBuzzer = 3;

OneWire oneWireBus(oneWirePin);
DallasTemperature sensor(&oneWireBus);

void setup()
{
pinMode(LED_BUILTIN, OUTPUT);
pinMode(8, INPUT);
pinMode(7, OUTPUT);
pinMode(6, OUTPUT);
pinMode(5, OUTPUT);
Serial.begin(9600);
sensor.begin(); 

  // Inicializamos comunicación serie
Serial.begin(9600);
 
  // Comenzamos el sensor DHT
dht.begin();
 
}

void loop() {
   Serial.println("\n Siguiente lectura: ");
   sensor.requestTemperatures();

   Serial.print("Temperatura en sensor: ");
   const int temp = sensor.getTempCByIndex(0);
   Serial.print(temp);
   Serial.println(" ºC");
   
  delay(1000); 

  if(temp<16){
    digitalWrite(ledrojo, LOW);
    digitalWrite(ledverde, LOW);
    digitalWrite(ledazul, HIGH);
  }
  else if(temp>=16 and temp<28){
    digitalWrite(ledrojo, LOW);
    digitalWrite(ledverde, HIGH);
    digitalWrite(ledazul, LOW);
  }
  else{
    digitalWrite(ledrojo, HIGH);
    digitalWrite(ledverde, LOW);
    digitalWrite(ledazul, LOW);
  }

 sensorValue = analogRead(analogInPin); 
 
 Serial.print("Sensor cubierto = " ); 
 Serial.print(sensorValue/10); 
 Serial.println("%");
 
 delay(1000); 

 if(sensorValue>300){
  analogWrite(pinBuzzer, HIGH);
  delay(5000);
  analogWrite(pinBuzzer, LOW);
  delay(20000);
 }
 else{
  analogWrite(pinBuzzer, LOW);
 }

   // Esperamos 2 segundos entre medidas
delay(2000);

// Leemos la humedad relativa
float h = dht.readHumidity();
// Leemos la temperatura en grados centígrados (por defecto)
float t = dht.readTemperature();
// Leemos la temperatura en grados Fahreheit
float f = dht.readTemperature(true);

// Comprobamos si ha habido algún error en la lectura
if (isnan(h) || isnan(t) || isnan(f)) {
  Serial.println("Error obteniendo los datos del sensor DHT11");
  return;
}

// Calcular el índice de calor en grados centígrados
float hic = dht.computeHeatIndex(t, h, false);

Serial.print("Humedad: ");
Serial.print(h);
Serial.print(" %\t");
Serial.print("Temperatura: ");
Serial.print(t);
Serial.print(" C ");
}