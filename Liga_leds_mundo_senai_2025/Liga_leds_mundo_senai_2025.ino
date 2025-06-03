#include <WiFi.h>

const char *ssid = "mundo_senai";
const char *password = "mundosenai2025";

NetworkServer server(80);
bool semaforoLigado = false;
unsigned long tempoAnterior = 0;
int estadoSemaforo = 0;


void setup() {
  Serial.begin(115200);
  pinMode(13, OUTPUT);  // set the LED pin mode
  pinMode(12, OUTPUT);  // set the LED pin mode
  pinMode(14, OUTPUT);  // set the LED pin mode

  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  NetworkClient client = server.accept();  // listen for incoming clients

  if (client) {                     // if you get a client,
    Serial.println("New Client.");  // print a message out the serial port
    String currentLine = "";        // make a String to hold incoming data from the client
    while (client.connected()) {    // loop while the client's connected
      if (client.available()) {     // if there's bytes to read from the client,
        char c = client.read();     // read a byte, then
        Serial.write(c);            // print it out the serial monitor
        if (c == '\n') {            // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // Início do HTML
            client.print("<!DOCTYPE HTML>");
            client.print("<html>");
            client.print("<head>");
            client.print("<meta charset='UTF-8'>");
            client.print("<title>Controle de LEDs ESP32</title>");
            client.print("<meta name='viewport' content='width=device-width, initial-scale=1'>");
            // CSS Inline para estilização
            client.print("<style>");
            // Azul escuro do banner, ou um tom que harmonize. O banner tem gradientes.
            // Vamos usar um azul escuro sólido que combine.
            client.print("body { font-family: Arial, sans-serif; background-color: #0A182E; /* Azul bem escuro */ margin: 0; padding: 20px; display: flex; flex-direction: column; align-items: center; min-height: 100vh; }");
            client.print(".header-image { display: block; margin: 0 auto 30px auto; max-width: 100%; width: 700px; /* Ajuste a largura conforme necessário, até o max-width da imagem original */ height: auto; border-radius: 8px; box-shadow: 0 4px 8px rgba(0,0,0,0.3); }");
            client.print("h2 { color: #E0E0E0; /* Cor clara para contraste com fundo escuro */ margin-bottom: 30px; text-align: center; }");
            client.print(".container { background-color: #FFFFFF; /* Mantem containers brancos para legibilidade */ padding: 25px; border-radius: 10px; box-shadow: 0 4px 8px rgba(0,0,0,0.15); margin-bottom: 25px; width: 90%; max-width: 450px; }");
            client.print(".led-control { margin-bottom: 15px; }");
            // As cores dos parágrafos dos LEDs são definidas inline, o que é bom para manter suas cores específicas.
            // Esta regra abaixo é um fallback caso algum P dentro de .led-control não tenha cor inline.
            client.print(".led-control p { margin: 0 0 15px 0; font-weight: bold; color: #333; /* Cor padrão para texto dentro do container */ text-align: center; }");
            client.print(".button-container { text-align: center; }");
            client.print("a.button { display: inline-block; padding: 15px 25px; margin: 8px; text-decoration: none; color: white; border-radius: 8px; text-align: center; transition: background-color 0.3s, transform 0.2s, box-shadow 0.3s; box-shadow: 0 2px 4px rgba(0,0,0,0.2); }");
            client.print("a.button:hover { transform: translateY(-2px); box-shadow: 0 4px 8px rgba(0,0,0,0.3); }");
            client.print("a.on { background-color: #388e3c; }"); // Verde para ligar
            client.print("a.on:hover { background-color: #2c6e30; }");
            client.print("a.off { background-color: #d32f2f; }"); // Vermelho para desligar
            client.print("a.off:hover { background-color: #a02525; }");
            // Removida a classe .corner-image, pois a imagem agora é centralizada no header.
            client.print("</style>");
            client.print("</head>");
            client.print("<body>");

            // Nova imagem centralizada no topo
            client.print("<img src='https://www.fiemg.com.br/fiemg/wp-content/uploads/sites/10/2025/05/AT000225_MUNDOSENAI_PECASDIGITAIS_BANNERNOTICIA-1024x396.png' alt='Banner Fiemg Senai' class='header-image'>");

            client.print("<h2>Painel de Controle dos LEDs</h2>");

            // Controle do LED Amarelo
            client.print("<div class='container'>");
            client.print("<div class='led-control'>");
            client.print("<p style='color: #e6a200; font-size: 1.1em;'>LED Amarelo</p>"); // Cor do texto Amarelo ajustada para melhor leitura no branco
            client.print("<div class='button-container'>");
            client.print("<a href='/HY' class='button on'>Ligar</a>");
            client.print("<a href='/LY' class='button off'>Desligar</a>"); // Botão desligar amarelo, mantido vermelho.
            client.print("</div>");
            client.print("</div>");
            client.print("</div>");

            // Controle do LED Verde
            client.print("<div class='container'>");
            client.print("<div class='led-control'>");
            client.print("<p style='color: #388e3c; font-size: 1.1em;'>LED Verde</p>"); // Cor do texto Verde
            client.print("<div class='button-container'>");
            client.print("<a href='/HG' class='button on'>Ligar</a>");
            client.print("<a href='/LG' class='button off'>Desligar</a>");
            client.print("</div>");
            client.print("</div>");
            client.print("</div>");

            // Controle do LED Vermelho
            client.print("<div class='container'>");
            client.print("<div class='led-control'>");
            client.print("<p style='color: #d32f2f; font-size: 1.1em;'>LED Vermelho</p>"); // Cor do texto Vermelho
            client.print("<div class='button-container'>");
            client.print("<a href='/HR' class='button on'>Ligar</a>");
            client.print("<a href='/LR' class='button off'>Desligar</a>");
            client.print("</div>");
            client.print("</div>");
            client.print("</div>");

            // Controle do semáforo
            client.print("<div class='container'>");
            client.print("<div class='led-control'>");
            client.print("<p style='font-size: 1.1em;'>Semáforo 🚦</p>"); // Texto com emoji de semáforo
            client.print("<div class='button-container'>");
            client.print("<a href='/HSEM' class='button on'>Ligar</a>");
            client.print("<a href='/LSEM' class='button off'>Desligar</a>");
            client.print("</div>");
            client.print("</div>");
            client.print("</div>");


            client.print("</body>");
            client.print("</html>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {  // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        if (currentLine.endsWith("GET /HY")) {
          digitalWrite(14, HIGH);
          semaforoLigado = false;  // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /LY")) {
          digitalWrite(14, LOW);
          semaforoLigado = false;  // GET /L turns the LED off
        }

        if (currentLine.endsWith("GET /HG")) {
          digitalWrite(12, HIGH);
          semaforoLigado = false;  // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /LG")) {
          digitalWrite(12, LOW); 
          semaforoLigado = false; // GET /L turns the LED off
        }

        if (currentLine.endsWith("GET /HR")) {
          digitalWrite(13, HIGH);
          semaforoLigado = false;  // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /LR")) {
          digitalWrite(13, LOW);
          semaforoLigado = false;  // GET /L turns the LED off
        }
        if (currentLine.endsWith("GET /HSEM")) {
          digitalWrite(14, LOW);
          digitalWrite(13, LOW);
          digitalWrite(12, HIGH); // Começa com verde
          tempoAnterior = millis();
          estadoSemaforo = 0;
          semaforoLigado = true;
        }
 
        if (currentLine.endsWith("GET /LSEM")) {
          digitalWrite(12, LOW);
          digitalWrite(13, LOW);
          digitalWrite(14, LOW);
          semaforoLigado = false;
        }
 
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
  if (semaforoLigado) {
  unsigned long tempoAtual = millis();

  switch (estadoSemaforo) {
    case 0: // Verde
      if (tempoAtual - tempoAnterior >= 3000) {
        digitalWrite(12, LOW);   // Desliga verde
        digitalWrite(14, HIGH);  // Liga amarelo
        tempoAnterior = tempoAtual;
        estadoSemaforo = 1;
      }
      break;
    case 1: // Amarelo
      if (tempoAtual - tempoAnterior >= 1000) {
        digitalWrite(14, LOW);   // Desliga amarelo
        digitalWrite(13, HIGH);  // Liga vermelho
        tempoAnterior = tempoAtual;
        estadoSemaforo = 2;
      }
      break;
    case 2: // Vermelho
      if (tempoAtual - tempoAnterior >= 3000) {
        digitalWrite(13, LOW);   // Desliga vermelho
        digitalWrite(12, HIGH);  // Liga verde
        tempoAnterior = tempoAtual;
        estadoSemaforo = 0;
      }
      break;
  }
}

}
