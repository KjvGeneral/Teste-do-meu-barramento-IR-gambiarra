const int pin[6] = {A8, A9, A10, A11, A12, A13};
int leitura[6];
int L[6];

void setup() {
  Serial.begin(9600);

  for(int i = 0; i < 6; i++)
  {
    pinMode(pin[i], INPUT);
    Serial.print("Pino ");
    Serial.print(pin[i]);
    Serial.println("foi configurado");
  }
  delay(500);
}

void loop() 
{
  Serial.print("Leitura: ");

  for(int i = 0; i < 6; i++)
    {
      leitura[i] = analogRead(pin[i]);

      if(leitura[i] < 250)
      {
        L[i] = 0;
      }
      if(leitura[i] > 250)
      {
        L[i] = 1;
      }

      Serial.print(" ");
      Serial.print(L[i]);
      Serial.print(" ");
    }
  Serial.println("");
  
}
