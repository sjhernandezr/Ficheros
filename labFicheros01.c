/*
* Autor: Santiago Jose Hernandez Rendon
* Fecha: 11 de Noviembre 2025
* Tema: Ficheros
* Resumen: Programa que lee de teclado el nombre de un directorio y muestra en pantalla el nombre y el tamaño de los ficheros que contiene.
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int main() {
    DIR *d;
    char nomdir[90], nomfich[90];
    struct stat datos;
    struct dirent *direc;

    printf("Introduzca el nombre de un directorio: ");
    fgets(nomdir, sizeof(nomdir), stdin);
    nomdir[strlen(nomdir) - 1] = '\0'; // Eliminar salto de línea

    if ((d = opendir(nomdir)) == NULL) {
        printf("El directorio no existe\n");
        return -1;
    }

    while ((direc = readdir(d)) != NULL) {
        strcpy(nomfich, nomdir);
        strcat(nomfich, "/");
        strcat(nomfich, direc->d_name);

        if (stat(nomfich, &datos) == 0 && S_ISREG(datos.st_mode)) {
            printf("Nombre: %s\tTamaño: %ld bytes\n", direc->d_name, datos.st_size);
        }
    }

    closedir(d);
    return 0;
}
