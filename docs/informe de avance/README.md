### Resumen de avances

Al día 29/08/24, se implementaron varias librerías que ayudarán a la implementación final del `Tipping Bucket Rain Gauge`.

#### Logros

* Aprendizaje de uso del módulo SIM800L: Se aprendió a utilizar los comandos AT para establecer una conexión TCP/IP con un servidor remoto, y enviar mensajes. Se logró enviar mensajes de prueba y el acumulado de lluvias.
* Se creó un port forwarding de la dirección ip pública del gateway para reenviar los paquetes recibidos desde el `Tipping Bucket Rain Gause` a un host de la red que hace de servidor.
* Estoy aprendiendo a utilizar el módulo GPS NEO-6M. Para ello se utilizará la librería `TinyGps++`.

#### Por hacer
* Terminar la librería gps y lograr leer los datos por puerto serie.
* Combinar las librerías para que el proyecto cumpla los requerimientos.
* Mejorar el estilo de código de las librerías agregadas.

En la tabla 1 podemos ver el estado de los requerimientos.

| Grupo de Requerimiento         | ID de Requerimiento                       | Descripción                                                                                                                                                                                                   | Estado               |
|--------------------------------|-------------------------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|----------------------|
| Sensado                        | 1.1                                       | El sistema medirá precipitaciones con una resolución de 0,2 mm.                                                                                                                                               |OK                    |
| Sensado                        | 1.2                                       | El sistema medirá latitud y longitud con un error menor a 100 m.                                                                                                                                              |EN PROGRESO           |
| Sensado                        | 1.3                                       | El sistema dispondrá de las mediciones de precipitación de los últimos 100 días.                                                                                                                              |OK                    |
| Conectividad                   | 2.1                                       | El sistema enviará datos a un servidor externo.                                                                                                                                                               |OK                    |
| Conectividad                   | 2.2                                       | En caso de haber mala conectividad, el dispositivo almacenará los datos hasta que la conexión se restablezca.                                                                                                 |OK                    |
| Mecánica                       | 3.1                                       | El sistema medirá oscilaciones de una cubeta basculante.                                                                                                                                                      |SIMULADO              |
| Mecánica                       | 3.2                                       | El diseño aerodinámico del sistema impedirá las oscilaciones espurias (falsas oscilaciones por viento o golpes).                                                                                              |NO                    |
| Alimentación                   | 4.1                                       | El sistema será alimentado con baterías AA.                                                                                                                                                                   |NO                    |
| Alimentación                   | 4.2                                       | El sistema deberá recargar las baterías utilizando paneles solares.                                                                                                                                           |NO                    |
| Alimentación                   | 4.3                                       | El sistema podrá admitir carga por transformador en caso de haber energía de la red disponible en el lote.                                                                                                    |NO                    |
| Configuración                  | 5.1                                       | El dispositivo se conectará automáticamente con el servidor una vez encendido.                                                                                                                                |OK                    |
| Configuración                  | 5.2                                       | El dispositivo podrá medir precipitaciones una vez encendido, incluso en el lapso en el que el sistema se conecta con el servidor.                                                                            |OK                    |
| Tiempo de Ejecución            | 6.1                                       | El proyecto se entregará antes del 17 de Septiembre de 2024.                                                                                                                                                  |                      |
| Manual de uso y Documentación  | 7.1                                       | El código del sistema embebido estará disponible en un repositorio git, acompañado de un informe detallado con lista de partes, diagramas de conexión, requerimientos cumplidos, forma de uso y conclusiones. |                      |
| Costo                          | 8.1                                       | El costo del dispositivo será menor a los 200 dólares.                                                                                                                                                        |OK                    |

Cómo se puede observar, los requerimientos toman uno de los siguientes estados:
* OK: Requerimiento cumplido
* En Progreso: Se está trabajando en el requerimiento
* Simulado (en este caso, el sistema basculante se simuló con un pulsador hasta montar el sistema mecánico).
* No: Requerimiento no cumplido aún.
