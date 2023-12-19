#define RXp2 16
#define TXp2 17
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
String message = "";
char incomingChar;

float dados[3]; // metano, giros, ldr

void setup()
{
    Serial.begin(115200);
    Serial2.begin(115200, SERIAL_8N1, RXp2, TXp2);
    while (!Serial)
        ;

    SerialBT.begin("IntelliVest"); // Nome Para o bluetooth
}

void loop()
{

    if (Serial2.available() > 0)
    {
        delay(10);

        String mensagemRecebida = Serial2.readStringUntil('\n');

        for (int pos = 0; pos < 3; pos++)
        {
            int posVirgula = mensagemRecebida.indexOf(',');
            String valorStr;

            (posVirgula != -1)
                ? (valorStr = mensagemRecebida.substring(0, posVirgula), mensagemRecebida = mensagemRecebida.substring(posVirgula + 1))
                : (valorStr = mensagemRecebida, mensagemRecebida = "");

            dados[pos] = valorStr.toFloat();
        }

        delay(1000);
     /*  Serial.println("Valores Recebidos:");
        Serial.print("metano: ");
        Serial.println(dados[0]);
        Serial.print("giros: ");
        Serial.println(dados[1]);
        Serial.print("ldr: ");
        Serial.println(dados[2]);
*/
        if (Serial.available())
        {
            SerialBT.print(Serial.read());
        }

        if (SerialBT.available())
        {
            char incomingChar = SerialBT.read();
            if (incomingChar != '\n')
            {
                message += String(incomingChar);
            }
            else
            {
                message = "";
            }
            Serial.write(incomingChar);
        }
        SerialBT.println("Valores Recebidos:");
        SerialBT.print("metano: ");
        SerialBT.println(dados[0]);
        SerialBT.print("giros: ");
        SerialBT.println(dados[1]);
        SerialBT.print("ldr: ");
        SerialBT.println(dados[2]);

    }
}
