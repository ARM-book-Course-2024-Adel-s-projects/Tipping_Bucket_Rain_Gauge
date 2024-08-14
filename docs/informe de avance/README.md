### 14/08/24

Se comienzan experimentos con el módulo SIM800L.

Se conecta utilizando una fuente step down (LM2596) conectada a una fuente de PC de escritorio.

* IN = 12 VCC
* OUT = 3.9 VCC

Siguiendo el Datasheet del SIM800L se conectan capacitores para filtrar posibles interferencias, un diodo Zener de 3.9V para proteger el módulo, y resistencias en Tx y Rx (dado que el micro trabaja en 3.3 V).

Las primeras pruebas se hacen con un kit ESP32 devkit. Se configura para poder enviar AT commands y de ese mode aprender a utilizar el módulo.

Se compró un sim de la compañía `Claro`.

Para configurar nuestro módulo, se deben enviar los siguientes comandos AT:

```bash

AT           (Verifica que el módulo esté listo)
OK

ATE0         (Desactiva el eco)
OK

AT+CSQ       (Verifica la intensidad de la señal)
+CSQ: 15,0   (Señal aceptable)
OK

AT+CREG?     (Verifica si la SIM está registrada en la red)
+CREG: 0,1   (Registrado)
OK

AT+CSTT="internet.claro.com.ar","",""  (Configura el APN)
OK

AT+CIICR     (Activa la conexión GPRS)
OK

AT+CIFSR     (Obtiene la IP asignada)
100.72.184.117

AT+CIPSTART="TCP","192.168.1.100","80"  (Establece la conexión TCP)
OK
CONNECT OK

AT+CIPSEND   (Prepara el envío de datos)
>

Hello Server (Envía los datos)
SEND OK

AT+CIPCLOSE  (Cierra la conexión TCP)
CLOSE OK

AT+CIPSHUT   (Desactiva la conexión GPRS)
SHUT OK

```