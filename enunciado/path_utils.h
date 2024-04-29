#ifndef PATH_UTILS_H
#define PATH_UTILS_H

#include <string.h>
#include <stdbool.h>

// Define a structure to represent a path
typedef struct
{
    char **path;
    int length;
} Path;

bool es_path_cmd(char *comando);

void imprimir_path();

void cambiar_path(char **nuevo_path, int nuevo_tamanio);

char *obtener_comando_en_path(const char *comando);

#include "path_utils.c"
#endif // PATH_UTILS_H