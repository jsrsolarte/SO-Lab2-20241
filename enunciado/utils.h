#ifndef UTILS_H
#define UTILS_H

char *terminar_en_nueva_linea(char *str);
char **dividir_por_espacios(char *str, int *count);
void imprimir_error();

#include "utils.c"
#endif