## Definición de Requisitos y Casos de Uso del Trabajo Final de Sistemas Embebidos

### Selección del proyecto a implementar

Uno de los propósitos de tomar este seminario fue el de desarrollar un sistema que tenga utilidad en la actividad empresarial en la que el alumno se desarrolla. Por ello, es que se debió elegir entre estos dos proyectos:
* Sistema de medición de nivel y llenado de tanques de agua para un campo ganadero
* Tipping Bucket Rain Gauge (Pluviómetro Digital por Balancín)

Los aspectos a analizar a la hora de elegir entre los dos proyectos son:
* Tiempo de implementación
* Aporte de nuevos  conocimientos
* Utilidad del sistema
* Disponibilidad de módulos de Hardware

En la Tabla 1 se aprecia una comparativa de los pesos de ambos proyectos. El proyecto con más peso final es el que resultará elegido como trabajo final.

Proyecto 1: `Tipping Bucket Rain Gauge`
Proyecto 2: `Sistema de medición de nivel y llenado de tanques de agua para un campo ganadero`

| Proyecto   |                   | Tiempo de Implementación(10) | Aporte de nuevos conocimientos (9) | Utilidad del Sistema (8) | Disponibilidad de módulos de hardware (5) | Peso Final |
|------------|-------------------|------------------------------|------------------------------------|--------------------------|-------------------------------------------|------------|
| Proyecto 1 | Puntaje           |8                             |10                                  |9                         |9                                          |            |
| Proyecto 1 | Puntaje Ponderado |80                            |90                                  |72                        |45                                         |287         |
| Proyecto 2 | Puntaje           |8                             |7                                   |9                         |7                                          |            |
| Proyecto 2 | Puntaje Ponderado |80                            |63                                  |72                        |35                                         |250         |

_Tabla 1: Comparación de puntajes ponderados de los proyectos candidatos para trabajo final_

Los tiempos de implementación de los proyectos son acordes a la materia, y además, ambos son extremadamente útiles una vez implementados.

A pesar de ello, no se dispone de los módulos de hardware necesarios para implementar el Sistema de Medición de nivel y llenado de tanques de agua para un campo ganadero, y además no resultaría tan enriquecedor en lo que a adquisición de nuevos conocimientos respecta.

El tipping bucket rain gauge hace uso del módulo SIM800L y de un módulo GPS. El know-how que se obtendrá será muy enriquecedor para futuros sistemas a desarrollarse en el rubro agropecuario.

Es por ello que se termina eligiendo el Tipping Bucket Rain Gauge como proyecto final. Se aclara además que el Sistema de medición de nivel y llenado de tanques de agua para un campo ganadero será implementado en el futuro (no en el marco de esta materia).

_Breve descripción del proyecto Tipping Bucket Rain Gauge_

La finalidad de este proyecto es la de disponer de un pluviómetro digital de fácil instalación en lotes agrícolas. Con ello, podemos obtener información acerca del milimetraje de agua, horas de mayor volumen de lluvia y variabilidad de precipitación en los diferentes lotes de un establecimiento.

El pluviómetro utiliza un reed-switch y un imán para detectar los movimientos de un balancín. El balancín oscila al llenarse con un volumen de agua conocido.

En la Figura 1 se observa una representación del sistema mecánico del pluviómetro digital.

![Fig 1 Tipping Bucket Rain Gauge Scheme](./data/tipping_bucket_rain_gauge.png)

_Figura 1: Tipping Bucket Rain Gauge Scheme_

Conociendo el número de oscilaciones que da el balancín para obtener un milimetraje determinado, es posible determinar, de manera indirecta, el milimetraje caído en la zona de estudio.

El sistema enviará información acerca del milimetraje caído por hora utilizando el módulo SIM800L. Además, se enviará la ubicación del pluviómetro.  La información será recibida por un servidor corriendo una aplicación python comunicada por un socket en un puerto determinado.

En la Figura 2 se observa un diagrama de bloques del sistema.

![Fig 2 Tipping Bucket Raing Gauge Block Diagram](./data/block_diagram.png)
_Figura 2: Diagrama de bloques del tipping bucket rain gauge_

### Elicitación de requisitos y casos de uso

