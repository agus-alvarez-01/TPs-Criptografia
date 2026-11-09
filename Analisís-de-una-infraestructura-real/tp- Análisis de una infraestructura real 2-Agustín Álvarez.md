# Análisis de una infraestructura real 2

## Proceso de análisis de riesgo

### Inventario de Activos

> ¿Qué debemos proteger?

| Activo | Tipo | Criticidad |
| ------ | ---- | ---------- | 
| Servidor HPE Proliant GEN10                 | Hardware    | **Crítico** |
| Archivos y Repositorio de Contenidos (1 TB) | Información | **Alto** |
| PC ad-hoc de Streaming                      | Hardware / Servicio | **Alto** |
| Plataformas OMV, NextCloud y Portainer      | Software    | **Alto** |
| Red Wi-Fi e Infraestructura LAN (TL-WR940N) | Infraestructura | **Medio** |
| Repositorio de Talleres (FileBrowser)       | Servicio    | **Medio** |

---

### Amenazas 

> ¿Qué puede afectar a los activos?

| Tipo | Amenaza | Descripción / Ejemplos en la Radio |
| ---- | ------- | ---------------------------------- |
| Naturales | **Cortes de energía por tormentas** | Fenómenos climáticos o fallas del suministro eléctrico que dejan fuera de servicio la transmisión o el servidor. |
| Naturales | **Inundación / Humedad** | Daño físico en equipos, cableado o servidores instalados en espacios sin control ambiental. |
| Accidentales | **Saturación del canal de Internet** | Consumo masivo de ancho de banda por parte de alumnos en talleres, interrumpiendo el streaming de la radio. |
| Accidentales | **Falla de hardware (Disco rígido)** | Se rompe el disco de 1 TB donde se alojan las producciones de audio. |
| Accidentales | **Borrado o modificación involuntaria** | Pérdida de carpetas o audios por errores humanos. |
| Intencionales | **Infección por Malware / Ransomware** | Cifrado o secuestro de información sensible debido al uso de programas/SO desactualizados expuestos. |
| Intencionales | **Acceso no autorizado a la red** | Intrusión a la LAN interna por parte de terceros desde la Wi-Fi o VPN. |
| Intencionales | **Interceptación / Interceptación de datos** | Captura de usuarios y contraseñas transmitidos a través de la red interna al usar tráfico HTTP sin cifrar. |

### Vulnerabilidades

> ¿Qué vulnerabilidades presentan los activos?

| Categoría | Vulnerabilidad | Descripción / Detalle Técnico |
| --------- | -------------- | ----------------------------- | 
| Técnica | **Falta de segmentación de red y QoS** | Red única e interna compartida entre estudio, talleres e invitados sin control de ancho de banda. |
| Técnica | **Software y SO desactualizados** | OpenMediaVault 6.0 sin soporte de parches y contenedores sin mantenimiento de versiones. |
| Técnica | **Transmisión en texto plano (Sin SSL/TLS)** | Interfaces web de administración (OMV puerto 80, Portainer puerto 9000) expuestas mediante HTTP. |
| Física | **Servidor y PC sin redundancia de disco (RAID)** | El servidor HPE opera con un solo disco de SO y un solo disco mecánico de almacenamiento. |
| Humana | **Credenciales compartidas y claves globales** | Red Wi-Fi con una única clave para todos y FileBrowser con un usuario compartido para alumnos. |
| Organizativa | **Sin copias de seguridad automáticas** | Falta de respaldos locales y externos de los audios. |
| Organizativa | **Dependencia de servicios de terceros (VPN)** | Uso de VPN gratuita limitada a 5 nodos (Hamachi), sin administración ni autonomía propia. |

---

### Controles de seguridad Existentes

> ¿Qué controles existen?

| Control Existente | Estado / Funcionamiento Actual |
| ----------------- | ------------------------------ | 
| **Contenedores Docker via Portainer** | Aísla programas en el servidor HPE, pero la web de gestión está expuesta en HTTP (puerto 9000). |
| **Protocolo SFTP para archivos** | Transferencia cifrada mediante OMV (puerto 222) para uso interno. |
| **VPN LogMeIn Hamachi** | Red virtual privada gratuita para conectar hasta 5 computadoras remotas. |
| **Router exclusivo para red interna** | Dispositivo TP-Link dedicado a la transmisión y circulación de archivos de la radio.|
| **IP fija en el Servidor** | Servidor HPE configurado en `192.168.0.150` para facilitar el acceso interno. |
| **Servidor dedicado HPE Gen10** | Equipo físico de prestaciones empresariales para centralizar la operación. | 

