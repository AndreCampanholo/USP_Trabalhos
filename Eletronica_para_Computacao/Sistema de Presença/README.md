# Sistema de Presença
Projeto desenvolvido para a disciplina [SSC0180 - Eletrônica para Computação], ministrada pelo Professor Eduardo do Valle Simôes.

# Integrantes do Grupo 13
| Aluno | Nº USP |
|---|---|
| André Campanholo Paschoalini | 14558061 |
| Eduardo Poltroniere da Silva | 16862892 |
| Felipe Fabiano das Chagas | 16811922 |
| Pedro Hamamoto da Palma | 16818280 |

# Explicação do Projeto
Deve ser desenvolvido o software e o hardware de um projeto à escolha do grupo, que utilize Arduino/ESP32.<br>
Optamos por desenvolver um sistema de controle de presença através de tags e sensores RFID. Seu funcionamento ocorre da seguinte maneira:<br>
À cada tag foi associado um nome e uma turma, de maneira que cada tag representa um aluno. Aproximá-la ao sensor ativa o sinal sonoro (buzzer) e exibe as informações do aluno em questão, conferindo presença a este. Após cada tag ser escaneada, as informações do aluno em questão são apresentadas em um display OLED de padrão de comunicação i2C, onde ficam por 5 segundos. No monitor serial é possível consultar quais alunos estão presentes ao enviar a frase "Quantos alunos presentes", de modo que sejam exibidos no monitor seus nomes. O cadastro dos alunos deve ser feito através do código, alterando o array "students[]"  acrescentando o UID das tags novas. Para ler o UID de uma tag, deve-se retirar o comentário na função dumpNewUID() na main e escanear a tag nova(o UID dessa tag será mostrado no monitor serial).

# Lista dos Componentes
| Componente | Quantidade | Preço |
|---|---|---|
| Arduino UNO R3 | 1 | R$ 42,90 |
| Módulo RFID RC522 | 1 | R$ 9,50 |
| Display SSD1306 OLED 128X64 | 1 | R$ 32,90 |
| Buzzer | 1 | R$ 9,40 |
| Tag RFID | 3 | R$ 16,50 |
| Jumper | 10 | R$ 7,00 |
| Total |   | R$ 118,20 |

# Circuito do projeto