Existen varios sistemas para medir precipitaciones en el mercado. En la Tabla 2 se observa una comparación de sus características.

| Característica         | Omixom OMX-Rain                           | Daza DZH2900                              |
|------------------------|-------------------------------------------|-------------------------------------------|
| Conectividad GPRS      | Sí                                        | No                                        |
| Cargador Solar         | Sí                                        | No                                        |
| API para HTTP Requests | Sí                                        | No                                        |
| Sensores               | Pluviómetro de cubeta Basculante          | Pluviómetro + Anemómetro + Sensor de T°   |
| Alimentación           | Baterías AA                               | Sin batería (transformador a 220V)        |
| Precio                 | 875USD + IVA                              | 528USD + IVA                              |
| Posicionamiento GNSS   | No                                        | No                                        |
| SD Card                | Sí                                        | Sí                                        |

_Tabla 2: Comparación entre dos productos de medición de precipitaciones disponibles en el mercado_

El sistema de Omixom es el que más se asemeja al dispositivo que se quiere construir. La principal limitante para el establecimiento es su precio. Si se quieren instalar varios pluviómetros con fines experimentales, el precio no justificará las pruebas.

Por otro lado, la flexibilidad que da el sistema que va a desarrollarse es clave a la hora de mutar el proyecto. Si bien este prototipo al principio busca medir precipitaciones, en el futuro pueden agregarse sensores de temperatura, radiación solar, anemómetro, etc, a un costo no tan elevado. Se puede también variar la frecuencia a la que el dispositivo envía los datos al servidor (e incluso, migrar a un web server embebido).

#### Requerimientos

La Tabla 3 presenta los requerimientos del proyecto.


| Grupo de Requerimiento         | ID de Requerimiento                       | Descripción                                                                                                                                                                                                   |
|--------------------------------|-------------------------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Sensado                        | 1.1                                       | El sistema medirá precipitaciones con una resolución de 0.2mm.                                                                                                                                                |
| Sensado                        | 1.2                                       | El sistema medirá latitud y longitud con un error menor a 100m.                                                                                                                                               |
| Sensado                        | 1.3                                       | El sistema dispondrá de las mediciones de precipitación de los últimos 100 días.                                                                                                                              |
| Conectividad                   | 2.1                                       | El sistema enviará datos a un servidor externo.                                                                                                                                                               |
| Conectividad                   | 2.2                                       | En caso de haber mala conectividad, el dispositivo almacenará los datos hasta que la conexión se restablezca.                                                                                                 |
| Mecánica                       | 3.1                                       | El sistema medirá oscilaciones de una cubeta basculante.                                                                                                                                                      |
| Mecánica                       | 3.2                                       | El diseño aerodinámico del sistema impedirá las oscilaciones espurias (falsas oscilaciones por viento o golpes).                                                                                              |
| Alimentación                   | 4.1                                       | El sistema será alimentado con baterías AA.                                                                                                                                                                   |
| Alimentación                   | 4.2                                       | El sistema deberá recargar las baterías utilizando paneles solares.                                                                                                                                           |
| Alimentación                   | 4.3                                       | El sistema podrá admitir carga por transformador en caso de haber energía de la red disponible en el lote.                                                                                                    |
| Configuración                  | 5.1                                       | El dispositivo se conectará automáticamente con el servidor una vez encendido.                                                                                                                                |
| Configuración                  | 5.2                                       | El dispositivo podrá medir precipitaciones una vez encendido, incluso en el lapso en el que el sistema se conecta con el servidor.                                                                            |
| Tiempo de Ejecución            | 6.1                                       | El proyecto se entregará antes del 17 de Septiembre de 2024.                                                                                                                                                  |
| Manual de uso y Documentación  | 7.1                                       | El código del sistema embebido estará disponible en un repositorio git, acompañado de un informe detallado con lista de partes, diagramas de conexión, requerimientos cumplidos, forma de uso y conclusiones. |
| Costo                          | 8.1                                       | El costo del dispositivo será menor a los 200 dólares.                                                                                                                                                        |
 _Tabla 3: Requerimientos del sistema_

#### Casos de uso

