# Seguridad en NTP y NTPsec

NTPsec es una implementación segura, reforzada y modernizada de NTP. La buena noticia es que NTPsec y NTP son compatibles porque siguen el mismo protocolo básico.

---

## Cuestionario

### 1. Vulnerabilidades e Implicancias
* **¿Cuáles son las vulnerabilidades de NTP?**
* **¿Qué implicancias podría tener que se exploten esas vulnerabilidades?**

### 2. Configuración Actual
* **¿Cuál es tu configuración de NTP actual?**

### 3. Ataques Man-in-the-Middle (MitM)
* **¿Puedes realizar un ataque de tipo Man-in-the-Middle (MitM) sobre un servicio NTP?**
* **¿Puedes implementarlo?**

### 4. Mitigación y Verificación
* **¿Cómo configurarías tu host para evitar problemas con NTP?**
* **¿Cómo verificas que la configuración es correcta?**

### 5. Evaluación de Servidores Externos
* **¿Conoces `ntp.inti.gob.ar`? ¿Es seguro?**

---

## Tarea

Genere un reporte sobre este tema y opcionalmente implemente un servicio de envío de hora como se explica en el documento `readteam.txt`.

---

## Anexo: `readteam.txt`

### Escenario de Laboratorio

**Objetivo:** Entender cómo un atacante podría desviar peticiones NTP y probar cómo defenderse con NTPsec y NTS.

#### 2.1. Montar un AP falso
* En un entorno aislado, se crea un *Access Point* controlado.
* Se podría usar algo como `hostapd` para levantar la red Wi-Fi falsa.

#### 2.2. Redirección de DNS
* Configurar el DNS del AP para resolver, por ejemplo, `time.google.com` hacia la IP de un servidor NTP controlado en la LAN.
* Esto se puede hacer con un DNS local como `dnsmasq` o `bind` en modo laboratorio.

#### 2.3. Servidor NTP manipulado
* En ese servidor NTP falso, devolver respuestas intencionalmente incorrectas para ver el impacto.
* Esto permite observar cómo un cliente sin autenticación acepta una hora errónea.
