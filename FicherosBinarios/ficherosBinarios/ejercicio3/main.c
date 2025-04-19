#include <stdio.h>

struct persona {
    char nombre [20];
    int edad;
};

int main (void) {
    
    struct persona p[3];
    int i;
    FILE *f;
    
    printf("Introduce los datos de cada persona:\n");
    for (i=0; i<3; i++) {
        printf("Persona %d\n", i+1);
        printf("\t-Nombre: "); scanf("%s", p[i].nombre);
        printf("\t-Edad: "); scanf("%d", &p[i].edad);
    }
    
    f = fopen("personas.dat", "wb");
    if (f == NULL) {
        printf("Error de apertura...\n"); return 1;
    }
    
    fwrite(p , sizeof(struct persona), 3, f);
    fclose(f);
    
    f = fopen("personas.dat", "rb");
    if (f == NULL) {
        printf("Error de apertura...\n"); return 1;
    }
    
    fread(p, sizeof(struct persona), 3, f);
    
    for (i=0; i<3; i++) {
        printf("Datos persona %d:\n", i+1);
        printf("\t-Nombre: %s | -Edad: %d\n", p[i].nombre, p[i].edad);
    }
    
    fclose(f);
    
    
    
    return 0;
}
