# Control de acceso usando ssh y técnicas de protección

## Generación de una nueva clave para SSH y adición al agente SSH

[](<img control de acceso/generar-ssh.png>)

![](<img control de acceso/cat clave publica.png>)

> ¿Cuáles son los algoritmos que puede utilizar ssh?

Los algoritmos que puede utilizar SSH son Ed25519, ECDSA, RSA y DSA.

> ¿RSA sigue vigente?

Sí, pero no en sus variantes antiguas. Las firmas RSA que utilizan el algoritmo de hash SHA-1 están deshabilitadas por defecto debido a vulnerabilidades de colisión. 
RSA solo se considera seguro si utiliza longitudes de clave de al menos 3072 o 4096 bits junto con esquemas de firma modernos (rsa-sha2-256 o rsa-sha2-512). En la actualidad, Ed25519 es el algoritmo recomendado por su mayor velocidad y nivel de seguridad criptográfica con claves más cortas.

## Crear el entorno de pruebas

Uso la VM de cyberops.

![](<img control de acceso/ssh root.png>)

> ¿puede ingresar con root?

No pude.

>  ¿por qué?

Por defecto, en la mayoría de las distribuciones Linux y configuraciones estándar de OpenSSH, la directiva PermitRootLogin está configurada en no o prohibit-password. 
Esto impide que el superusuario acceda directamente via SSH mediante contraseña por motivos de seguridad.  

Con un usuario analyst si se puede:

![](<img control de acceso/ssh analyst.png>)

Copio la clave publica generada a través de ssh hacia el usuario de la VM.  

```bash
ssh-copy-id -i ~/.ssh/tp-asegurar-terminales.pub analyst@192.168.1.39
```

![](<img control de acceso/ssh copy id.png>)

Configuro la conexión por SSH usando la clave privada:

```bash
ssh -o "IdentitiesOnly=yes" -i ~/.ssh/tp-asegurar-terminales analyst@192.168.1.39
```

![](<img control de acceso/ssh private.png>)

Impedir el ingreso con contraseña:

```bash
sudo nano /etc/ssh/sshd_config
```
![](<img control de acceso/nano sshd_config.png>)

Creó el nuevo usuario:

![](<img control de acceso/adduser.png>)

Intento acceder: 

![](<img control de acceso/su nonpriv.png>)

![](<img control de acceso/ssh nonpriv.png>)

> ¿Puede ingresar? 

No

> ¿Por qué? 

Porque lo configuramos sin PasswordAuthentication y tampoco tiene la clave publica copiada en su directorio

> ¿Cómo podemos hacer para poder ingresar?

Para poder ingresar debemos transferir ls clave pública o autorizar el ingreso por contraseña. 

## Banner

Habilito el banner en /etc/sshd_config y lo creo en /etc/banner
```bash
sudo nano /etc/ssh/sshd_config
sudo nano /etc/banner
cat /etc/banner
```

![](<img control de acceso/cat banner.png>)

## Autorización usando PAM

```bash
sudo nano /etc/pam.d/sshd
```
Agrego la linea: `auth required pam_listfile.so item=user sense=deny file=/etc/ssh/ssh.deny onerr=succeed`

```bash
sudo nano /etc/ssh/sshd_config
```
Tuve un problema con el archivo ssh.deny (no existia).

Creo el archivo ssh.deny:
```bash
sudo nano /etc/ssh/ssh.deny
```
Agrego el usuario: `analyst`.
Y pruebo ingresar por ssh nuevamente:

![](<img control de acceso/ssh deny.png>)

Compruebo el archivo de registro de acceso:
```bash
sudo tail -n 20 /var/log/auth.log
```

![](<img control de acceso/auth.log.png>)

Falla la autenticación desde mi IP (`192.168.1.36`), en la linea [4048].

## Fail2ban
```bash
sudo apt update
sudo apt install fail2ban iptables
```
Estado inicial:

![](<img control de acceso/fail2ban.png>)

Primeros 3 intentos de contraseña mal puesta:

![](<img control de acceso/primer-intento.png>)

Baneado:

![](<img control de acceso/baneado.png>)

![](<img control de acceso/baneado-ssh.png>)

> ¿que sucede? 
Despues de 5 intentos quede baneado desde mi host para ingresar por ssh a la VM.

> cual es la salida del comando “sudo iptables -L” ?

Mi IP aparece en REJECT:

![](<img control de acceso/iptables -L.png>)


## Reflexión

> ¿En qué casos conviene listar los usuarios a denegar el acceso? 

Cuando la cantidad de usuarios que usan el acceso es muy grande. 

> ¿sería más interesante listar solamente a quienes deseo permitir el acceso?

Sí, es más seguro denegar el acceso por defecto y solo habilitar lo que quiero.

> ¿En qué casos puede tener sentido? 

En entornos criticos que deben ser seguros, donde el acceso es de pocos usuarios.

> ¿Qué otros servicios puede vigilar fail2ban? 

Puede monitorear cualquier servicio que genere registros (logs) en texto plano. Por ejemplo: servidores Web (Apache y Nginx), FTP, de correo electrónico, bases de datos, VPNs, etc.

> ¿Se puede configurar para que envíe alertas cuando se active?

Si, se pueden configurar para que envíe notificaciones de alerta a tu e-mail, o incluso hacer un script para que te mande mensajes a tu Whatsapp, telegram o discord.

-----
-----

En conclusión, el uso listas de control de acceso, el bloqueo automatizado de direcciones IP y el poder emitir alertas reduce la superficie de ataque del protocolo SSH, haciendo que sea un entorno de operaciones más seguro.