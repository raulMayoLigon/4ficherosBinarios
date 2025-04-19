#include <stdio.h>

int main (void) {
    
    int array [10];
    int i;
    int cantidadValores = 0;
    FILE *f;
    
    printf("Introduce los valores del array, hasta 10, \n(cuando quieras terminar escribe -1).\n\n");
    
    for (i=0; i<10; i++) {
        printf("-Introduce un valor para el número %d: ", i+1);
        scanf("%d", &array[i]);
        
        if (array[i] == -1) {
            break;
        }
        cantidadValores++; //Solo si no es menos 1
    }
    
    f = fopen("numeros.dat", "wb");
    if (f == NULL) {
        printf("Error de apertura...\n"); return 1;
    }
    
    fwrite(array, sizeof(int), cantidadValores, f);
    
    fclose(f);
    
    printf("Se guardaron %d en el fichero.\n", cantidadValores);
    
    f = fopen("numeros.dat", "rb");
    if (f == NULL) {
        printf("Error de apertura...\n"); return 1;
    }
    
    fread(array, sizeof(int), cantidadValores, f);
    
    printf("Los valores del fichero son:\n");
    
    for (i=0; i<cantidadValores; i++) {
        printf("|Valor %d: %d|\n", i+1, array[i]);
    }
    
    fclose(f);
    
    return 0;
}
