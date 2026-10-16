int pinActiv = 8; 
String animatie = "off";
unsigned long durata = 1000;

int luminozitate = 0; 
unsigned long perioadaPWM = 2000; 

void setup() {
  Serial.begin(9600);
  
  for(int i = 8; i <= 13; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  if (Serial.available() > 0) {
    pinActiv = Serial.parseInt();           
    Serial.read();                          
    animatie = Serial.readStringUntil(','); 
    durata = Serial.parseInt();             
  }

  unsigned long timpScurs = millis() % durata; 

  if (animatie == "off") {
    luminozitate = 0; 
  } 
  else if (animatie == "blink") {
    if (timpScurs < durata / 2) {
      luminozitate = 255; 
    } else {
      luminozitate = 0;  
    }
  } 
  else if (animatie == "fadein") {
    luminozitate = (timpScurs * 255) / durata;
  } 
  else if (animatie == "fadeout") {
    luminozitate = 255 - ((timpScurs * 255) / durata); 
  } 
  else if (animatie == "fadeinout") {
    int jumatate = durata / 2;
    
    if (timpScurs < jumatate) {
      luminozitate = (timpScurs * 255) / jumatate;
    } else {
      luminozitate = 255 - (((timpScurs - jumatate) * 255) / jumatate); 
    }
  }


  unsigned long timpCurent_us = micros();
  unsigned long progresCiclu = timpCurent_us % perioadaPWM;
  
  unsigned long timpAprins = (luminozitate * perioadaPWM) / 255;

  if (progresCiclu < timpAprins) {
    digitalWrite(pinActiv, HIGH);
  } else {
    digitalWrite(pinActiv, LOW);
  }
}