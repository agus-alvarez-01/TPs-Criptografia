# Archivos de registro de eventos

#### - Describir brevemente lo que sucedió a partir de la entrada de registro

La entrada indica que el servidor Apache recibió una solicitud desde la dirección 
IP `209.165.200.230` y se produjo un error porque el archivo `favicon.ico` no se 
encontró en la ruta `/var/www/apache/htdocs/favicon.ico`.

---

#### - ¿La salida anterior se puede considerar una transacción web? Explicar por qué el formato es diferente al de la entrada única que se presenta en el punto (a).

Sí, se puede considerar una transaccion web, ya que cada entrada registra varias solicitudes HTTP realizadas a servidores web.
Contiene información como dirección IP del cliente, fecha y hora de la solicitud, utiliza el metodo `GET` de HTTP, etc.

La salida tiene un formato diferente al de la entrada del punto anterior porque corresponden a distintos tipos de registros. La primera entrada pertenece al **registro de errores** (`error log`), y lo que muestra `cat` corresponden a un **registro de acceso** (`access log`).

---

#### - ¿ Puede encontrar pruebas de ello en las entradas de registro de arriba ? Si es así, ¿ en qué líneas ? Explicar brevemente.

Hay un error con respencto a las fechas que se plantean pero sí, en las entradas se pueden ver indicios de problemas en la conexión de red. 
Aparecen varias entradas en las que la interfaz `enp0s3` pierde y recupera el enlace, lo que podría provocar problemas o lentitud en las operaciones de red:

```text
Mar 20 14:28:29 ... enp0s3: link down
Mar 20 14:28:33 ... enp0s3: link up, 100Mbps, full-duplex
Mar 20 14:28:35 ... enp0s3: link down
Mar 20 14:28:43 ... enp0s3: link up, 100Mbps, full-duplex
Mar 20 14:28:53 ... enp0s3: link down
Mar 20 14:28:57 ... enp0s3: link up, 100Mbps, full-duplex
Mar 20 14:29:01 ... enp0s3: link down
Mar 20 14:29:05 ... enp0s3: link up, 100Mbps, full-duplex
```
---

#### - ¿Cómo pueden ejecutar `journalctl` y ver todas las entradas de registro?

Para poder ver todas las entradas de registro del sistema, hay que ejecutar `journalctl` con permisos de superusuario `sudo journalctl`, porque `analyst` no pertenece a los grupos que tienen permisos para acceder a todos los registros del sistema.
