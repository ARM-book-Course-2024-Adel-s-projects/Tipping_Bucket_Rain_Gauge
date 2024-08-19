#define SIM800L_TX_PIN 17  // Pin TX de ESP32 conectado al RX del SIM800L
#define SIM800L_RX_PIN 16  // Pin RX de ESP32 conectado al TX del SIM800L

void setup() {
  // Inicia la comunicación serial para depuración a través de USB
  Serial.begin(9600);
  
  // Inicia la comunicación serial con el SIM800L
  Serial2.begin(9600, SERIAL_8N1, SIM800L_RX_PIN, SIM800L_TX_PIN);

  Serial.println("ESP32 Serial Communication with SIM800L Started");

  // Espera unos segundos para que el SIM800L se estabilice
  delay(3000);

  // Envía un comando AT inicial y espera la respuesta
  sendATCommand("AT");
}

void loop() {
  // Aquí puedes agregar más comandos AT o procesos adicionales
  if(Serial.available()) {
    String command = Serial.readString();
    if ( command.indexOf("CIPSEND") != -1) {
      sendATCommand(command);
      Serial2.print("Hello server!");
      Serial2.write(0x1A);
      while(!Serial.available()) {
        ;
      }
      String text = Serial.readString();
      Serial.write("Cerrando!");
      Serial2.print(text);
      Serial2.write(0x1A);
      Serial2.println("");
    } else {
      sendATCommand(command);
    }
  } else if(Serial2.available()) {
    String response = Serial2.readString();
    Serial.print("Received: ");
    Serial.println(response);
  }
}

// Función para enviar un comando AT y recibir la respuesta
void sendATCommand(String command) {
  // Envía el comando AT al SIM800L
  Serial2.println(command);
  Serial.print("Sent: ");
  Serial.println(command);

  // Espera un momento para la respuesta del SIM800L
  delay(5000);

  // Lee la respuesta del SIM800L
  if (Serial2.available()) {
    String response = Serial2.readString();
    Serial.print("Received: ");
    Serial.println(response);
  } else {
    Serial.println("No response received.");
  }
}
