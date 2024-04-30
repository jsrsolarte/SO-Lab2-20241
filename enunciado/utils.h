#include <stdbool.h>

#ifndef UTILS_H
#define UTILS_H

char *terminar_en_nueva_linea(char *str);
char **dividir_por_espacios(char *str, int *count);
void imprimir_error();
char **dividir_array(char **args, int inicio, int fin);
char* separar_por_redireccion(char **comandos, int cantidad);
void imprimir_array(char **array, int cantidad);

void redirigir_salida(char *file_redireccion);

#include "utils.c"
#endif