#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *terminar_en_nueva_linea(char *str)
{
    str[strcspn(str, "\n")] = '\0';
    return str;
}

char **dividir_por_espacios(char *str, int *count)
{
      int i, j, k = 0, len = strlen(str);
    *count = 0;

    // Contar la cantidad de palabras
    for (i = 0; i < len; i++) {
        if (str[i] == ' ') {
            (*count)++;
        }
    }
    (*count)++; // Contar la última palabra

    // Reservar memoria para el arreglo de palabras
    char **words = (char **)malloc(*count * sizeof(char *));
    if (words == NULL) {
        fprintf(stderr, "Error de asignación de memoria\n");
        exit(1);
    }

    // Extraer las palabras
    for (i = 0; i < *count; i++) {
        // Encontrar la longitud de la palabra
        for (j = k; j < len && str[j] != ' '; j++);
        // Reservar memoria para la palabra
        words[i] = (char *)malloc((j - k + 1) * sizeof(char));
        if (words[i] == NULL) {
            fprintf(stderr, "Error de asignación de memoria\n");
            exit(1);
        }
        // Copiar la palabra
        strncpy(words[i], str + k, j - k);
        words[i][j - k] = '\0'; // Agregar el carácter nulo al final
        k = j + 1; // Avanzar k al siguiente espacio
    }

    return words;
}

void imprimir_error()
{
    fprintf(stderr, "An error has occurred\n");
}