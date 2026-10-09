int ledPins[] = {8, 9, 10, 11, 12, 13}; 
int numLeds = 6;

void setup() {
  Serial.begin(9600);
  
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  if (Serial.available() > 0) {
    
    int valoare = Serial.parseInt(); 
    
    if (valoare >= 0 && valoare <= 63) {
      
      Serial.print("Am primit valoarea: ");
      Serial.println(valoare);

      for (int bit = 0; bit < numLeds; bit++) {
        int stareBit = bitRead(valoare, bit);
        
        if (stareBit == 1) {
          digitalWrite(ledPins[bit], HIGH);
        } else {
          digitalWrite(ledPins[bit], LOW);
        }
      }
    }
    
    while(Serial.available() > 0) {
      Serial.read();
    }
  }
}