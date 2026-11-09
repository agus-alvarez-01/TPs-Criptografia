# 🛡️ Gestión de Riesgos en Tecnologías de la Información
**Guía práctica para organizaciones en Argentina**


## 1. Definición de conceptos clave

- **Riesgo**
  Posibilidad de que una **amenaza** aproveche una **vulnerabilidad** y produzca un **incidente** capaz de generar consecuencias negativas sobre uno o más **activos** de información. Se expresa como la combinación de la probabilidad de que ocurra el incidente y el impacto que tendría:
  **Riesgo = Probabilidad × Impacto**
  *(No es una fórmula matemática exacta: es una forma sencilla de entender que el riesgo depende de dos factores.)*

- **Activo**
  Cualquier recurso que posee valor para la organización y cuya pérdida, alteración, divulgación no autorizada o indisponibilidad puede generar consecuencias negativas. Incluye activos tangibles e intangibles. Su valor **no** depende solo de su costo económico: una base de datos de clientes puede valer mucho más que el servidor que la aloja.
  Ejemplo: servidor del sistema contable, base de datos de clientes, red de fibra óptica.

- **Amenaza**
  Cualquier evento, circunstancia o agente con capacidad para causar un daño a un activo de información. Por sí sola no implica que se produzca un incidente: generalmente debe existir una vulnerabilidad que pueda ser explotada.
  Ejemplo: ransomware, incendios, cortes eléctricos prolongados, errores humanos.

- **Vulnerabilidad**
  Debilidad o deficiencia presente en un activo, sistema o procedimiento que puede ser aprovechada por una amenaza.
  Ejemplo: contraseñas débiles, software sin actualizar, ausencia de UPS, falta de procedimientos o de capacitación.

- **Incidente de seguridad**
  Evento que compromete, o tiene el potencial de comprometer, la confidencialidad, integridad o disponibilidad de la información o de los sistemas. Representa la materialización de un riesgo.

- **Impacto**
  Consecuencias que tendría un incidente sobre la organización: económicas, operativas, legales o reputacionales.
  Ejemplo: pérdida de facturación, sanción legal, interrupción de un servicio.

- **Probabilidad**
  Posibilidad de que una amenaza aproveche una vulnerabilidad y afecte al activo. Puede expresarse de forma cualitativa (Baja, Media, Alta), semicuantitativa (escala 1 a 5) o cuantitativa (datos estadísticos, p. ej. eventos por año).

- **Control de seguridad / Mitigación**
  Medidas técnicas, físicas u organizativas destinadas a prevenir incidentes, disminuir su probabilidad o reducir su impacto.
  Ejemplo: firewall, autenticación multifactor, antivirus, copias de seguridad, políticas de seguridad, capacitación del personal.

- **Riesgo inherente**
  Nivel de riesgo al que está expuesto un activo **antes** de aplicar cualquier control. Responde a: *¿qué nivel de riesgo existiría si no se aplicara ningún control?*

- **Riesgo residual**
  Nivel de riesgo que permanece **después** de aplicar los controles. Ningún control elimina el riesgo por completo; la organización debe decidir si el riesgo residual es aceptable.

| Característica | Riesgo inherente | Riesgo residual |
|---|---|---|
| Momento de evaluación | Antes de implementar controles | Después de implementar controles |
| Controles de seguridad | No se consideran | Sí se consideran |
| Nivel de riesgo | Generalmente mayor | Generalmente menor |
| Finalidad | Conocer la exposición inicial | Determinar el riesgo que permanece |

**Secuencia que relaciona los conceptos:**
`Activo → Amenaza → Vulnerabilidad → Incidente → Impacto → Riesgo`

**Características del riesgo:** es incierto, puede variar con el tiempo, depende del contexto y puede gestionarse. Por eso el análisis de riesgos es un **proceso continuo** y debe repetirse periódicamente.

---

## 2. Activos de información

### 2.1 Clasificación de activos

| Categoría | Descripción | Ejemplos |
|---|---|---|
| Información | Datos en formato digital o físico | Bases de datos, documentos, contratos, registros |
| Hardware | Dispositivos físicos de procesamiento, almacenamiento y transmisión | Servidores, PC, notebooks, equipos de red |
| Software | Programas utilizados por la organización | Sistemas operativos, aplicaciones de gestión, bases de datos |
| Servicios | Funciones que permiten operar a la organización | Correo, web institucional, acceso a Internet, autenticación, nube |
| Personas | Quienes usan, administran y deciden sobre los sistemas | Usuarios, administradores, directivos, proveedores |
| Instalaciones e infraestructura | Espacios físicos y soporte de los sistemas | Salas de servidores, cableado, sistemas eléctricos, climatización |

