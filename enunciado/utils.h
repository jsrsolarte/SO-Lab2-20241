#ifndef UTILS_H
#define UTILS_H

char *terminar_en_nueva_linea(char *str);
char **dividir_por_espacios(char *str, int *count);
void imprimir_error();
char** seleccionar_argumentos(char **args, int inicio, int fin);

#include "utils.c"
#endif