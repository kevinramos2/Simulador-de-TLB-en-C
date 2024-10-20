# Simulador-de-TLB-en-C
Como parte de una actividad evaluativa de la asignatura Sistemas Operativos, se nos pidió realizar desde cero un Translation Lookasida Buffer (TLB). La funcionalidad del programa es traducir una dirección de memoria lógica/virtual a una dirección física; el TLB podrá contener únicamente 5 traducciones. Una vez se supere el límite, las nuevas traducciones que se ingresen serán guardadas pero se aplicará una política de reemplazo FIFO.  
# Instrucciones de ejecución
El programa leerá de manera indefinida los inputs del usuario hasta que este ingrese una "s", si la entrada es una dirección virtual válida el programa deberá mostrar la siguiente información: 
 - El número de página en decimal y en binario.
 - Deplazamiento dentro de la página en decimal y en binario.
 - El tiempo en segundos que tomó realizar la operación.
 - Mostrar un TLB Hit en caso que la traducción ya se encuentre dentro del TLB.
 - Mostrar un TLB Miss cuando la dirección ingresada aún no esté en el TLB.
 - En caso de haber política de reemplazo se mostrará la dirección del elemento reemplazado.  
    
  
**Este es un ejemplo de uso del programa:** 

  
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
  
**----Más traducciones----**    
  
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


Puedes ejecutar el programa directamente en Replit haciendo clic en el siguiente enlace:   

[![Ejecutar en Replit](https://replit.com/badge?caption=Ejecutar%20en%20Replit)](https://replit.com/@keramosl/parcial2)  
# Créditos  
Este programa fue realizado por:  
--> tmurilloa  
--> kevinramos2  
  

