# OpenSSL

## Cifrar mensajes con OpenSSL utilizando criptografía simétrica

### Cifrar un archivo de texto

```bash
cd ./lab.support.files/
cat letter_to_grandma.txt
openssl aes-256-cbc -in letter_to_grandma.txt -out message.enc
```
![](img/cat-letter.png)

### Cifrado AES-256-CBC sin Base64 y con Base64 (-a) 

```bash
cat message.enc
openssl aes-256-cbc -a -in letter_to_grandma.txt -out message.enc
cat message.enc
```
![](<img/cat-message.png>)

## Descifrar mensajes con OpenSSL utilizando criptografía simétrica

```bash
openssl aes-256-cbc -a -d -in message.enc -out decrypted_letter.txt
cat decrypted_letter.txt
```
![](img/cat-decryption.png)

## Cifrar y descifrar datos con OpenSSL utilizando criptografía asimétrica

### Cifrar mensajes con OpenSSL utilizando criptografía asimétrica

```bash
openssl genrsa -aes128 -out alice_private.pem 1024
ls -l alice_private.pem
file alice_private.pem
head alice_private.pem
openssl rsa -in alice_private.pem -noout -text
```
![](img/head-alice.png)

![](img/alice-private.png)

### Extraer la clave pública

```bash
openssl rsa -in alice_private.pem -pubout > alice_public.pem
ls -l *.pem
openssl rsa -in alice_public.pem -pubin -text -noout
```
![](img/alice-public.png)

### Intercambiar mensajes encriptados con la clave públicas

```bash
echo "vim or emacs ?" > top_secret.txt
cat top_secret.txt
```
![](img/vim-emacs.png)

> Hago el mismo procedimiento de Alice para Bob.
```bash
openssl genrsa -aes128 -out bob_private.pem 1024
openssl rsa -in bob_private.pem -pubout > bob_public.pem
ls -l bob_*.pem
```
![](img/bob-private-public.png)

```bash
openssl pkeyutl -encrypt -pubin -inkey bob_public.pem -in top_secret.txt -out top_secret.enc
ls -l top_secret.*
hexdump -C ./top_secret.enc
file top_secret.enc
```
![](img/top-secret.png)

## Descifrar mensajes con OpenSSL utilizando criptografía asimétrica

### Desencriptar mensaje cifrado utilizando la clave privada

```bash
openssl rsautl -decrypt -inkey bob_private.pem -in top_secret.enc > top_secret.txt
cat top_secret.txt
```
![](img/decrypt-bob.png)

## Cifrar y descifrar grandes archivos con OpenSSL

### Genero una clave random y encripto con la clave publica de Bob

> Como no existe un archivo file_secret use letter_to_grandma.txt

```bash
cp letter_to_grandma.txt file_secret
openssl rand -base64 32 > key.bin
openssl rsautl -encrypt -pubin -inkey bob_public.pem -in key.bin -out key.bin.enc
openssl aes-256-cbc -a -pbkdf2 -salt -in file_secret -out file_secret.enc -k key.bin

```
![](img/file-secret.png)

### Desencripto file_secret con la clave privada de Bob

```bash
openssl rsautl -decrypt -inkey bob_private.pem -in key.bin.enc -out key.bin
openssl aes-256-cbc -d -a -pbkdf2 -in file_secret.enc -out file_secret -k key.bin
```
![](img/decrypt-file-secret.png)

---

# Criptografía y Certificados Digitales en la Práctica

## PARTE 1: Fundamentos Teóricos (PKI y Estándar X.509)

### Definición básica 

> ¿Qué es exactamente un certificado digital X.509? 

* **Certificado Digital X.509:** Es un documento digital estandarizado bajo la norma ITU-T X.509 que vincula criptográficamente una clave pública con la identidad de una entidad (un dominio web, persona u organización) mediante la firma digital de una Autoridad de Certificación (CA) de confianza.

> ¿y qué problema fundamental de criptografía asimétrica resuelve?

* **Problema que resuelve:** La criptografía asimétrica por sí sola no garantiza la identidad del dueño de una clave pública. El certificado X.509 resuelve este problema introduciendo la CA que certifica que la clave pública le pertenece realmente al dominio solicitante, evitando que un intermediario pueda suplantar la identidad en el canal cifrado.

---

### El Rol de la CA 

> ¿Qué es una Autoridad de Certificación (CA)? 

Es una entidad de confianza (pública o privada) encargada de verificar la identidad de quienes solicitan certificados, emitir dichos certificados digitales firmándolos con su propia clave privada.

> ¿y por qué los navegadores confían en ellas para validar la identidad de un sitio web?

Los navegadores vienen preconfigurados con un "Almacén de Confianza" (*Trust Store*) que contiene una lista predeterminada de Certificados Raíz de CAs auditadas bajo estándares de seguridad. Si la CA valida la identidad del sitio y firma su certificado, el navegador confía en el sitio porque confía implícitamente en esa CA.

---

### Jerarquía

> Define las diferencias y responsabilidades entre un Certificado Raíz (Root CA), un Certificado Intermedio y un Certificado de Entidad Final (End-Entity/Leaf Certificate).

* **Certificado Raíz:** Es el certificado ubicado en la cima de la jerarquía. Está autofirmado (*self-signed*) y su clave privada se almacena bajo extremas medidas de seguridad (por lo general offline en instalaciones físicas ultraseguras). Su clave pública reside en los almacenes de confianza de los sistemas operativos/navegadores.

* **Certificado Intermedio:** Es un certificado emitido y firmado por la CA Raíz (o por otro intermedio) cuya función principal es actuar como puente y firmar los certificados de los clientes/sitios web finales. Protege a la CA Raíz de estar expuesta directamente a la red en las operaciones diarias.

* **Certificado de Entidad Final:** Es el certificado expedido para el dominio o servidor web específico.

---

### Ciclo de vida 

> ¿Qué es una Lista de Revocación de Certificados (CRL) y qué es OCSP? 

* **CRL (Certificate Revocation List):** Es una lista publicada periódicamente por la CA que contiene los números de serie de los certificados que han sido revocados antes de su fecha de caducidad.

* **OCSP (Online Certificate Status Protocol):** Es un protocolo de red que permite a los clientes/navegadores consultar en tiempo real el estado actual de un certificado específico ante la CA mediante un endpoint.

> ¿Por qué son necesarios incluso antes de que un certificado expire?

Un certificado puede perder su validez antes del tiempo estipulado por diversas razones: filtración o robo de la clave privada del servidor, cambio de propietario del dominio, la quiebra/cierre de la empresa o emisión fraudulenta. 
CRL y OCSP aseguran que un cliente no confíe en un certificado comprometido aunque todavía no haya vencido por fecha calendarizada.

-----------------------------------------------
