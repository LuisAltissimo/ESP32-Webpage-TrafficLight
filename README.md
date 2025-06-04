# Controle de LEDs e Semáforo com ESP32 via Wi-Fi

Este projeto permite controlar três LEDs individuais (amarelo, verde, vermelho) e uma sequência de semáforo utilizando um ESP32 conectado à rede Wi-Fi. O controle é feito através de uma página web simples hospedada pelo próprio ESP32.

## Funcionamento Principal

1.  **Conexão Wi-Fi**: Ao iniciar, o ESP32 se conecta à rede Wi-Fi especificada nas variáveis `ssid` e `password`.
2.  **Servidor Web**: Após conectar, ele inicia um servidor web na porta 80. O endereço IP do ESP32 na rede local é exibido no Monitor Serial do Arduino IDE.
3.  **Interface HTML**: Ao acessar o IP do ESP32 em um navegador, uma página HTML é carregada. Essa página contém botões para:
    * Ligar/Desligar o LED Amarelo (conectado ao pino 14).
    * Ligar/Desligar o LED Verde (conectado ao pino 12).
    * Ligar/Desligar o LED Vermelho (conectado ao pino 13).
    * Ligar/Desligar uma sequência de semáforo automática.
4.  **Controle dos LEDs**:
    * Cliques nos botões enviam requisições HTTP GET para o ESP32 (ex: `GET /HY` para ligar o LED amarelo).
    * O ESP32 interpreta essas requisições e aciona os pinos correspondentes (HIGH para ligar, LOW para desligar).
5.  **Lógica do Semáforo**:
    * Ao ligar o semáforo (`GET /HSEM`), uma rotina é ativada, alternando entre os LEDs verde (3s), amarelo (1s) e vermelho (3s) automaticamente.
    * A função `millis()` é usada para o controle de tempo não bloqueante.
    * Ao desligar (`GET /LSEM`), a sequência para e todos os LEDs do semáforo são apagados.

## Como Conectar e Controlar os LEDs

1.  **Configuração**:
    * Altere as variáveis `ssid` e `password` no código com as credenciais da sua rede Wi-Fi.
    * Faça o upload do código para o seu ESP32.
2.  **Descobrir o IP**:
    * Abra o Monitor Serial na Arduino IDE (baud rate 115200).
    * Ou conecte no roteador para verificar o IP do ESP (Nome de usuário: admin, Senha: mundosenai)
    * Após o ESP32 conectar ao Wi-Fi, ele imprimirá o **endereço IP local** (Ex: `IP address: 192.168.1.X`). Anote este IP.
3.  **Acessar a Interface**:
    * Em um dispositivo (computador, smartphone) conectado à **mesma rede Wi-Fi** que o ESP32, abra um navegador web.
    * Digite o endereço IP obtido no passo anterior na barra de endereços do navegador.
    * A página de controle dos LEDs será carregada, permitindo que você os comande.

## Pinos Utilizados

* **LED Amarelo**: GPIO 14
* **LED Verde**: GPIO 12
* **LED Vermelho**: GPIO 13

## Requisições HTTP para Controle

A interface web envia os seguintes comandos via GET requests:
* `/HY`: Liga LED Amarelo
* `/LY`: Desliga LED Amarelo
* `/HG`: Liga LED Verde
* `/LG`: Desliga LED Verde
* `/HR`: Liga LED Vermelho
* `/LR`: Desliga LED Vermelho
* `/HSEM`: Liga o modo Semáforo
* `/LSEM`: Desliga o modo Semáforo e todos os LEDs
