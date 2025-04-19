#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (void) {
    
    //Declaración
    int x;
    int xLeer;
    FILE *f;
    
    //Crear y guardar el número en el fichero:
    
    //1.Pedir número al usuario
    printf("Introduce el valor de x: "); scanf("%d", &x);
        
    //2.Abrir fichero modo escritura
    f = fopen("numero.dat", "wb");
    if (f == NULL) {
        printf("Error al crear el fichero...\n"); return 1;
    }
    
    //3.Escribimos el número en el fichero
    fwrite(&x, sizeof(int), 1, f);
    
    //4.Cerramos el fichero después de escribir
    fclose(f);
    
    
    //Leer el fichero:
    
    //1.Abrimos el fichero en modo lectura
    f = fopen("numero.dat", "rb");
    if (f == NULL) {
        printf("Error de apertura...\n"); return 1;
    }
        
    //2.Leemos el número del fichero
    fread(&xLeer, sizeof(int), 1, f);
    
    //3.Cerramos el fichero después de leer
    fclose(f);
    
    //4.Mostramos el número leído
    printf("El número leído es: %d\n", xLeer);
    
    return 0;
    
}


