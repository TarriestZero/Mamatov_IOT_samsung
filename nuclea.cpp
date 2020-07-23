#include <Arduino.h>

#define device_number 1


int pinA0 = A0;                    // Пин к которому подключен A0
int pinD0 = A1;                    // Пин к которому подключен D0



//------------------------------------------



void sending(int nois){
  int pack = 0;
  if ((nois / 100) == 0) pack = (nois + (100*device_number));
  else pack = (nois + (1000*device_number));
  Serial.print(pack); // первое число номер девайса, остальные значение шума
}

void setup() {
  Serial.begin(9600);
  pinMode (pinA0, INPUT);         
  pinMode (pinD0, INPUT);          
  pinMode(LED_BUILTIN,OUTPUT);
}




void loop() {
  int xA0, xD0;                     // Создаем переменные
  xD0 = digitalRead (pinD0); 
  
  if (xD0 == HIGH) sending(analogRead(pinA0));  
  
  sending(get_noise());
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
