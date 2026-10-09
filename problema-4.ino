int led = 9;            
int brightness = 0;     
int fadeAmount = 5;     
 
unsigned long timpPrecedent = 0; 
int interval = 30;                

void setup() {
  pinMode(led, OUTPUT);
  
   Serial.begin(9600);
  Serial.println("(Numere mici = rapid / Numere mari = lent)");
}

void loop() {
   if (Serial.available() > 0) {
    int valoarePrimita = Serial.parseInt(); 
    
     if (valoarePrimita > 0) {
      interval = valoarePrimita;  
      
      Serial.print("timpul de asteptare: ");
      Serial.print(interval);
      Serial.println(" milisecunde.");
    }
    
     while(Serial.available() > 0) {
      Serial.read();
    }
  }

   unsigned long timpCurent = millis(); 
  
   if (timpCurent - timpPrecedent >= interval) {
    
     timpPrecedent = timpCurent;   
     analogWrite(led, brightness);
     brightness = brightness + fadeAmount;
    
     if (brightness <= 0 || brightness >= 255) {
      fadeAmount = -fadeAmount;
    }
  }
}