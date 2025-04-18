#include <stdio.h>
#include <string.h>

struct tipoAsignatura {
    char codigoAsignatura [9];
    char nombre [31];
    int curso;
};

void generarFichero (char nombreFichero []);
void leerFichero (char nombreFichero []);
void eliminarFichero (char nombreFichero [], char codigoEliminar []);
void volcar (char nombreFicheroOrigen [], char nombreFicheroDestino []);

int main (void) {
    
    char nombre [31], codigo [8];
    
    printf("Introduce el nombre del fichero: "); fflush(stdin);
    scanf("%s", nombre);
    
    //1.Genera el fichero con la info. de la asignatura:
    generarFichero(nombre);
    
    //2.Leer Fichero:
    leerFichero(nombre);
    
    //3.Eliminar asignatura por código:
    printf("Introduce el código de la asignatura a eliminar: "); fpurge(stdin);
    scanf("%s", codigo);
    eliminarFichero(nombre, codigo);
    
    leerFichero(nombre);
    
    printf("\nSaliendo... --> ");
    return 0;
}

void leerFichero (char nombreFichero []) {
    
    FILE *f;
    struct tipoAsignatura asignatura;
    
    //1.Abrir el fichero:
    f = fopen(nombreFichero, "rb"); //OJO abrimos en modo lectura.
    if(f == NULL) {
        printf("Error de apertura...\n"); return;
    }
    
    //2.Leo:
    fread(&asignatura, sizeof(struct tipoAsignatura), 1, f);
    while (!feof(f)) { //Mientras no leas la marca de fin de fichero
        //Hago tratamiento con lo que he leído
        printf("\n|Código: %s | Nombre: %s | Curso: %d|\n", asignatura.codigoAsignatura, asignatura.nombre, asignatura.curso);
        
        
        //Leo
        fread(&asignatura, sizeof(struct tipoAsignatura), 1, f);
    }
    
    //3.Cierro:
    fclose(f);
}

void generarFichero (char nombreFichero []) {
    
    FILE *f;
    struct tipoAsignatura asignatura;
    int opc;
    
    //1.Abrir el fichero
    f = fopen(nombreFichero, "wb");
    if (f==NULL) {
        printf("Error... de apertura.\n"); return;
    }
    
    //2. Escribe Escribe Escribe
    do {
        printf("\n---------------------------------------\n");
        printf("\nIntroduce los datos de la asignatura:\n");
        printf("\t-Código: "); fpurge(stdin);
        scanf("%s", asignatura.codigoAsignatura);
        printf("\t-Nombre: "); fpurge(stdin);
        scanf("%s", asignatura.nombre);
        printf("\t-Curso: "); fpurge(stdin);
        scanf("%d", &asignatura.curso);
        
        //Escribe:
        fwrite(&asignatura, sizeof(struct tipoAsignatura), 1, f);
        
        printf("\nQuieres seguir (0 para parar de escribir): "); scanf("%d", &opc);
    } while (opc != 0);
    
    //3.Cierra
    fclose(f);
}

void eliminarFichero (char nombreFichero [], char codigoEliminar []) {
    
    FILE *fAsig, *fAux; //Necesito un auxiliar para poder eliminar información
    struct tipoAsignatura asignatura;
    
    fAsig = fopen(nombreFichero, "rb");
    fAux = fopen("borrame", "wb");
    
    if (fAux == NULL || fAsig == NULL) {
        printf("Error... de apertura."); return;
    }
    
    //Leo del original:
    fread(&asignatura, sizeof(struct tipoAsignatura), 1, fAsig);
    
    while (!feof(fAsig) && strcmp(asignatura.codigoAsignatura, codigoEliminar) != 0) {
        
        //Hago el tratamiento
        if (strcmp(asignatura.codigoAsignatura, codigoEliminar)) {
            //Si no es la que queremos borrar:
            //La escribo en el auxiliar:
            fwrite(&asignatura, sizeof(struct tipoAsignatura), 1, fAux);
        }
        
        if (feof(fAsig)) {
            
            printf("\nAsignatura no encontrada.\n");
            fclose(fAux);
            remove("borrame");
        } else {
            
            fread(&asignatura, sizeof(struct tipoAsignatura), 1, fAsig);
            while (!feof(fAsig)) {
                //Escribir el resto de asignaturas:
                fwrite(&asignatura, sizeof(struct tipoAsignatura), 1, fAux);
                //Leo:
                fread(&asignatura, sizeof(struct tipoAsignatura), 1, fAsig);
            }
            fclose(fAux); fclose(fAsig);
            //Volcar del auxiliar al original:
            void volcar ("borrame", nombreFichero);
        }
        
        //Leo
        fread(&asignatura, sizeof(struct tipoAsignatura), 1, fAsig);
    }
}

//Volcar del auxiliar al original:
void volcar (char nombreFicheroOrigen [], char nombreFicheroDestino []) {
    
    FILE *fAsig, *fAux; //Necesito un auxiliar para poder eliminar información
    struct tipoAsignatura asignatura;
    
    fAsig = fopen(nombreFichero, "rb");
    fAux = fopen("borrame", "wb");
    
    if (fAux == NULL || fAsig == NULL) {
        printf("Error... de apertura."); return;
    }
    
}
