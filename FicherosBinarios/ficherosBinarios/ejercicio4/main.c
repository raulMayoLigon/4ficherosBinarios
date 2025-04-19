#include <stdio.h>
#include <string.h>

struct persona {
    char nombre[20];
    int edad;
};

int main(void) {
    struct persona p;
    FILE *f;
    char nombreBuscado[20];
    int encontrado = 0;

    printf("Introduce el nombre de la persona que quieres buscar: ");
    scanf("%s", nombreBuscado);

    f = fopen("personas.dat", "rb");
    if (f == NULL) {
        printf("Error al abrir el fichero personas.dat\n");
        return 1;
    }

    while (fread(&p, sizeof(struct persona), 1, f) == 1) {
        if (strcmp(nombreBuscado, p.nombre) == 0) {
            printf("Encontrado! %s tiene %d años.\n", p.nombre, p.edad);
            encontrado = 1;
        }
    }
    
    if (encontrado != 1) {
        printf("No se encontró a %s.\n", nombreBuscado);
    }

    fclose(f);

    return 0;
}
