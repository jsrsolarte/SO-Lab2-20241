#ifndef PATH_UTILS_H
#define PATH_UTILS_H

#include <string.h>

// Define a structure to represent a path
typedef struct {
    char** path;
    int length;
} Path;

// Function to check if a path exists
int path_exists(const char* path);

void imprimir_path();

void cambiar_path(char** nuevo_path, int nuevo_tamanio);


#include "path_utils.c"
#endif // PATH_UTILS_H