---

### Evaluación y Tratamiento de los Riesgos

> ¿Qué tan importante es el riesgo?

> ¿Qué haremos con el riesgo identificado?


| Riesgo a evaluar | Probabilidad | Impacto | Riesgo | Tratamiento |
| ---------------- | ------------ | ------- | ------ | ----------- |
| Interrupción de la emisión en vivo por consumo excesivo de banda en talleres | **Alta** | **Alto** | **Crítico** | **Mitigar** |
| Pérdida masiva de archivos por falla mecánica del disco rígido | **Media** | **Alto** | **Alto** | **Mitigar** |
| Compromiso del servidor por explotación de vulnerabilidades en OMV 6 / Portainer | **Media** | **Alto** | **Alto** | **Mitigar** |
| Acceso no autorizado a archivos internos desde la Wi-Fi de alumnos | **Alta** | **Medio** | **Alto** | **Mitigar** |
| Interrupción del servicio por dependencia y límites de VPN gratuita (Hamachi) | **Alta** | **Bajo** | **Medio** | **Evitar / Mitigar** |
| Caída prolongada del servidor por cortes de suministro eléctrico | **Baja** | **Medio** | **Bajo** | **Aceptar** |
| Fuga de datos o eliminación accidental por uso de credenciales compartidas en FileBrowser | **Alta** | **Medio** | **Alto** | **Mitigar** |

---

## Medidas que podrían llevarse a cabo

> La radio opera como una cooperativa de trabajo con recursos limitados, por lo tanto se priorizan soluciones basadas en software libre, reutilización de infraestructura existente y un costo económico mínimo.

> En el costo de implementacion no tengo el cuenta el costo operacional.

| Medida Propuesta | Costo de Implementación | Reducción de Riesgo |
| ---------------- | ----------------------- | ------------------- |
| **Configuración de QoS y Aislamiento de Wi-Fi** | $0 (Uso de hardware actual) | **Muy Alta:** Elimina la saturación del ancho de banda asignado al streaming y bloquea el acceso indebido de alumnos a la red interna. |
| **Migración a WireGuard / Tailscale (VPN Propia)** | $0 (Despliegue en Docker) | **Alta:** Reemplaza a Hamachi, elimina el límite de 5 usuarios y quita la dependencia de servicios de terceros. |
| **Proxy Inverso con HTTPS (Nginx Proxy Manager)** | $0 (Let's Encrypt) | **Alta:** Cifra todo el tráfico de gestión web (OMV, Portainer, NextCloud), eliminando la transmisión de claves en texto plano. | 
| **Actualización de SO a OpenMediaVault** | $0 (Software libre) | **Media-Alta:** Remedia vulnerabilidades conocidas y parches de seguridad del sistema operativo base que estaba fuera de soporte (OMV 6). |
| **Individualización de Accesos en FileBrowser y NextCloud** | $0 (Configuración de software) | **Alta:** Elimina el uso de claves compartidas en talleres, garantizando la trazabilidad de acciones y reduciendo el riesgo de fuga/borrado de datos. | 
| **Backup Automatizado** | Bajo (1 disco HDD de 2 TB extra) | **Muy Alta:** Automatiza copias de seguridad diarias del repositorio de 1 TB local y remotamente, para prevenir la pérdida masiva de datos por falla del único disco. |
| **Autenticación SSH por Claves y 2FA + Fail2ban** | $0 (Configuración del SO Debian) | **Alta:** Deshabilita accesos por contraseña y bloquea automáticamente intentos de fuerza bruta sobre el servidor. |
| **Control de Acceso a la Red** | $0 (Configuración de router y switches actuales) | **Media-Alta:** Restringe la asignación de direcciones IP y el acceso a la red cableada/Wi-Fi únicamente a dispositivos previamente autorizados. |
| **Limpieza de Datos Residuales** | $0 (Tarea de mantenimiento) | **Media:** Elimina rastros de instalaciones pasadas de Ubuntu/NextCloud en el disco de 1 TB, recuperando almacenamiento y reduciendo la exposición indebida de datos. |

---

## Conclusion del Reporte de Riesgos

La inversión requerida es prácticamente nula en términos de capital.
La implementación de las medidas podría reducir el perfil de riesgo global de la organización de **Alto/Crítico** a un riesgo residual **Bajo/Aceptable**, también buscan garantizar la estabilidad del servicio de streaming en vivo, la performance de la red y el respaldo de los archivos.
