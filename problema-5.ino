const int pinIesire = 8; 

unsigned long perioadaSemnal = 2000; 
unsigned long timpHigh = 0;
unsigned long timpLow = perioadaSemnal;
unsigned long timpPrecedent = 0;

bool starePin = false;
float tensiuneDorita = 0.0;

void setup() {
  pinMode(pinIesire, OUTPUT);
  Serial.begin(9600);
 }

void loop() {
  if (Serial.available() > 0) {
    float valoarePrimita = Serial.parseFloat();
    
    while(Serial.available() > 0) Serial.read(); 

    if (valoarePrimita >= 0.0 && valoarePrimita <= 5.0) {
      tensiuneDorita = valoarePrimita;
      
      float dutyCycle = tensiuneDorita / 5.0; 
      
      timpHigh = perioadaSemnal * dutyCycle;
      timpLow = perioadaSemnal - timpHigh;
      
       Serial.print(tensiuneDorita);
      Serial.println(" V");
    }
  }

  if (tensiuneDorita == 0.0) {
    digitalWrite(pinIesire, LOW); 
  } 
  else if (tensiuneDorita == 5.0) {
    digitalWrite(pinIesire, HIGH); 
  } 
  else {
    unsigned long timpCurent = micros();
    
    if (starePin == true) {
      if (timpCurent - timpPrecedent >= timpHigh) {
        starePin = false;
        digitalWrite(pinIesire, LOW);
        timpPrecedent = timpCurent;
      }
    } else {
      if (timpCurent - timpPrecedent >= timpLow) {
        starePin = true;
        digitalWrite(pinIesire, HIGH);
        timpPrecedent = timpCurent;
      }
    }
  }
}