> **Dependencias:** un activo puede depender de otros (una aplicación depende del servidor, de la base de datos y de la red), por lo que un incidente sobre uno puede afectar a los demás.
> **Reputación:** el daño a la imagen institucional se considera un **criterio de valoración del impacto**, no un activo en sí.

### 2.2 Valoración de activos

La valoración **no busca el precio** del activo, sino medir el **impacto** que produciría su pérdida, alteración, destrucción o indisponibilidad. Criterios habituales: valor económico, importancia para la operación, valor de la información, requisitos legales y normativos, e impacto sobre la imagen institucional.

**Valoración mediante la tríada CIA** (escala 0 a 5: 0 sin importancia, 1 muy baja, 2 baja, 3 media, 4 alta, 5 muy alta):

`Valor del activo = Confidencialidad + Integridad + Disponibilidad`

| Activo | C | I | D | Valor |
|---|---|---|---|---|
| Base de datos | 5 | 5 | 4 | 14 |
| Servidor | 4 | 4 | 5 | 13 |
| Computadoras | 2 | 3 | 2 | 7 |

Existen otras formas de combinar la tríada (ponderaciones o valor máximo). Los métodos de valoración pueden ser **cualitativos** (Bajo, Medio, Alto, Crítico), **semicuantitativos** (escala numérica relativa) o **cuantitativos** (valores económicos y datos medibles).

### 2.3 Inventario de activos

Documento que reúne los activos, su ubicación, responsable y criticidad. Campos habituales: identificador, nombre/descripción, tipo, ubicación, responsable, criticidad y observaciones.

| ID | Activo | Tipo | Responsable | Criticidad |
|---|---|---|---|---|
| A-001 | Base de datos académica | Información | Dirección de Sistemas | Crítico |
| A-002 | Servidor principal | Hardware | Dirección de Sistemas | Alto |
| A-003 | Plataforma educativa | Software | Área Académica | Alto |
| A-004 | Sitio web institucional | Software | Área de Comunicación | Medio |
| A-005 | Impresora administrativa | Hardware | Secretaría Administrativa | Bajo |

---

## 3. Clasificación de amenazas y vulnerabilidades

### 3.1 Amenazas (según origen o intencionalidad)

| Tipo | Descripción | Ejemplos |
|---|---|---|
| Naturales | Fenómenos de la naturaleza fuera del control de la organización | Terremotos, inundaciones, tormentas eléctricas, cortes prolongados de energía por fenómenos climáticos |
| Accidentales | Sin intención de dañar; errores humanos, fallas técnicas o descuidos | Borrado accidental, errores de configuración, fallas de hardware, pérdida de dispositivos |
| Intencionales | Realizadas deliberadamente para obtener un beneficio o causar un perjuicio | Malware, phishing, fraude, sabotaje, robo de equipos, acceso no autorizado |

### 3.2 Vulnerabilidades (cuatro categorías)

| Tipo | Descripción | Ejemplos |
|---|---|---|
| Técnicas | Infraestructura, software, hardware o redes | SO sin actualizar, contraseñas predeterminadas, puertos abiertos, ausencia de firewall |
| Humanas | Acciones u omisiones de usuarios o administradores, generalmente sin mala intención | Contraseñas débiles, compartir credenciales, abrir enlaces sospechosos |
| Físicas | Protección de instalaciones y equipamiento | Sin control de acceso físico, sin detección de incendios, cableado expuesto |
| Organizativas | Deficiencias en la gestión de la seguridad | Sin políticas, procedimientos no documentados, sin auditorías ni planes de continuidad |

### 3.3 Relación entre amenazas y vulnerabilidades

`Amenaza + Vulnerabilidad = Posibilidad de que ocurra un incidente de seguridad`

| Activo | Amenaza | Vulnerabilidad |
|---|---|---|
| Base de datos institucional | Malware | Sistema operativo sin actualizar |
| Servidor principal | Incendio | Ausencia de sistema automático de extinción |
| Correo electrónico corporativo | Phishing | Usuarios sin capacitación en ciberseguridad |
| Oficina administrativa | Robo | Falta de control de acceso físico |
| Sistema de gestión académica | Acceso no autorizado | Contraseñas débiles |

---

