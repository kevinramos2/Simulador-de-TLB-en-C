# Simulador-de-TLB-en-C
Como parte de una actividad evaluativa de la asignatura Sistemas Operativos, se nos pidió realizar desde cero un Translation Lookasida Buffer (TLB). La funcionalidad del programa es traducir una dirección de memoria lógica/virtual a una dirección física; el TLB podrá contener únicamente 5 traducciones. Una vez se supere el límite, las nuevas traducciones que se ingresen serán guardadas pero se aplicará una política de reemplazo FIFO. 

# Características del simulador  
- Traduce direcciones de memoria virtual a direcciones físicas.  
- Capacidad limitada a **5 traducciones** en el TLB.  
- Aplicación de la política de reemplazo **FIFO** cuando se supere el límite de traducciones.  
- Reporte de **TLB Hit** o **TLB Miss** según corresponda.  
- Muestra detalles como la página y desplazamiento en formatos **decimal y binario**.  
- Calcula el **tiempo en segundos** que toma cada operación.
  
# Instrucciones de ejecución
El programa leerá de manera indefinida los inputs del usuario hasta que este ingrese una "s", si la entrada es una dirección virtual válida el programa deberá mostrar la siguiente información:   
| Información                  | Descripción                                                                                     |
|------------------------------|-------------------------------------------------------------------------------------------------|
| **Página (decimal y binario)** | Número de página correspondiente a la dirección ingresada.                                      |
| **Desplazamiento**           | Offset dentro de la página, en formatos decimal y binario.                                      |
| **Tiempo de operación**      | Tiempo que tomó la traducción, medido en segundos.                                              |
| **Estado del TLB**           | Indica si la traducción fue un **Hit** (ya estaba en el TLB) o un **Miss** (no estaba en el TLB).|
| **Reemplazo en el TLB**      | Dirección reemplazada, si se aplica la política FIFO.                                           |

    
  
### Este es un ejemplo de uso y salida del programa:
```bash
Ingrese direccion virtual: 10992  
TLB desde 0x563cfed532a0 hasta 0x563cfed533bd  
TLB Miss  
Pagina: 2  
Desplazamiento: 2800  
Pagina en binario: 00000000000000000010  
Desplazamiento en binario: 101011110000  
Politica de reemplazo: 0x0  
Tiempo: 0.000024 segundos  

Ingrese direccion virtual: 10992  
TLB desde 0x563cfed532a0 hasta 0x563cfed533bd  
TLB Hit  
Pagina: 2  
Desplazamiento: 2800  
Pagina en binario: 00000000000000000010  
Desplazamiento en binario: 101011110000  
Politica de reemplazo: 0x0  
Tiempo: 0.000029 segundos     
  
----Más traducciones----  
  
Ingrese direccion virtual: 19986  
TLB desde 0x563cfed532a0 hasta 0x563cfed533bd  
TLB Miss  
Pagina: 4  
Desplazamiento: 3602  
Pagina en binario: 00000000000000000100  
Desplazamiento en binario: 111000010010  
Politica de reemplazo: 0x563cfed532a0  //Aquí se realizó una política de reemplazo  
Tiempo: 0.000028 segundos  

Ingrese direccion virtual: 19986  
TLB desde 0x563cfed532a0 hasta 0x563cfed533bd  
TLB Hit  
Pagina: 4  
Desplazamiento: 3602  
Pagina en binario: 00000000000000000100  
Desplazamiento en binario: 111000010010  
Politica de reemplazo: 0x0  
Tiempo: 0.000020 segundos  

Ingrese dirección virtual: s  
Good bye!
```

Puedes ejecutar el programa directamente en Replit haciendo clic en el siguiente enlace:   

[![Ejecutar en Replit](https://replit.com/badge?caption=Ejecutar%20en%20Replit)](https://replit.com/@keramosl/parcial2)  
# Créditos  
Este programa fue realizado por:  
--> <a href="https://github.com/tmurilloa">tmurilloa</a>  
--> <a href="https://github.com/kevinramos2">kevinramos2</a>  
  

