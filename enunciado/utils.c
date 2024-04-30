#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

char *terminar_en_nueva_linea(char *str)
{
    char *ptr = strchr(str, '\n');
    if (ptr != NULL)
    {
        *ptr = '\0';
    }

    // Eliminar espacios en blanco al inicio
    while (*str && *str == ' ')
    {
        str++;
    }

    // Eliminar espacios en blanco al final
    char *end = str + strlen(str) - 1;
    while (end > str && *end == ' ')
    {
        *end-- = '\0';
    }

    return str;
}

char **dividir_por_espacios(char *str, int *count)
{
    int i, j, k = 0, len = strlen(str);
    *count = 0;

    // Contar la cantidad de palabras
    for (i = 0; i < len; i++)
    {
        if (str[i] == ' ')
        {
            (*count)++;
        }
    }
    (*count)++; // Contar la última palabra

    // Reservar memoria para el arreglo de palabras
    char **words = (char **)malloc((*count + 1) * sizeof(char *));
    if (words == NULL)
    {
        fprintf(stderr, "Error de asignación de memoria\n");
        exit(1);
    }

    // Extraer las palabras
    for (i = 0; i < *count; i++)
    {
        // Encontrar la longitud de la palabra
        for (j = k; j < len && str[j] != ' '; j++)
            ;
        // Reservar memoria para la palabra
        words[i] = (char *)malloc((j - k + 1) * sizeof(char));
        if (words[i] == NULL)
        {
            fprintf(stderr, "Error de asignación de memoria\n");
            for (int l = 0; l < i; l++)
            {
                free(words[l]); // Liberar la memoria asignada anteriormente
            }
            free(words);
            exit(1);
        }
        // Copiar la palabra
        strncpy(words[i], str + k, j - k);
        words[i][j - k] = '\0'; // Agregar el carácter nulo al final
        k = j + 1;              // Avanzar k al siguiente espacio
    }
    words[*count] = NULL; // Establecer el último elemento como NULL

    return words;
}

char **dividir_array(char **args, int inicio, int fin)
{
    int cantidad_argumentos = fin - inicio;
    if (cantidad_argumentos <= 0 || inicio < 0)
    {
        return NULL; // Manejo de error: índices incorrectos o ningún argumento para dividir
    }

    char **argumentos = malloc(sizeof(char *) * cantidad_argumentos);
    if (argumentos == NULL)
    {
        fprintf(stderr, "Error de asignación de memoria\n");
        exit(1);
    }

    for (int i = 0; i < cantidad_argumentos; i++)
    {
        argumentos[i] = strdup(args[inicio + i]); // strdup hace malloc y strcpy en una sola llamada
        if (argumentos[i] == NULL)
        {
            fprintf(stderr, "Error de asignación de memoria\n");
            for (int j = 0; j < i; j++)
            {
                free(argumentos[j]); // Liberar la memoria asignada anteriormente
            }
            free(argumentos);
            exit(1);
        }
    }

    return argumentos;
}

void imprimir_error()
{
    char error_message[30] = "An error has occurred\n";
    write(STDERR_FILENO, error_message, strlen(error_message));
}

bool tiene_redireccion(char **comandos, int cantidad)
{
    for (int i = 0; i < cantidad; i++)
    {
        if (strcmp(comandos[i], ">") == 0)
        {
            return true;
        }
    }
    return false;
}

char *separar_por_redireccion(char **comandos, int cantidad)
{
    char *argumento_despues = NULL;

    if (cantidad <= 1)
    {
        // Si hay menos de dos elementos, no hay comandos que procesar
        comandos[0] = NULL;
        return NULL;
    }

    if (strcmp(comandos[0], ">") == 0)
    {
        // Si el primer comando es '>', el segundo comando es el argumento de redirección
        if (cantidad >= 3)
        {
            argumento_despues = strdup(comandos[1]);
            comandos[0] = NULL; // Establecer el primer elemento como NULL
            comandos[1] = NULL; // Establecer el segundo elemento como NULL
        }
        else
        {
            comandos[0] = NULL; // Establecer el primer elemento como NULL
        }
        return argumento_despues;
    }

    int indice_redireccion = -1;

    for (int i = 0; i < cantidad; i++)
    {
        if (strcmp(comandos[i], ">") == 0)
        {
            // Encontramos el operador de redirección
            indice_redireccion = i;
            break;
        }
    }

    if (indice_redireccion != -1 && indice_redireccion + 2 == cantidad)
    {
        // Si encontramos el operador de redirección y hay exactamente un argumento después
        argumento_despues = strdup(comandos[indice_redireccion + 1]);

        // Eliminar los elementos después del operador de redirección
        for (int i = indice_redireccion; i < cantidad; i++)
        {
            comandos[i] = NULL;
        }
    }

    return argumento_despues;
}

void imprimir_array(char **array, int cantidad)
{
    for (int i = 0; i < cantidad; i++)
    {
        printf("%s\n", array[i]);
    }
}

void redirigir_salida(char *file_redireccion)
{
    FILE *file = fopen(file_redireccion, "w");
    if (file == NULL)
    {
        imprimir_error();
        return;
    }
    // Redirigir stdout al descriptor de archivo del archivo abierto
    dup2(fileno(file), STDOUT_FILENO);
    // Cerrar el archivo después de la redirecció
    fclose(file);
}