## 4. Proceso de análisis de riesgos (6 pasos)

| Paso | Actividad | Pregunta que responde |
|---|---|---|
| 1 | **Definir el alcance** (organización, área, sistema, aplicación, centro de cómputos o servicio; objetivos, responsables y período) | ¿Qué vamos a analizar? |
| 2 | **Identificar los activos** (elaborar o actualizar el inventario y verificar su valoración) | ¿Qué debemos proteger? |
| 3 | **Identificar las amenazas** (naturales, accidentales, intencionales) | ¿Qué puede afectar a los activos? |
| 4 | **Identificar vulnerabilidades y controles de seguridad existentes** | ¿Qué vulnerabilidades presentan los activos? ¿Qué controles existen? |
| 5 | **Evaluar el riesgo** | ¿Qué tan importante es el riesgo? |
| 6 | **Tratar el riesgo** | ¿Qué haremos con el riesgo identificado? |

> El análisis es **continuo**: debe actualizarse ante cambios de infraestructura, software, personal o procesos. Para identificar amenazas actuales pueden consultarse fuentes como [CSIRT Américas](https://csirtamericas.org/) o [INCIBE](https://www.incibe.es/).

### 4.1 Paso 5: modelos de evaluación del riesgo

| Modelo | Factores | Aplicación principal |
|---|---|---|
| **Riesgo = Valor del activo × Probabilidad de la amenaza** | Valor del activo y probabilidad | Análisis introductorios y ejercicios didácticos |
| **Riesgo = Probabilidad × Impacto** | Probabilidad e impacto | Metodologías modernas y matrices de riesgo |

Un riesgo de baja probabilidad pero consecuencias muy graves puede ser comparable a otro frecuente pero de impacto reducido.

### 4.2 Paso 6: estrategias de tratamiento del riesgo

1. **Evitar:** eliminar la fuente del riesgo (dejar la actividad o retirar el activo).
   *Ej.: dejar de usar un servidor obsoleto, retirar software con vulnerabilidades críticas.*
2. **Mitigar:** implementar controles que reduzcan la probabilidad o el impacto.
   *Ej.: instalar un firewall, aplicar actualizaciones, capacitar al personal.*
3. **Transferir:** trasladar total o parcialmente las consecuencias a un tercero.
   *Ej.: contratar un seguro informático o externalizar un servicio especializado.*
4. **Aceptar:** asumir el riesgo cuando su nivel es aceptable o cuando el costo de reducirlo supera el beneficio esperado.
   *Ej.: aceptar el riesgo de usar un equipo antiguo cuya sustitución no es económicamente conveniente.*

> Los planes de contingencia, de continuidad y los respaldos fuera del sitio **no** son una estrategia separada en el apunte: se consideran **controles de mitigación** (reducen el impacto). Un riesgo de nivel crítico no debería aceptarse.

---

## 5. Matriz de riesgos

La matriz evalúa **riesgos**, no activos aislados. Cada riesgo surge de la combinación de un **activo**, una **amenaza** y una o más **vulnerabilidades**; por eso un mismo activo puede tener varios riesgos, cada uno evaluado de forma independiente:

| Riesgo | Activo | Amenaza | Vulnerabilidad |
|---|---|---|---|
| R1 | Servidor de base de datos | Ransomware | Sistema operativo sin actualizar |
| R2 | Servidor de base de datos | Corte de energía | Ausencia de UPS |
| R3 | Servidor de base de datos | Robo | Sala sin control de acceso |

**Escalas simples:**

| Nivel | Probabilidad | Impacto |
|---|---|---|
| Baja / Bajo | Rara vez ocurre o no hay antecedentes | Inconvenientes menores |
| Media / Medio | Puede ocurrir ocasionalmente | Interrupciones parciales o pérdidas moderadas |
| Alta / Alto | Ocurre con frecuencia | Pérdidas importantes o afecta procesos críticos |

**Matriz Impacto × Probabilidad:**

| Impacto \ Probabilidad | Baja | Media | Alta |
|---|---|---|---|
| **Alto** | Medio | Alto | Crítico |
| **Medio** | Bajo | Medio | Alto |
| **Bajo** | Bajo | Bajo | Medio |

**Interpretación:**
- **Bajo:** puede aceptarse o mantenerse bajo monitoreo.
- **Medio:** requiere seguimiento y algunos controles.
- **Alto:** demanda acciones correctivas en el corto plazo.
- **Crítico:** requiere atención inmediata.

### Ejemplo cualitativo
Servidor de base de datos expuesto a Internet, con ransomware como amenaza y SO sin actualizar: probabilidad **Alta**, impacto **Alto** → riesgo **Crítico**.

### Ejemplo semicuantitativo
Escalas de 1 (muy bajo) a 5 (muy alto). Valor del activo = 5; probabilidad de ransomware = 4.

`Riesgo = 5 × 4 = 20`

| Resultado | Nivel |
|---|---|
| 1 – 5 | Bajo |
| 6 – 10 | Medio |
| 11 – 15 | Alto |
| 16 – 25 | Crítico |

20 → **Crítico**. Estrategia elegida: **Mitigar** (no se puede evitar eliminando un activo crítico, no corresponde aceptar un riesgo crítico y transferir no resuelve el problema operativo). Controles: actualizar el SO, reforzar las copias de respaldo, autenticación multifactor para administradores y mejor monitoreo del servidor.

---

## 6. Metodologías y marcos de referencia

### 6.1 Metodologías de análisis de riesgos (según el apunte)

| Metodología | Origen | Característica principal |
|---|---|---|
| **MAGERIT** | Consejo Superior de Administración Electrónica, Gobierno de España | Gran énfasis en la valoración de activos y el análisis sistemático de riesgos; muy difundida en el ámbito hispanohablante |
| **OCTAVE** | Software Engineering Institute, Carnegie Mellon University | Enfoque orientado al negocio; prioriza la participación del personal y el conocimiento de los procesos |
| **ISO/IEC 27005** | ISO | Directrices para la gestión de riesgos dentro de un SGSI; no impone una metodología única. Etapas: contexto, identificación, análisis, evaluación, tratamiento, comunicación y seguimiento/revisión |
| **NIST SP 800-30 Rev. 1** | NIST | Guía para realizar evaluaciones de riesgo (incluida en la bibliografía del apunte) |

La elección depende del tamaño de la organización, la complejidad de sus sistemas, los recursos disponibles, los requisitos legales y el nivel de detalle requerido. Es habitual adaptar o combinar metodologías.

### 6.2 Otros marcos y normas (complementarios, no desarrollados en el apunte)

| Marco | Descripción |
|---|---|
| **ISO/IEC 27001** | Norma de seguridad de la información; define el SGSI, dentro del cual se inscribe el análisis de riesgos (ISO/IEC 27005 la acompaña). |
| **ISO 31000** | Marco general de gestión de riesgos. |
| **NIST Cybersecurity Framework (CSF)** | Cinco funciones: Identificar, Proteger, Detectar, Responder, Recuperar. |
| **COBIT** | Marco de gobernanza de TI. |
| **FAIR** | Modelo cuantitativo de valoración económica del riesgo. |

---

## 7. Políticas de seguridad

Una **Política de Seguridad** es un documento formal, aprobado por la dirección, que establece los principios, objetivos y normas generales para proteger la información y los sistemas. Indica **qué** debe hacerse; los procedimientos describen **cómo**. Se elabora a partir de los resultados del análisis de riesgos.

**Características:** aprobada por la dirección, clara y comprensible, aplicable (realista), difundida y actualizada.

**Ciclo de la política (P.S.I.):**
1. **Definición de necesidades:** activos, riesgos identificados, requisitos legales y objetivos de la organización.
2. **Definición de acciones:** reglas, lineamientos y medidas generales.
3. **Implementación:** difusión, capacitación de usuarios e implementación de controles.
4. **Auditoría de seguridad:** verificación del cumplimiento y la eficacia; reinicia el ciclo.

**Ejemplos de políticas derivadas de un análisis de riesgos:**
- Contraseñas robustas y no compartidas.
- Copias de seguridad diarias de la base de datos.
- Servidores actualizados con los últimos parches.
- Acceso al centro de cómputos restringido a personal autorizado.
- Deshabilitación de cuentas inactivas por períodos prolongados.

---

## 8. Ejemplo aplicado en Argentina

**Contexto:** una PyME argentina con servidores locales y conexión de fibra óptica comunitaria.
**Situación:** apagones eléctricos frecuentes en verano.

| Elemento | Valor |
|---|---|
| Activo | Servidor de gestión administrativa (Hardware / Información) |
| Amenaza | Corte prolongado de energía eléctrica (natural, por fenómenos climáticos) |
| Vulnerabilidad | Física: ausencia de UPS o generador |
| Probabilidad | Alta |
| Impacto | Medio: pérdida de acceso a facturación y posible daño de hardware |
| Nivel de riesgo (matriz) | **Alto** |
| Estrategia | Mitigar |
| Controles | Instalar UPS + copia de respaldo en la nube |
| Riesgo residual | Bajo |

---

## 9. Tablas para completar

### 🧩 Tabla A — Inventario y valoración de activos

La escala CIA es de 0 a 5. Los umbrales de criticidad los define cada organización; los valores son ilustrativos.

| ID | Activo | Tipo | Responsable | C | I | D | Valor (C+I+D) | Criticidad | Comentarios |
|---|---|---|---|---|---|---|---|---|---|
| A-001 | Servidor administrativo | Hardware | Área TI | 4 | 4 | 5 | 13 | Alto | Sistema contable y de RRHH |
| A-002 | Base de datos de clientes | Información | Dirección | 5 | 5 | 4 | 14 | Crítico | Datos personales (Ley 25.326) |
| A-003 | Red comunitaria | Infraestructura | Área técnica | 3 | 3 | 5 | 11 | Medio | Necesaria para acceso remoto |
| … | | | | | | | | | |

### ⚠️ Tabla B — Análisis de riesgos (probabilidad × impacto)

| Riesgo | Activo | Amenaza (tipo) | Vulnerabilidad (tipo) | Probabilidad | Impacto | Nivel de riesgo (matriz) | Estrategia | Controles | Riesgo residual |
|---|---|---|---|---|---|---|---|---|---|
| R1 | Servidor administrativo | Corte eléctrico (natural) | Sin UPS (física) | Alta | Medio | Alto | Mitigar | UPS + copia en la nube | Bajo |
| R2 | Base de datos de clientes | Ransomware (intencional) | Sin backup offline (organizativa) | Media | Alto | Alto | Mitigar | Backup semanal offline + antivirus | Medio |
| R3 | Red comunitaria | Sabotaje o falla física (intencional / accidental) | Sin redundancia (técnica) | Baja | Medio | Bajo | Mitigar / Aceptar | Doble enlace de fibra | Bajo |
| … | | | | | | | | | |

### 💲 Tabla C — Complemento cuantitativo (ARO, SLE, ALE)

> Este enfoque **no** forma parte del apunte. Corresponde a la valoración **cuantitativa**, útil cuando se dispone de datos para estimar pérdidas económicas.

- **ARO (Annual Rate of Occurrence):** frecuencia anual estimada del evento.
- **SLE (Single Loss Expectancy):** pérdida monetaria esperada por incidente.
- **ALE (Annualized Loss Expectancy):** pérdida anual esperada. **ALE = SLE × ARO**

| Riesgo | Activo | Amenaza | ARO | SLE | ALE = SLE × ARO |
|---|---|---|---|---|---|
| R1 | Servidor administrativo | Corte eléctrico | 4 | $150.000 | $600.000 |
| R2 | Base de datos de clientes | Ransomware | 1 | $1.000.000 | $1.000.000 |
| R3 | Red comunitaria | Sabotaje o falla física | 2 | $200.000 | $400.000 |
| … | | | | | |

---

## 10. Recursos útiles para Argentina

- [CSIRT Córdoba – Incidentes de Seguridad Informática](https://csirtcordoba.ar/)
- [Ley 25.326 de Protección de Datos Personales](https://www.argentina.gob.ar/aaip/datospersonales/ley-de-proteccion-de-los-datos-personales)
- [CERT UNLP](https://www.cespi.unlp.edu.ar/certunlp/)
- [CSIRT Américas](https://csirtamericas.org/) · [INCIBE](https://www.incibe.es/)

---

## 11. Bibliografía básica (apunte de cátedra)

- Calder, A. *IT Governance: An International Guide to Data Security and ISO 27001/ISO 27002*. Kogan Page.
- ISO/IEC 27005. *Information Security Risk Management*. ISO.
- INCIBE. *Gestión de Riesgos de Seguridad de la Información*.
- MAGERIT v3.0. *Metodología de Análisis y Gestión de Riesgos de los Sistemas de Información*. Gobierno de España.
- NIST SP 800-30 Rev. 1. *Guide for Conducting Risk Assessments*.
- OCTAVE Allegro. *Improving the Information Security Risk Assessment Process*. SEI, Carnegie Mellon University.
- Stallings, W. *Seguridad Informática: Principios y Práctica*. Pearson.
- Whitman, M. E.; Mattord, H. J. *Principles of Information Security*. Cengage Learning.