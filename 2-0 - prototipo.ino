// Código prototipo para PID do robo busca e resgate 2026
// Esquema de peso e contagem de sensores e da esquerda para a direita
// Usei o gemini para me ensinar PID, ainda não testei então tem muita coisa ora mudar..

// ---- CONFIGURAÇÃO DA SHIELD PONTE H MONSTER ----

//      Canal A
const int A_ho  = 4;  // -> Sentido Horário
const int A_ah  = 9;  // -> Sentido Ant-horário
const int A_pwm = 6;  // -> Velocidade - pwm do motor
const int A_En  = A1; // -> Pino de enable do canal A

//      Canal B
const int B_ho  = 7;  // -> Sentido Horário
const int B_ah  = 8;  // -> Sentido Ant-horário
const int B_pwm = 5;  // -> Velocidade - pwm do motor
const int B_En  = A0; // -> Pino de enable do canal B


int MAXI_VEL = 255;
int BASE_VEL = 155;

float Kp;
float Kd;
float Ki;

int erro = 0;
int erroAnterior = 0; // erroAnterior = Variação do erro - erro atual
int somaErro = 0;     // somaErro = integralAnterior 

float PID;            // retorndo do calculo completo


// Desvio para a esquerda e NEGATIVO
// Desvio para a direita e POSITIVO

// Proporcional = Kp * erro
// Integral: IntegralAnterior * erro -> I = Ki * erro
// Derivada: variação = erroAtual - erroAnterior -> D = Kd * erro


// Peso dos sensores: ((-1)+(+1))/2 = 0
// S1:-5, S2:-3, S3:-1, S4:+1, S5:+3, S6:+5
const int monster[8] = {A_ah, A_ho, A_pwm, B_ah, B_ho, B_pwm, A_En, B_En}
const int sensores[6] = {1, 2, 3, 4, 5, 6};
const int peso[6] = {-5, -3, -1, 1, 3, 5};

void setup(){
    Serial.begin(9600);

    for(int i = 0; i < 6; i++){
        pinMode(sensores[i], INPUT);
        Serial.print("O pino ");
        Serial.print(sensores[i]);
        Serial.print(" foi configurado com sucesso!");
    }
    for (int i = 0; i < 8; i++) {
        pinMode(monster, OUTPUT);
    }
    
    digitalWrite(A_En, HIGH);
    digitalWrite(B_En, HIGH);

}

void loop(){
    erro = erroCal();
    PID  = calPID();

    int velEsq = BASE_VEL + PID;
    int velDir = BASE_VEL - PID;

    Motor(HIGH, LOW, velEsq, HIGH, LOW, velDir);

    Serial.print("PID: ");
    Serial.print(PID);
    Serial.print(" | Motores: ");
    Serial.print(velEsq);
    Serial.print(" ");
    Serial.println(velDir);
}

// ================= FUNÇÔES ====================


// Calculo do erro
/* 
 Fluxo: analisa qual e o sensor esta lendo a linha e analisa a posição dele
no vetor e aplica no peso respectivo
 Em seguida pergunta se todos os sensores que foram ativados e > 0, e dividir
 pelos pesos para retornar um valor valido. E caso tudo seja falsi perguntamos
o erroAnterior e > 0, retorna um valor de 5 ou -5, caso perda linha.

*/
int erroCal(){
    int somaPesos = 0;
    int sensoresAt = 0;

    for(int i = 0; i < 6; i++){
        int leitura = digitalRead(sensores[i]);

        if(leitura == HIGH) {
            somaPesos += peso[i]; // armazena o valor de cada peso/somando
            sensoresAt++;         // esse valor e usado pra saber quantos sehore leram
        }
    }

    if(sensoresAt > 0){
        return somaPesos/sensoresAt; // retorna o peso equivalente
    }
    else(erroAnterior > 0) ? 6 : -6; // pergunta se erro anterior maior que 0, se sim returna 5 se não -5
    // para o robot girar para um sentido com tudo ate encontrar a linha
}

// Tramanto dos termos de PID
// Proporcional = P = Kp * erro
// Integral: somaErro = IntegralAnterior * erro -> I = Ki * somaErro
// Derivada: variação = erroAtual - erroAnterior -> D = Kd * vairiação

float calPID(){
    // chamamos o calculo do erro para assim conhecermos oque estamos chamando de erro
    
    erro = erroCal(); // erro atual

    float P = Kp * erro;

    somaErro += erro; // acumula o erro = integralAnterior
    float I = Ki * erro;

    float variacao = (erro - erroAnterior);
    float D = Kd * variacao;

    return (P + I + D);
}

//    Lado Esquerdo    velocidade | Lado Direito       Velocidade
void Motor(bool in1, bool in2, float pwm_A, bool in3, bool in4, float pwm_B){

  //           Canal A
  digitalWrite(A_ho, in1);
  digitalWrite(A_ah, in2);
  digitalWrite(A_pwm, pwm_A);

  //           Canal B
  digitalWrite(B_ho, in3);
  digitalWrite(B_ah, in4);
  digitalWrite(B_pwm, pwm_B);
}

