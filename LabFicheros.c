/*
* Autor: Santiago Jose Hernandez
* Fecha: 11 de Noviembre 2025
* Tema: Ficheros
* Objetivo: recibir el nombre de un directorio y muestra los nombres de los archivos y subdirectorios que contiene dicho directorio*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUF 2048
#define TEN_DAYS (10*24*60*60)

static void chomp(char *s) {
    size_t n = strlen(s);
    if (n && (s[n-1] == '\n' || s[n-1] == '\r')) s[n-1] = '\0';
}

int main(void) {
    char nomdir[BUF];
    DIR *d;
    struct dirent *ent;

    printf("Nombre de directorio: ");
    if (!fgets(nomdir, sizeof(nomdir), stdin)) {
        fprintf(stderr, "Error leyendo entrada\n");
        return 1;
    }
    chomp(nomdir);

    d = opendir(nomdir);
    if (!d) {
        perror("No existe ese directorio / no se puede abrir");
        return 1;
    }

    time_t ahora = time(NULL);
    while ((ent = readdir(d)) != NULL) {
        if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
            continue;

        char ruta[BUF];
        snprintf(ruta, sizeof(ruta), "%s/%s", nomdir, ent->d_name);

        struct stat st;
        if (lstat(ruta, &st) != 0) { 
            perror("stat");
            continue;
        }

        unsigned modo = st.st_mode & 07777;
        int owner_read = (st.st_mode & S_IRUSR) ? 1 : 0;
        int es_dir = S_ISDIR(st.st_mode);

        printf("entrada: %s | modo: %04o | R propietario: %s | %s\n",
               ent->d_name,
               modo,
               owner_read ? "SI" : "NO",
               es_dir ? "Directorio" : "Fichero");
 /* si es fichero y fue modificado en los últimos 10 días, imprimir fecha de acceso */
        if (S_ISREG(st.st_mode) && (difftime(ahora, st.st_mtime) <= TEN_DAYS)) {
            char *fa = ctime(&st.st_atime);   /* fecha de último acceso */
            if (fa) {
                printf("  -> Modificado <10d | Último acceso: %s", fa);
            }
        }
    }

    closedir(d);
    return 0;
}
