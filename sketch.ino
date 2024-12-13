#include <WiFi.h>
#include <HTTPClient.h>

#define led_azul 8 // Pino utilizado para controle do led azul
#define led_verde 2 // Pino utilizado para controle do led verde
#define led_vermelho 40 // Pino utilizado para controle do led vermelho
#define led_amarelo 9 // Pino utilizado para controle do led amarelo

const int button_pin = 6;  // Pino utilizado para controle do botão
int buttonState = HIGH;  // Variável de status do botão 
unsigned long lastDebounceTime = 0; // Configuração do Debounce
unsigned long debounceDelay = 50; // Configuração do Debounce

const int ldr_pin = 4;  // Pino do ldr
int ldr_status; // Variável de status do ldr
int threshold=800; // Variável que determina o threshold

void setup() {

  // Configuração inicial dos pinos para controle dos leds como OUTPUTs (saídas) do ESP32
  pinMode(led_azul,OUTPUT);
  pinMode(led_verde,OUTPUT);
  pinMode(led_vermelho,OUTPUT);
  pinMode(led_amarelo, OUTPUT);

  // Inicialização das entradas
  pinMode(button_pin, INPUT); // Inicia o botão como input
  digitalWrite(led_azul, LOW); 
  digitalWrite(led_verde, LOW);
  digitalWrite(led_vermelho, LOW);
  digitalWrite(led_amarelo, LOW);

  Serial.begin(9600); // Configuração para debug por interface serial entre ESP e computador com baud rate de 9600
}

void loop() {
  unsigned long currentMillis = millis();
  buttonState = digitalRead(button_pin);// Verifica estado do botão

  if ((currentMillis - lastDebounceTime) > debounceDelay) { //Adição da lógida do Debounce
    if (buttonState == LOW) {
        Serial.println("Botão pressionado!");
    } else {
        Serial.println("Botão não pressionado!");
    }
    lastDebounceTime = currentMillis; // Atualizar o tempo
}

  int ldr_status=analogRead(ldr_pin);

  if(ldr_status>=threshold) { //Inicialização do Modo Noturno
    Serial.print("Modo Noturno: ");
    Serial.println(ldr_status);
    digitalWrite(led_amarelo, HIGH);
    delay(1000);
    digitalWrite(led_amarelo, LOW);
    delay(1000);

  }else{
    Serial.print("Modo Convencional: "); //Inicialização do Modo Conevncional se a condição do Modo Noturno não for atendida
    Serial.println(ldr_status);
    digitalWrite(led_verde, HIGH);
    delay(3000);
    digitalWrite(led_verde, LOW);
    delay(3000);
    digitalWrite(led_amarelo, HIGH);
    delay(2000);
    digitalWrite(led_amarelo, LOW);
    delay(2000);

    digitalWrite(led_vermelho, HIGH);
        bool ledVermelhoAtivo = digitalRead(led_vermelho); //Variável para estado do Led vermelho
          if (ldr_status > threshold && ledVermelhoAtivo && buttonState == LOW) { //Condição para abrir o farol se o botão estiver pressionado, o Modo convencional ativado e o led vermelho aceso
              delay(1000);
              digitalWrite(led_verde, HIGH);
              Serial.print("Farol aberto!");
              delay(1000);
          }
    delay(5000);
    digitalWrite(led_vermelho, LOW);
    delay(5000);
    }
}