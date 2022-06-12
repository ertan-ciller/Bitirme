
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <dht11.h> // dht11 kütüphanesini ekliyoruz.
#define DHT11PIN 4 // DHT11PIN olarak Dijital 2"yi belirliyoruz.
dht11 DHT11;
int sicaklik = 25, nem = 50, esik_degeri = 25;

// OKUNABİLİR VERİLER
// SICAKLIK     - DHT11.temperature
// NEM          - DHT11.humidity
// ÇİĞ NOKTASI  - DHT11.fahrenheit()
// KELVİN       - DHT11.kelvin()
// ÇİĞ NOKTASI  - DHT11.dewPoint()


char auth[33] = "IcqNMEOHpbF9bPntUzQudAl6H1dDvQhx";
char ssid[33] = "MORUK2.4";
char pass[33] = "MorukS@14";


void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
}


BLYNK_READ(V0) {
  DHT11.read(DHT11PIN);
  sicaklik = DHT11.temperature;
  Serial.println("Sıcaklık: " + String(sicaklik));
  
  Blynk.virtualWrite(V0, sicaklik);
  
  if (sicaklik >= esik_degeri)
  {
    digitalWrite(5, LOW);   // röleyi çektir
    delay(500);
    Serial.println("low verildi");
  }
  else
  {
    digitalWrite(5, HIGH);  // röleyi söndür
    delay(500);
    Serial.println("high verildi");
  }
}

BLYNK_READ(V1) {
  DHT11.read(DHT11PIN);
  nem = DHT11.humidity;
  Serial.println("Nem: " + String(nem));
  
  Blynk.virtualWrite(V1, nem);
}

BLYNK_WRITE(V2){  // This function gets called each time something changes on the widget
  esik_degeri = param.asInt();  // This gets the 'value' of the Widget as an integer
  Serial.println("esik_degeri: " + String(esik_degeri));
  
}
