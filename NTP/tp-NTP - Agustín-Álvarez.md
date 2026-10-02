# NTP

### Primero: que es NTP? 
NTP (Network Time Protocol) es un protocolo de red utilizado para sincronizar la fecha y hora de los dispositivos a través de una red, como Internet o una red local.
También el protocolo tiene mecanismos para estimar el retardo de la red y calcular qué tan desfasado está el reloj local respecto del servidor.

### Vulnerabilidades e Implicancias

- **¿Cuáles son las vulnerabilidades de NTP?**

Las principales vulnerabilidades de NTP están relacionadas con la falta de autenticación ,lo que permite ataques como **spoofing, Man-in-the-Middle (MITM)**, donde un atacante puede interceptar o falsificar respuestas y hacer que un equipo ajuste su reloj a una hora incorrecta.

> Aclaración: Spoofing es falsificar la identidad o el origen de una comunicación para engañar al receptor.

Ademas, un MITM no necesariamente tiene que modificar las respuesta, solamente con retrasar determinados paquetes puede provocar que NTP calcule mal el defasaje.

- **¿Qué implicancias podría tener que se exploten esas vulnerabilidades?**

La alteración de la hora puede afectar logs, auditorías, certificados, mecanismos de autenticación y sistemas distribuidos, generando problemas de seguridad y dificultando el análisis de incidentes. 


- **¿Cuál es tu configuración de NTP actual?**

Para ver eso ejecuto `timedatectl`.

![](timedatectl.png)

Figura si el protocolo está activo y la zona horaria que uso.

Tambien se puede ver el servidor que estoy usando, con su IP ejecutando `timedatectl timesync-status`

![](timedatectl_timesync-status.png)

Ademas, figuran la version del protocolo, el defasaje y retardo que tengo.


### Ataque Man-in-the-Middle (MitM)
- **¿Puedes realizar un ataque de tipo Man-in-the-Middle (MitM) sobre un servicio NTP? ¿Puedes implementarlo?**


Si, usando 3 maquinas virtuales y generando una red interna, donde una maquina es el server, otra el cliente y otra el MITM.



### 4. Mitigación y Verificación
* **¿Cómo configurarías tu host para evitar problemas con NTP?**
* **¿Cómo verificas que la configuración es correcta?**

### 5. Evaluación de Servidores Externos
* **¿Conoces `ntp.inti.gob.ar`? ¿Es seguro?**
