# Two-factor authentication

## Paso 1: instalar PAM de Google

![](<img two factor authentication/google-authenticator.png>)

![](<img two factor authentication/preguntas.png>)
## Paso 2: Configurar OpenSSH para usar MFA/2FA

copia de seguridad del archivo de configuración:
```bash
sudo cp /etc/pam.d/sshd /etc/pam.d/sshd.back
sudo nano /etc/pam.d/sshd
```
![](<img two factor authentication/nullok.png>)

Ingreso desde mi host a través de ssh, usando contraseña y el codigo generado en freeotp+:

![](<img two factor authentication/ssh password and code.png>)

## Paso 3: Hacer que SSH sea consciente de MFA

Despues de anular `@include common-auth`, me pide solo el código de verificación:

```bash
ssh analyst@192.168.1.39 -v
```

![](<img two factor authentication/ssh code.png>)

## Paso 4: Agregar un tercer factor

Paso como paramentro la clave privada para entrar y ademas me pide contraseña y código de verificación:

![](<img two factor authentication/ssh 3 factores.png>)

## Paso 5: Recuperar el acceso a Google MFA

Dos de las opciones para recuperar el acceso son:
- Ingresar desde la VM y ver la clave secreta:
```bash
head -n 1 ~/.google_authenticator
```
![](<img two factor authentication/head -n.png>)

- O puedo utilizar uno de los codigos de emergencia para ingresar:

![](<img two factor authentication/codigo de emergencia.png>)

## Paso 6: Cambiar la configuración de autenticación
|   Antes                              |    Despues                           |  
|--------------------------------------|--------------------------------------|
|![](<img two factor authentication/cat antes.png>)|![](<img two factor authentication/cat despues.png>)|
|3 intentos de inicio de sesión cada 30 segundos.|3 intentos cada 60 segundos|
|Usaba el valor predeterminado de 3 códigos en 1:30 minutos | Amplió el margen de tolerancia a 17 códigos válidos|
| |Permite reutilizar el mismo código de 6 dígitos más de una vez dentro de su ventana de validez|

## Conclusión

Aunque las claves criptográficas SSH ofrecen una protección superior contra ataques de fuerza bruta frente a las contraseñas tradicionales, si la clave privada de un usuario es robada o comprometida, el atacante obtiene acceso inmediato. La integración de un token de 6 dígitos obliga a validar la identidad a través de dos canales físicos independientes (la computadora y el dispositivo móvil).

Tiene sentido usar 2FA/MFA en servidores expuestos a Internet y cuentas con privilegios elevados, donde la pérdida de credenciales implica un impacto crítico.
No tiene sentido usarlas en cuentas de servicio automatizados que no pueden responder interactivamente al prompt de un código TOTP, o en entornos de alta disponibilidad donde la pérdida del dispositivo móvil pueda paralizar la operación.
