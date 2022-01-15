
#include <DHT.h> 
#include <SPI.h>
#include <SD.h>
int DHTPIN = 2;
const int chipSelect = 10;
unsigned long Secs=0;
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);
File dataFile;

void setup() {
  Serial.begin(9600);
  while (!Serial) {}
  dht.begin();
  Serial.print("inizio");
  if (!SD.begin(chipSelect)) {
    Serial.println("Non hai messo la scheda SD");
    return;
  }
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  Serial.println("continuo");
  if (dataFile) {
    Serial.print("sto procedendo...");
    dataFile.println("tempo, umidita, temperatura");
    dataFile.close();
    Serial.println("ho finito");
  }
}

void loop() {
  String dataString = "";
  int h = dht.readHumidity();
  int t = dht.readTemperature(false); 
  unsigned long Secs=millis();

  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println(String(Secs)+","+String(h)+","+String(t));
    dataFile.close();
    Serial.println(String(Secs)+","+String(h)+","+String(t));
    delay(4000);  
  }
  else {
    Serial.println("non riesco ad aprire il file dei valori");
  }
}
/* creato da BENSAIKOUK MOHAMED 4E
