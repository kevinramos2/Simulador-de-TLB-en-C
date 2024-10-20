//Parcial #2 - Tom�s Murillo Aristizabal y Kevin Leandro Ramos Luna - 2024-1s

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>

// Definimos estos datos
#define TAMANO_DE_PAGINA 4096
#define TAMANO_TLB 285  // 5 entradas * 50 bytes cada una
#define MAX_ENTRADAS_TLB 5
#define TAMANO_ENTRADA 53
#define PAGE_BITS 20 // 20 BITS POR PAG
#define OFFSET_BITS 12 // 12 BITS POR DESP

// Definicion de punteros
int *PUNTERO_ORIGINAL;
int *ptr;

// Contadores
int contadorTraducciones = 0;
int posicionAntigua = 0;

// Atributo para saber si hay pol�tica de reemplazo(1) o no(0)
int politica = 0;

// Funci�n para a�adir una entrada al TLB
void Anadir_Entrada_TLB(char* direccionDecimal, char* numPagina, char* desplazamiento, char* numPaginaBinario, char* despBinario) {
    char* list[5] = {direccionDecimal, numPagina, desplazamiento, numPaginaBinario, despBinario};
    int x;

    // Si el n�mero de traducciones es menor al l�mite permitido 
    if (contadorTraducciones < MAX_ENTRADAS_TLB) {
        // A�adir al TLB normalmente
        memcpy((char*)PUNTERO_ORIGINAL + (contadorTraducciones * TAMANO_ENTRADA), list[0], 10);
        memcpy((char*)PUNTERO_ORIGINAL + (contadorTraducciones * TAMANO_ENTRADA) + (10), list[1], 7);
        memcpy((char*)PUNTERO_ORIGINAL + (contadorTraducciones * TAMANO_ENTRADA) + (17), list[2], 4);
        //Binarios completos
        memcpy((char*)PUNTERO_ORIGINAL + (contadorTraducciones * TAMANO_ENTRADA) + (21), list[3], 20);
        memcpy((char*)PUNTERO_ORIGINAL + (contadorTraducciones * TAMANO_ENTRADA) + (41), list[4], 12);
        contadorTraducciones++;
    } else {
        // Pol�tica de reemplazo FIFO - Dado que el n�mero de traducciones es igual al l�mite permitido
        if (posicionAntigua >= MAX_ENTRADAS_TLB) {
            // Retornamos al valor original
            posicionAntigua = 0;
        }

        // Reemplazamos la informaci�n en los espacios necesarios

        memcpy((char*)PUNTERO_ORIGINAL + (posicionAntigua * TAMANO_ENTRADA), list[0], 10);
        memcpy((char*)PUNTERO_ORIGINAL + (posicionAntigua * TAMANO_ENTRADA) + (10), list[1], 7);
        memcpy((char*)PUNTERO_ORIGINAL + (posicionAntigua * TAMANO_ENTRADA) + (17), list[2], 4);
        //Binarios completos
        memcpy((char*)PUNTERO_ORIGINAL + (posicionAntigua * TAMANO_ENTRADA) + (21), list[3], 20);
        memcpy((char*)PUNTERO_ORIGINAL + (posicionAntigua * TAMANO_ENTRADA) + (41), list[4], 12);

        posicionAntigua = (posicionAntigua + 1) % MAX_ENTRADAS_TLB;
        politica = 1;
    }

    //Son pruebas de depuraci�n
    //printf("Numero Pag: %s\n",numPaginaBinario);
    //printf("Desp: %s\n",despBinario);

}


// La funci�n convierte un n mero decimal a una cadena binaria con longitud especificada
void decimal_binario(int num, char *bin_str, int len) {
    int i;
    for (i = len - 2; i >= 0; --i) {
        bin_str[i] = (num & 1) ? '1' : '0';  // Si el bit menos significativo es 1
        num >>= 1;  // Desplaza a la derecha el n mero
    }
    bin_str[len - 1] = '\0';  // A ade el car cter nulo al final de la cadena
}

// Funci�n para buscar una entrada en el TLB
char* Buscar_Entrada_TLB(char* direccionDecimal) {
    char *ptrBusqueda = (char *)PUNTERO_ORIGINAL;
    char direccionEncontrada[11];  // Aumentado a 11 para incluir '\0'

    //Verificamos cada direcci�n virtual dentro del TLB - se desplazan 53 bytes
    memcpy(direccionEncontrada, ptrBusqueda, 10);
    direccionEncontrada[10] = '\0';
    if (strcmp(direccionEncontrada, direccionDecimal) == 0) {
        return ptrBusqueda;
    }
    memcpy(direccionEncontrada, ptrBusqueda+53, 10);
    direccionEncontrada[10] = '\0';
    if (strcmp(direccionEncontrada, direccionDecimal) == 0) {
        return ptrBusqueda+53;
    }
    memcpy(direccionEncontrada, ptrBusqueda+53*2, 10);
    direccionEncontrada[10] = '\0';
    if (strcmp(direccionEncontrada, direccionDecimal) == 0) {
        return ptrBusqueda+53*2;
    }
    memcpy(direccionEncontrada, ptrBusqueda+53*3, 10);
    direccionEncontrada[10] = '\0';
    if (strcmp(direccionEncontrada, direccionDecimal) == 0) {
        return ptrBusqueda+53*3;
    }
    memcpy(direccionEncontrada, ptrBusqueda+53*4, 10);
    direccionEncontrada[10] = '\0';
    if (strcmp(direccionEncontrada, direccionDecimal) == 0) {
        return ptrBusqueda+53*4;
    }
    return NULL;
}

