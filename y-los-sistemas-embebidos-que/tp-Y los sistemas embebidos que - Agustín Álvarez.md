# Y los sistemas embebidos que?

## Casos de incidentes en sistemas embebidos

### Vulnerabilidades en Marcapasos Cardiacos (St. Jude Medical)

> Descripción del Incidente:

En 2017, la FDA (Food and Drug Administration de Estados Unidos) emitió una alerta de seguridad tras confirmarse la presencia de fallos críticos de ciberseguridad en transmisores y marcapasos cardíacos implantables del fabricante St. Jude Medical. Un atacante remoto con conocimientos técnicos podía explotar estas vulnerabilidades para alterar la programación del dispositivo, administrar descargas eléctricas no autorizadas, modificar el ritmo de estimulación cardíaca o agotar de forma prematura la batería del implante, poniendo en riesgo directo la vida del paciente.

> Vulnerabilidad:

El problema principal era la falta de mecanismos de seguridad en las comunicaciones por radiofrecuencia (RF) entre el transmisor doméstico y el marcapasos implantado. Las transmisiones carecían de autenticación mutua y de cifrado de extremo a extremo, lo que permitía a un atacante interceptar la señal, realizar ataques de denegación de servicio o inyectar comandos de control arbitrarios (Ataque de Man-in-the-Middle).

> Se pudo haber evitado:

Cifrado: Implementar protocolos criptográficos robustos para cifrar los canales de comunicación inalámbrica y requerir la autenticación de claves antes de procesar cualquier orden dentro del microcontrolador del marcapasos.

Arranque Seguro: Garantizar que únicamente el firmware firmado digitalmente por el fabricante pueda ejecutarse en el dispositivo, previniendo modificaciones no autorizadas en el código ejecutable.

---

### Control Remoto Vehicular - Jeep Cherokee

> Descripción del Incidente:

En 2015, investigadores de ciberseguridad demostraron la posibilidad de tomar el control remoto y total de un vehículo Jeep Cherokee en pleno movimiento desde una ubicación distante. Sin necesidad de acceso físico previa instalación de componentes, los investigadores lograron manipular desde la distancia funciones del sistema de infoentretenimiento, el aire acondicionado y los limpiaparabrisas, hasta acciones críticas de seguridad como la dirección, el acelerador y la desactivación del sistema de frenado, lo que derivó en el retiro del mercado de 1,4 millones de vehículos para la aplicación de un parche de seguridad.

> Vulnerabilidad:

La vulnerabilidad principal se encontró en el sistema de "infoentretenimiento" embebido (es la consola central), el cual mantenía abierto y expuesto el puerto de comunicación D-Bus a través del servicio de telefonía celular, accesible sin ningún tipo de autenticación previa. Sumado a esto, el procesador del sistema multimedia carecía de una separación lógica o aislamiento físico respecto a la red de bus de control de la área local del vehículo, permitiendo a un atacante enviar tramas de datos maliciosas directamente a las Unidades de Control Electrónico (ECU) del motor, los frenos y la dirección.

> Se pudo haber evitado:

Aislamiento de Redes: Implementar puertas de enlace (Gateways) con firewalls embebidos que aíslen estrictamente las redes no críticas (infoentretenimiento, conectividad celular/Wi-Fi) de los buses de control crítico del vehículo.

Restricción de Puertos e Interfaces Expuestas: Deshabilitar por defecto cualquier puerto de diagnóstico, depuración o interfaz de administración accesible a través de redes inalámbricas o WAN.

Autenticación: Implementar protocolos de comunicación vehicular seguros que requieran autenticación de mensajes y firmas digitales antes de que una ECU acepte y ejecute órdenes sobre sistemas físicos críticos.

---

### Vulnerabilidades URGENT/11 en el Sistema Operativo VxWorks

> Descripción del Incidente:

En 2019, la empresa de ciberseguridad Armis descubrió un conjunto de 11 vulnerabilidades críticas (denominadas **URGENT/11**) en VxWorks, uno de los sistemas operativos en tiempo real (RTOS) más utilizados del mundo en sistemas embebidos. Estas vulnerabilidades afectaban a cientos de millones de dispositivos en diversos sectores, incluyendo equipos médicos críticos (bombas de infusión, monitores de paciente, sistemas de imágenes), infraestructura industrial y dispositivos de red. 
Seis de estas fallas permitían la ejecución remota de código sin requerir interacción del usuario, lo que posibilitaba a un atacante tomar el control total del dispositivo embebido o alterar su funcionamiento en tiempo real.

> Vulnerabilidad:

Los fallos eran en la pila de protocolos de red TCP/IP integrada dentro del sistema operativo. Las vulnerabilidades incluían errores de buffer overflow y fallos en la validación de paquetes de datos a nivel de red, lo que permitía a un atacante enviar paquetes TCP/IP especialmente diseñados para sobreescribir la memoria del procesador, eludir los controles de autenticación y ejecutar código malicioso con privilegios elevados dentro del sistema embebido.

> Se pudo haber evitado:

Actualización y Parcheo de Firmware: Aplicar las actualizaciones de seguridad y parches del RTOS emitidos por el fabricante para corregir la validación de los datos de entrada en la pila TCP/IP.

Inspección de Trafico de Red y Firewalls Embebidos: Implementar reglas de filtrado e inspección de paquetes en los conmutadores y firewalls de la red médica/industrial para detectar y bloquear tramas de datos anómalas o manipuladas.

Aislamiento de Dispositivos: Aislar los dispositivos médicos y sistemas de control embebidos en redes locales virtuales (VLANs), impidiendo su exposición directa a redes públicas.

---

## QEMU_ESP32

Para realizar los ejemplos de las filminas de Seguridad en sistemas embebidos, utilice el repositorio de `mluis/qemu-esp32`.

```bash
git clone https://github.com/mluis/qemu-esp32.git
```
### Ejecución

Segui los pasos del archivo README.md para poder usarlo:

```bash
cd qemu-esp32/
docker build . -t qemu-esp32
docker run --name qemu-esp32 --rm -i -p 8080:80 -t qemu-esp32 bash
idf
```

Luego dentro de `program/main` en el archivo `emulation.c` modifique el codigo generando los scripts para hash (SHA-256), encripción simétrica (AES-128) y firma digital (ECDSA), los cuales utilizan la libreria `PSA Crypto`.

En otra terminal copie el archivo `emulation.c` hacia el docker ya levantado:

```bash
docker cp program/main/emulation.c qemu-esp32:/root/program/main/emulation.c
```
En la terminal de docker se compila el firmware, se empaqueta la imagen flash y se arranca el emulador QEMU.

```bash
idf.py build -C program
./flash.sh program/build/emulation.bin
qemu-system-xtensa -nographic -M esp32 -m 4 -drive file=flash.bin,if=mtd,format=raw
```

![](<img/docker run.png>)

![](<img/qemu run.png>)

### Código
Link al repositorio para ver emulation.c: https://github.com/agus-alvarez-01/TPs-Criptografia/blob/main/y-los-sistemas-embebidos-que/qemu-esp32/program/main/emulation.c
