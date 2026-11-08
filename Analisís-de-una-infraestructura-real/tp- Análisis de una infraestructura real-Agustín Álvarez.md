# Análisis de una infraestructura real

## La infraestructura de red y su arquitectura:

### ¿Que herramientas de autorización y autenticación se podrían implementar?

* **Autenticación WPA3-Enterprise (IEEE 802.1X):** Reemplazar las claves WPA2 compartidas por un servidor RADIUS para autenticar a los integrantes de la cooperativa mediante credenciales individuales.


* **Control de Acceso a la Red (802.1X / MAC Filtering):** Restringir la asignación de IP y el acceso a la red interna cableada y Wi-Fi a dispositivos previamente autorizados.

> ¿Qué es WPA3-Enterprise?
Es un sistema de seguridad para redes Wi-Fi donde no se usa una contraseña global (como la clave que hoy comparten todos en la radio).
En su lugar, se instala un servidor de autenticación (RADIUS). Cuando alguien intenta conectarse, la Wi-Fi le pide un usuario y contraseña individual.

### ¿Que otras herramientas podrían agregarse para asegurar el sistema?

* **Firewall:** Implementar control de tráfico para restringir accesos inter-VLAN.

* **Uso de VPN propia (Tailscale):** Sustituir LogMeIn Hamachi por un servidor VPN propio para evitar la dependencia de servicios de terceros y eliminar el límite de 5 cuentas.

* **Reglas de QoS / Traffic Shaping:** Priorizar el ancho de banda para la PC de streaming frente a las descargas de los talleres.

### ¿Que bugs o errores puede tener cada uno de estos dispositivos o aplicaciones? Ej. versiones de fw desactualizadas, versiones de aplicaciones desactualizadas ... etc.

* **Router TP-Link:** Firmware desactualizado, puede tener vulnerabilidades de denegación de servicio (DoS) y desbordamiento de memoria.

* **Router Domus :** Mantener credenciales por omisión del proveedor y la falta de control sobre parches de seguridad expone la red WAN.


* **Ausencia de cifrado:** El servidor se administra vía web por el puerto 80, por lo tanto la red interna transmite credenciales sin cifrar.

---

## Los nodos y sus sistemas operativos.

### ¿Que herramientas de autorización y autenticación se podrían implementar?

* **Directorio Centralizado de Usuarios (OpenLDAP):** Centralizar la gestión de cuentas del sistema operativo para evitar tener cuentas de administrador dispersas o mal gestionadas.

* **Autenticación PAM con claves SSH y 2FA:** Deshabilitar la autenticación por contraseña en accesos por terminal e implementar claves RSA/Ed25519 con verificación en dos pasos (TOTP).

* **Principio de Menor Privilegio:** Restringir los privilegios root/administrador únicamente al personal técnico habilitado.

### ¿Que otras herramientas podrían agregarse para asegurar el sistema?

* **Sistema de Autodiagnóstico y Detección de Intrusos (Fail2ban + HIDS):** Bloqueo automático de IP tras reiterados intentos fallidos y monitoreo de integridad de archivos del SO.

* **Gestión Centralizada de Parches:** Programar actualizaciones automáticas de seguridad en el SO base Debian.

### ¿Que bugs o errores puede tener cada uno de estos dispositivos o aplicaciones? Ej. versiones de fw desactualizadas, versiones de aplicaciones desactualizadas ... etc.

* **OpenMediaVault 6.0:** Versión sin soporte.

* **Archivos residuales no borrados:** Presencia de datos de instalaciones pasadas de Ubuntu/NextCloud en el disco de 1 TB que ocupan espacio y aumentan el riesgo de exposición indebida.

* **Falta de redundancia en hardware:** Uso de un único disco para el sistema operativo sin arreglo RAID en el servidor ni contingencia ante fallas físicas en la PC de streaming.

---

## Las aplicaciones instaladas y las posibilidades de asegurarlas.

### ¿Que herramientas de autorización y autenticación se podrían implementar?

* **Autenticación de Doble Factor (MFA/2FA) Obligatoria:** Habilitar MFA en las interfaces de administración de Portainer y NextCloud.

* **Políticas de Contraseñas Robustas:** Exigir contraseñas complejas y expiración periódica, eliminando contraseñas compartidas para FileBrowser.

### ¿Que otras herramientas podrían agregarse para asegurar el sistema?

* **Proxy Inverso con SSL/TLS (Nginx Proxy Manager):** Cifrar todo el tráfico web mediante HTTPS (Let's Encrypt), evitando la exposición en texto plano de los puertos 80, 3670, 8181 y 9000.

* **Aislamiento con contenedores Docker:** Ejecutar contenedores con usuarios no privilegiados y aplicar límites de memoria y CPU a aplicaciones secundarias.

### ¿Que bugs o errores puede tener cada uno de estos dispositivos o aplicaciones? Ej. versiones de fw desactualizadas, versiones de aplicaciones desactualizadas ... etc.

* **Portainer en Puerto 9000 (HTTP):** Exposición de la consola de gestión de Docker en texto plano sin cifrar.

* **FileBrowser con usuario único compartido:** La utilización de una misma credencial para todos los alumnos en talleres elimina la trazabilidad de acciones.

---