// Funcion que transforma un numero binario a decimal
int Binario_a_Decimal(char* numeroBinario){
    int size = strlen(numeroBinario)-1;
    int suma = 0;
    int i = 0;
    for (i; i <= size; i++){
        int num = numeroBinario[i] - '0';
        suma += num * pow(2, size - i);
    }	
    return suma;
}      

// Funci�n para calcular el tiempo transcurrido
double tiempo_Transcurrido(struct timespec inicio, struct timespec final) {
    long segundos = final.tv_sec - inicio.tv_sec;
    long nanoseg = final.tv_nsec - inicio.tv_nsec;
    double tiempoTotal = segundos + nanoseg * 1e-9;
    return tiempoTotal;
}

// Funci�n para obtener los atributos de la entrada en el TLB
void Obtener_Atributos_TLB(char* direccionDecimal) {
    char* ptrEntrada = Buscar_Entrada_TLB(direccionDecimal);

    if (ptrEntrada != NULL) {
        char direccionDecimal[11];
        char numPagina[8];
        char desplazamiento[5];
        char numPaginaBinario[PAGE_BITS + 1];  // Para 20 bits
        char despBinario[OFFSET_BITS + 1];       // Para 12 bits

        memcpy(direccionDecimal, ptrEntrada, 10);
        direccionDecimal[10] = '\0';

        memcpy(numPagina, ptrEntrada + 10, 7);
        numPagina[7] = '\0';

        memcpy(desplazamiento, ptrEntrada + 17, 4);
        desplazamiento[4] = '\0';

        memcpy(numPaginaBinario, ptrEntrada + 21, PAGE_BITS);  // 20 bits
        numPaginaBinario[PAGE_BITS] = '\0';


        memcpy(despBinario, ptrEntrada + 41, OFFSET_BITS);  // 12 bits
        despBinario[OFFSET_BITS] = '\0';

        printf("Pagina: %s\n", numPagina);
        printf("Desplazamiento: %s\n", desplazamiento); 
        printf("Pagina en binario: %s\n", numPaginaBinario);
        printf("Desplazamiento en binario: %s\n", despBinario);

        if (politica == 1) {
            printf("Politica de reemplazo: %p\n", (char*)PUNTERO_ORIGINAL + (posicionAntigua * 53) - 53);
            politica = 0;
        } else {
            printf("Politica de reemplazo: 0x0\n");
        }
    } else {
        printf("No se encontro la direccion en el TLB.\n");
    }
}

int main() {
    PUNTERO_ORIGINAL = (int *) malloc(MAX_ENTRADAS_TLB * TAMANO_ENTRADA);
    ptr = PUNTERO_ORIGINAL;

    if (PUNTERO_ORIGINAL == NULL) {
        printf("Error al asignar memoria.\n");
        return -1;
    }

    //Para valores m�ximo de 10 enteros
    uint32_t direccionVirtual;
    char input[11];

    struct timespec inicio, final;

    while (1) {    
        printf("Ingrese direccion virtual: ");
        scanf("%10s", input);

        clock_gettime(CLOCK_MONOTONIC, &inicio);

        if (input[0] == 's') {
            printf("Good bye!\n");
            break;
        }

        if (sscanf(input, "%" SCNu32, &direccionVirtual) == 1) {
            if (Buscar_Entrada_TLB(input) != NULL) {
                printf("TLB desde %p hasta %p\n", (void*)PUNTERO_ORIGINAL, (char*)PUNTERO_ORIGINAL + 285);
                printf("TLB Hit\n");
                Obtener_Atributos_TLB(input);
            } else {
                int numPagina = direccionVirtual / 4096;
                int desplazamiento = direccionVirtual % 4096;

                // Convertir a binario con 20 bits para la p�gina y 12 bits para el desplazamiento
                char numPaginaBinario[PAGE_BITS + 1]; // PAGE_BITS + 1 para el car�cter nulo
                char despBinario[OFFSET_BITS + 1];  // OFFSET_BITS + 1 para el car�cter nulo

                decimal_binario(numPagina, numPaginaBinario, PAGE_BITS + 1);
                decimal_binario(desplazamiento, despBinario, OFFSET_BITS + 1);

                printf("TLB desde %p hasta %p\n", (void*)PUNTERO_ORIGINAL, (char*)PUNTERO_ORIGINAL + 285);
                printf("TLB Miss\n");

                char numPaginaDecimal[11];
                char desplazamientoDecimal[11];
                sprintf(numPaginaDecimal, "%u", numPagina);
                sprintf(desplazamientoDecimal, "%u", desplazamiento);


                Anadir_Entrada_TLB(input, numPaginaDecimal, desplazamientoDecimal, numPaginaBinario, despBinario);
                Obtener_Atributos_TLB(input);            
            }

            clock_gettime(CLOCK_MONOTONIC, &final);
            printf("Tiempo: %.6f segundos\n", tiempo_Transcurrido(inicio, final));
            printf("\n");
        } else {
            printf("Entrada no valida, intenta de nuevo (Direccion virtual)\n");
        }
    }

    free(PUNTERO_ORIGINAL);
    return 0;
}