#include <stdio.h>
#include <string.h>

struct persona {
    char nombre[20];
    int edad;
};

int main (void) {
    
    struct persona p;
    FILE *f;
    char nombreBuscar[20];
    int encontrado = 0;
    int i;
    
    
    printf("Introduce el nombre de una persona: "); scanf("%s", nombreBuscar);
    
    // Abrimos el fichero en modo lectura y escritura
    f = fopen("personas.dat", "r+b");
    if (f == NULL) {
        printf("Error de apertura...\n"); return 1;
    }
    
    // Leemos los registros del fichero uno a uno
    while (fread(&p, sizeof(struct persona), 1, f) == 1) {
        
        // Comparamos el nombre introducido con el nombre de la persona leída
        if (strcmp(nombreBuscar, p.nombre)==0) {
            printf("Persona encontrada!\n");
            printf("%s tiene %d años.\n", p.nombre, p.edad);
            
            //Aquí cambiamos el valor de p en memoria, no en el fichero aún:
            printf("Introduce la nueva edad de %s: ", p.nombre);
            scanf("%d", &p.edad);
            
            // Usamos fseek para mover el puntero del archivo a la posición anterior
            // Esto es necesario porque no podemos sobrescribir directamente en el archivo
            // con fwrite sin mover primero el puntero de vuelta al inicio del registro
            fseek(f, -sizeof(struct persona), SEEK_CUR);
            
            // Escribimos el nuevo registro con la edad modificada en el archivo
            fwrite(&p, sizeof(struct persona), 1, f);
            
            printf("Edad actualizada!\n"); encontrado = 1;
            break;
        }
    }
    if (encontrado != 1) {
        printf("No se encontró la persona...\n");
    }
    
    fclose(f);
    
    return 0;
}