![Circuito no tinkercad](https://github.com/user-attachments/assets/374e0dd4-f5e7-4066-9805-f9aa9d971d74)

Descrição do circuito contendo a ligação de todos os pinos:
| Módulo/Função          | Pino no Módulo | Pino no Arduino Uno | Observações                |
|------------------------|----------------|---------------------|----------------------------|
| **RC522 RFID**         | SDA / SS       | D10                 | `SS_PIN` (SPI SS)          |
|                        | SCK            | D13                 | SPI CLK                    |
|                        | MOSI           | D11                 | SPI MOSI                   |
|                        | MISO           | D12                 | SPI MISO                   |
|                        | RST            | D9                  | `RST_PIN`                  |
|                        | 3 V3           | 3.3 V               | Alimentação 3.3 V          |
|                        | GND            | GND                 | Terra                      |
| **OLED SSD1306 (I²C)** | SDA            | A4                  | Linha de dados I²C         |
|                        | SCL            | A5                  | Clock I²C                  |
|                        | VCC            | 5 V                 | Módulo compatível 5 V      |
|                        | GND            | GND                 | Terra                      |
| **Buzzer passivo**     | +              | D7                  | `BUZZER_PIN`               |
|                        | −              | GND                 | Terra                      |

# Circuito no Protoboard - Vista Superior
![Circuito_Arduino1](https://github.com/user-attachments/assets/3ee80f93-8c2f-4cbb-aec0-f455463efbc0)

# Circuito no Protoboard - Vista Frontal
![Circuito_Arduino2](https://github.com/user-attachments/assets/2b4f12f5-6067-4ce5-ab4b-1ae93a61e205)


# Vídeo do funcionamento
Link do youtube: https://youtube.com/shorts/wO78POOzBGw?feature=share

# Código

```
//para cadastrar novos alunos, seguir os seguintes passos
//1 - descomentar a funcao dumpNewId() na main e mandar para a placa. agora, ao ler uma tag, será exibido o UID dela no serial
//2 - comentar novamente a funçao
//3 - adicionar um novo elemento no array Students[], seguindo o padrão dos já disponíveis e mudando as informaçoes(primeiro UID da tag, depois nome, turma e por fim deixar "false" no fim). sugerido copiar e colar uma linha e ir mudando as informacoes
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/* ----------- Pinos e periféricos ----------- */
#define SS_PIN       10
#define RST_PIN       9
#define BUZZER_PIN    7

/* ----------- OLED ----------- */
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT  64
#define OLED_ADDR    0x3C          // Endereço I2C padrão
// -1 porque o módulo de 4 pinos não possui pino RST dedicado
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

/* ----------- RFID ----------- */
MFRC522 rfid(SS_PIN, RST_PIN);

/* ----------- Estrutura do aluno ----------- */
struct Student {
  byte uid[4];
  const char* name;
  const char* section;
  bool present;
};

Student students[] = {    //editar essa parte conforme for necessário para cadastrar os alunos. deve-se escanear o UID das tags em outro programa e colocar os valores em hexadecimal no campo correspondente 
  {{0x36, 0xED, 0x49, 0x5C}, "PEDRO HAMAMOTO DA PALMA", "1", false},
  {{0xD9, 0x58, 0xD0, 0xC2}, "ANDRE PASCOALINI", "2", false},
  {{0x39, 0x17, 0xF5, 0xB9}, "EDUARDO BIUSP", "TURMA 1", false},
};

const int studentCount = sizeof(students) / sizeof(Student);

String inputCommand;

/* ====================================================== */
void setup() {
  Serial.begin(9600);

  pinMode(BUZZER_PIN, OUTPUT);
  SPI.begin();
  rfid.PCD_Init();

  Wire.begin();
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println(F("OLED não encontrado. Verifique a fiação."));
    while (true);                           // trava se falhar
  }

  display.setTextSize(1.00);                   // Fonte 6×8 px
  display.setTextColor(SSD1306_WHITE);
  showWelcome();

  Serial.println(F("Sistema pronto. Passe o cartão RFID ou digite 'Quantos alunos presentes'"));
}

void loop() {
  checkRFID();
  checkSerialInput();
 // dumpNewUID();     //para descobrir UID de uma nova tag, descomente essa linha e veja a tag ao escanear no monitor serial
}

/* ------------------- RFID ------------------- */
void checkRFID() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    return;

  beepBuzzer();

  for (int i = 0; i < studentCount; i++) {
    if (compareUID(rfid.uid.uidByte, students[i].uid)) {
      if (!students[i].present) {
        students[i].present = true;
        showOnOLED(students[i].name, students[i].section, true);    //funçao checa se aluno não estava presente e setta ele como presente. depois printa no serial nome do aluno e status
        Serial.print(F("Marcado Presente: "));
      } else {
        showOnOLED(students[i].name, students[i].section, false);
        Serial.print(F("Já marcado: "));
      }
      Serial.println(students[i].name);
      delay(5000);                // mantém mensagem 3 s
      showWelcome();
      break;
    }
  }
  rfid.PICC_HaltA();
}

bool compareUID(byte* a, byte* b) {
  for (int i = 0; i < 4; i++)
    if (a[i] != b[i]) return false;
  return true;
}

/* ------------------- OLED ------------------- */
void showOnOLED(const char* name, const char* section, bool firstTime) {  //configuração do display OLED para mostrar status do aluno
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print(F("Nome: "));
  display.println(name);
  display.print(F("Turma: "));
  display.println(section);
  display.print(F("Status: "));
  display.println(firstTime ? F("Presente") : F("Ja escaneado"));
  display.display();
}

void showWelcome() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(F("Sistema de Presenca"));
//  display.println(F("      System"));
  display.display();
}

/* ------------------- Serial ------------------- */
void checkSerialInput() {   //Checa se comando para mostrar chamada é dado
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      inputCommand.trim();
      if (inputCommand.equalsIgnoreCase("Quantos alunos presentes")) {
        showAttendance();
      }
      inputCommand = "";
    } else {
      inputCommand += c;
    }
  }
}

void showAttendance() {
  Serial.println(F("---- Relatório de presença ----"));   //Mostra a lista de chamada ao receber o comando no serial
  for (int i = 0; i < studentCount; i++) {
    Serial.print(students[i].name);
    Serial.print(" - ");
    Serial.println(students[i].present ? "Presente" : "Ausente");
  }
  Serial.println(F("---------------------------"));
}

/* ------------------- Buzzer ------------------- */
void beepBuzzer() {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(200);
  digitalWrite(BUZZER_PIN, LOW);
}


void dumpNewUID() {
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {   //comando para mostrar UID de uma tag. Usado para configurar tags
    Serial.print(F("{"));
    for (byte i = 0; i < rfid.uid.size; i++) {
      Serial.print(F("0x"));
      if (rfid.uid.uidByte[i] < 0x10) Serial.print('0'); // zero à esquerda
      Serial.print(rfid.uid.uidByte[i], HEX);
      if (i < rfid.uid.size - 1) Serial.print(F(", "));
    }
    Serial.println(F("},"));
    rfid.PICC_HaltA();
  }
}
```
