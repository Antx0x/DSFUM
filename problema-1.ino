
int ledPins[] = {8, 9, 10, 11, 12, 13}; 
int numLeds = 6;

void setup() {
 
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {

  for (int numar = 0; numar <= 63; numar++) {
    
    for (int bit = 0; bit < numLeds; bit++) {
   
      int stareBit = bitRead(numar, bit);
      
      if (stareBit == 1) {
        digitalWrite(ledPins[bit], HIGH); 
      } else {
        digitalWrite(ledPins[bit], LOW); 
      }
    }
    

    delay(1000); 
  }
}