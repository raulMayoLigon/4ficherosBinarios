#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct datosFecha{
int dia;
int mes;
int anno;
};
struct datosCompra{
char nombre[40];//nombre de la compañía
int numero; //número de acciones
struct datosFecha fecha; //fecha de compra
double precio; //precio de compra
};

void visualizarFichero (char nombreFichero[]);
void visualizarTotales (char nombreFichero[]);

void gestionCompra (char nombreFichero[]);
void introducirDatosCompra (struct datosCompra *reg);
void volcar (char nombreFicheroOrigen[], char nombreFicheroDestino []);

int main (void) {
    
    visualizarFichero("acciones");
    
}

void introducirDatosCompra (struct datosCompra *reg) {
    
    printf("Introduce la compañía de la que compras: "); fpurge(stdin);
    scanf("%s", reg->nombre);
    printf("Introduce el núm de acciones: "); fpurge(stdin);
    scanf("%d", &reg->numero);
    printf("Introduce el precio: "); fpurge(stdin);
    scanf("%lf", &reg->precio);
    printf("Introduce la fecha: \n");
    printf("-Día: "); scanf("%d", &reg->fecha.dia);
    printf("-Mes: "); scanf("%d", &reg->fecha.mes);
    printf("-Año: "); scanf("%d", &reg->fecha.anno);
    
}

void visualizarFichero (char nombreFichero[]) {
    
    FILE *f;
    struct datosCompra reg;
    
    //1.Abro el fichero en lectura
    f = fopen(nombreFichero, "rb");
    if (f == NULL) {
        printf("Error de apertura...\n");
        return;
    }
    
    //2.Leo
    fread(&reg, sizeof(struct datosCompra), 1, f);
    
    //3.Bucle hasta el eof
    while (!feof(f)) {
        printf("\nCompañía: %s, Núm acciones: %d, Precio: %lf, %d/%d/%d", reg.nombre, reg.numero, reg.precio, reg.fecha.dia, reg.fecha.mes, reg.fecha.anno);
        fread(&reg, sizeof(struct datosCompra), 1, f);
    }
    printf("\n----------Fin del fichero----------\n");
    
    //4.Cierro
    fclose(f);
    
    
}

void visualizarTotales (char nombreFichero[]) {
    
    FILE *f;
    struct datosCompra reg;
    char companny [40];
    int total;
    
    //1.Abro el fichero en lectura
    f = fopen(nombreFichero, "rb");
    if (f == NULL) {
        printf("Error de apertura...\n");
        return;
    }
    
    //2.Leo
    fread(&reg, sizeof(struct datosCompra), 1, f);
    //Inicializo companny y total
    if (feof(f)) {
        //El fichero está vacío, no tengo que hacer nada
        printf("Fichero vacío...\n"); fclose(f); return;
    }
    //El fichero tienen compras, inicializo
    strcpy(companny, reg.nombre); //Me quedo con la compañía para ver si hay más de esta
    total = reg.numero;
    fread(&reg, sizeof(struct datosCompra), 1, f);  //Leo el segundo
    while (!feof(f)) {
        //Hago el tratamiento
        fread(&reg , sizeof(struct datosCompra), 1, f);
        if (strcmp(reg.nombre, companny) == 0) {
            //sigo con compras de la misma compañía
            total = total + reg.numero;
        } else {
            //He cambiado la compañía
            //Visualizo la información de la compañía con la que he terminado.
            printf("\nCompañía: %s \t número Total: %d", companny, total);
            //reinicializar las vbles total y companny;
            strcpy(companny, reg.nombre);
            total = reg.numero;
        }
        
        fread(&reg, sizeof(struct datosCompra), 1, f);
    }
    printf("Visualizar la última compañía.\n");
    printf("Compañía: %s \t Núm total: %d\n", companny, total);
    fclose(f);
}

void gestionCompra (char nombreFichero[]) {
    
    FILE *f, *faux;
    struct datosCompra reg, regNuevo;
    
    f = fopen(nombreFichero, "rb");
    if (f == NULL) {
        printf("Error de apertura...\n");
        return;
    }
    
    //2.Leo
    fread(&reg, sizeof(struct datosCompra), 1, f);
    //Inicializo companny y total
    if (feof(f)) {
        //El fichero está vacío, no tengo que hacer nada
        printf("Fichero vacío...\n"); fclose(f); return;
    }
    
    faux = fopen("borrar", "wb");
    if(faux == NULL) {
        printf("Error de apertura...\n"); return;
    }
    
    //Introducimos la información de la nueva compra,
    introducirDatosCompra(&regNuevo);
    
    fread(&reg, sizeof(struct datosCompra), 1, f);
    
    while (!feof(f) && strcmp(reg.nombre, regNuevo.nombre) <= 0) {
        
        fwrite(&reg, sizeof(struct datosCompra), 1, faux);
        fread(&reg, sizeof(struct datosCompra), 1, f);
    }
    
    //He encontrado el sitio donde debe de ir la nueva compra
    fwrite(&regNuevo, sizeof(struct datosCompra), 1, faux);
    //ahora tengo que escribir el resto
    while (!feof(f)) {
        fwrite(&reg, sizeof(struct datosCompra), 1, faux);
        fread(&reg, sizeof(struct datosCompra), 1, f);
    }
    
    fclose(f);
    volcar("borrar", nombreFichero);
    
}


void volcar (char nombreFicheroOrigen[], char nombreFicheroDestino []) {
    
    FILE *fOrigen, *fDestino;
    struct datosCompra reg;
    
    fOrigen = fopen(nombreFicheroOrigen, "rb");
    fDestino = fopen(nombreFicheroDestino, "wb");
    if (fOrigen == NULL) {
        return;
    }
    
    fread(&reg, sizeof(struct datosCompra), 1, fOrigen);
    while (!feof(fOrigen)) {
        fwrite(&reg, sizeof(struct datosCompra), 1, fDestino);
        fread(&reg, sizeof(struct datosCompra), 1, fOrigen);

    }
    
    fclose(fOrigen); fclose(fDestino);
    
}
