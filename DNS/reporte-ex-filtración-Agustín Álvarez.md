# Ex-filtración de datos usando DNS

### ¿Qué es la exfiltración de datos mediante DNS?

DNS Exfiltration es una técnica que utiliza el protocolo DNS para extraer información de una computadora hacia un servidor controlado por un atacante. 
Para realizarlo, los datos se codifican, se dividen en fragmentos y se incorporan a los nombres utilizados en las consultas DNS. El servidor del atacante recibe estos fragmentos y puede reconstruir la información original.


### ¿Cómo funciona?

El artículo `DNS Exfiltration & Tunneling` nombra dos variantes.

- Comunicación directa: la computadora víctima envía las consultas directamente al servidor DNS del atacante.

- Uso del DNS corporativo: la víctima utiliza su servidor DNS habitual, que reenvía la consulta hacia el dominio controlado por el atacante.

---

En el artículo se nombra a `DNSteal`.

`DNSteal` es una herramienta implementada en Python que permite realizar la parte del servidor de una exfiltración DNS directa.
Recibe las consultas, decodifica los datos enviados y permite reconstruir los archivos originales.

---

### ¿Como creen que podrían detectarse este tipo de ataques?

Este tipo de ataque puede detectarse mediante el análisis del tráfico DNS. La idea principal es buscar patrones que no sean habituales en las consultas DNS normales.

Por ejemplo, pueden resultar sospechosas:

* consultas DNS con nombres de dominio excesivamente largos
* grandes cantidades de consultas DNS
* subdominios que contienen cadenas largas de caracteres codificados
* consultas con patrones repetitivos
* utilización anormal del protocolo DNS para transportar grandes cantidades de información.

### ¿Pueden evitarse estos ataques?

Sí, pueden reducirse considerablemente mediante controles de seguridad, aunque aparentemente no hay una única medida que garantice su eliminación.

Una de las medidas es restringir las consultas DNS salientes. 
Los equipos de la red corporativa deberían utilizar los servidores DNS autorizados por la organización, evitando que cada equipo pueda comunicarse directamente con servidores DNS externos.

## Conclusión

El artículo muestra que DNS puede ser utilizado como un canal para transportar información de manera encubierta. Debido a que las consultas DNS normalmente están permitidas en las redes, este tipo de ataque puede resultar difícil de detectar. Por eso, es importante tener restricciones de acceso y monitorear el tráfico DNS para reducir el riesgo de exfiltración.
