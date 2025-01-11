#include "BluetoothSerial.h"
#include "esp_bt.h" 
BluetoothSerial ESP_BT;
 
const int LED = 2;
String receive;
int i = 0;
int j = 100;

void setup() {
  ESP_BT.begin("Esp32");
  Serial.begin(115200);
  Serial.println("Bluetooth iniciado!");

  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
}

void loop() {

  // Verifica se há dados disponíveis para leitura
  if (ESP_BT.available()) {
    receive = ESP_BT.readString();
    Serial.println(receive);
  }

  // Verifica se há dados disponíveis para enviar do Serial
  if (Serial.available()) {
    receive = Serial.readString();
    ESP_BT.println(receive);
  }

  // Controla o LED baseado nos comandos recebidos
  if (receive == "LIGA") {
    digitalWrite(LED, HIGH);
    Serial.println("LED_ON");

    if (ESP_BT.connected()) {
    i++;
    j--;
    ESP_BT.print(String(i) + "|" + String (j)); // Enviar mensagem apenas quando conectado
    Serial.print(String(i) + "|" + String (j));
  }
  }
  else if (receive == "DESLIGA") {
    digitalWrite(LED, LOW);
    Serial.println("LED_OFF");
  }

  // Limpa a variável 'receive' para a próxima iteração
  receive = "";
}