| Elemento de Caso de Uso | Definición                                                                                                                                                                                                                                                                                                                                                                                                                                              |
|-------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Disparador              | El usuario advierte que hay precipitaciones en la zona en la que se encuentra el pluviómetro.                                                                                                                                                                                                                                                                                                                                                           |
| Precondición            | El sistema está encendido y conectado al servidor. Las baterías del sistema están cargadas.                                                                                                                                                                                                                                                                                                                                                             |
| Flujo Básico            | El usuario abre la aplicación del servidor. El sistema registra el milimetraje de agua caída, y envía el acumulado del día al servidor cada una hora.                                                                                                                                                                                                                                                                                                   |
| Flujo Alternativo | **1.a** El sistema no está conectado a la red. En este caso, el sistema seguirá registrando las precipitaciones, y una vez conectado, enviará el acumulado al servidor. <br><br> **1.b** El sistema está apagado. En este caso, el registro de las precipitaciones se pierde hasta que el sistema se encienda. Una vez encendido, el sistema registra milimetraje hasta que se conecta a la red. Luego de ello, el acumulado diario es enviado al servidor cada una hora. |


_Tabla 4: Diagrama de caso de uso número 1. Medición de acumulado al detectar precipitación_



| Elemento de Caso de Uso | Definición                                                                                                                                                                                                                                                                                                                                                                                                                                              |
|-------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Disparador              | El usuario quiere conocer la posición del pluviómetro en el que se registran precipitaciones.                                                                                                                                                                                                                                                                                                                                                           |
| Precondición            | El sistema está encendido, conectado al servidor y con señal de GPS. Las baterías del sistema están cargadas.                                                                                                                                                                                                                                                                                                                                           |
| Flujo Básico            | El usuario abre la aplicación del servidor. El sistema registra el milimetraje de agua caída, y envía el acumulado del día al servidor cada una hora. Además se recibe la latitud y longitud donde se encuentra el pluviómetro.                                                                                                                                                                                                                         |
| Flujo Alternativo       | **2.a** El sistema no está conectado a la red. En este caso, el sistema seguirá registrando las precipitaciones, y una vez conectado, enviará el acumulado al servidor. También enviará la posición. <br><br> **2.b** El sistema está apagado. En este caso el registro de las precipitaciones se pierde hasta que el sistema se encienda. Una vez encendido, el sistema registra milimetraje hasta que se conecta a la red. Luego de ello, el acumulado diario es enviado al servidor cada una hora, junto con la ubicación del pluviómetro (si hay señal GPS). <br><br> **2.c** El sistema está encendido, conectado a la red, pero sin señal GPS. En este caso, el registro de milimetraje sigue siendo enviado hasta que el GPS obtenga señal nuevamente. Una vez con señal, la posición es registrada y enviada al servidor junto con el acumulado de precipitaciones diario. |


_Tabla 5: Diagrama de caso de uso número 2. Obtención de la posición del pluviómetro digital_



| Elemento de Caso de Uso | Definición                                                                                                                                                                                                                                                                                                                                                                                                                                              |
|-------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Disparador              | El usuario coloca el pluviómetro en el lote y lo enciende.                                                                                                                                                                                                                                                                                                                                                                                              |
| Precondición            | Las baterías del sistema están cargadas. El sistema se encuentra conectado al módulo de carga solar.                                                                                                                                                                                                                                                                                                                                                    |
| Flujo Básico            | El usuario abre la aplicación del servidor. Luego de menos de 3 minutos, la aplicación recibe un mensaje que indica que el pluviómetro está Online. El dispositivo comienza a enviar el acumulado diario de precipitaciones, además de la Latitud y Longitud si hay señal GPS.                                                                                                                                                                          |
| Flujo Alternativo | **3.a** El módulo GNSS no tiene señal y el pluviómetro se conecta con la aplicación del servidor. En este caso, se envía sólo el registro de lluvia hasta que la señal GNSS permite obtener Latitud y Longitud. Una vez que esto ocurre, es enviada junto con los registros de lluvia. <br><br> **3.b** El módulo GNSS posee señal previo a que el sistema se conecte con la aplicación del servidor. En este caso, la posición es registrada junto con el milimetraje, y una vez conectado el sistema, se envía la información a la app en el servidor. |



_Tabla 5: Diagrama de caso de uso número 3. Encendido del pluviómetro._

