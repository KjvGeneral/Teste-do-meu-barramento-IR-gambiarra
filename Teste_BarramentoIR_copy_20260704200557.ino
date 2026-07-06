const int pin[6] = {A8, A9, A10, A11, A12, A13};
int leitura[6];

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
      leitura[i] = analogRead(pin[i]);  // armazena valores de 0 -1023 -- 8bits
      /*
      // trasnforma esses valores para bitnario para facilitar o segue linha
      // No meu caso dos sensores entre escuro e claro (braco e preto) meu sensor lia de ~230 ate ~370
      // então eu tranformei em binario para fazer uma forma simplifcada para fazer um segue linha
      // Vou estudar como faz para generalizar isso, como calibrar os sensores com valores minimos e maximos
      // para garar um binario ou algo assim para fazer o tratamento para fazer um segue linha ou um PID para
      // o mesmo... 
      // OBS: ainda estou estudando pouco a pouco, errando bastante e procurando ajuda
      
      if(leitura[i] < 250)
      {
        leitura[i] = 0;
      }
      if(leitura[i] > 250)
      {
        leitura[i] = 1;
      }
      */
      Serial.print(" ");
      Serial.print(leitura[i]);
      Serial.print(" ");
    }
  Serial.println("");
  
}
