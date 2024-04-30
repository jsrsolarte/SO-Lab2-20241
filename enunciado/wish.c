#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "bincmds.h"  // Incluye los prototipos de funciones para comandos internos
#include "utils.h"     // Incluye los prototipos de funciones utilitarias
#include "pthcmds.h"  // Incluye los prototipos de funciones para comandos externos

// Función para ejecutar un comando dado
void ejecutar_comando(char *linea_comando)
{
    int cantidad_palabras;

    // Elimina el caracter de nueva línea si está presente al final de la línea de comando
    linea_comando = terminar_en_nueva_linea(linea_comando);

    // Divide la línea de comando en palabras individuales
    char **comando = dividir_por_espacios(linea_comando, &cantidad_palabras);

    // Verifica si el comando es un comando interno
    if (es_buildin_cmd(comando[0]))
    {
        ejecutar_buildin_cmd(comando, cantidad_palabras); // Ejecuta el comando interno
    }
    // Verifica si el comando es un ejecutable en la ruta especificada
    else if (es_path_ejecutable(comando[0]))
    {
        ejecutar_comando_path(comando, cantidad_palabras); // Ejecuta el comando externo
    }
    else
    {
        imprimir_error(); // Imprime un mensaje de error si el comando no es reconocido
    }

    free(comando); // Libera la memoria asignada para almacenar el comando dividido
}

int main(int argc, char *argv[])
{
    char input[100];

    // Verifica si se proporcionaron argumentos de línea de comandos
    if (argc == 1)
    {
        // Bucle para leer y ejecutar comandos desde la entrada estándar
        while (1)
        {
            printf("wish> ");
            fgets(input, sizeof(input), stdin); // Lee la línea de comando

            ejecutar_comando(input); // Ejecuta el comando ingresado
        }
    }
    // Verifica si se proporcionó un archivo de script como argumento
    else if (argc == 2)
    {
        FILE *file = fopen(argv[1], "r"); // Abre el archivo en modo lectura
        if (file == NULL)
        {
            imprimir_error(); // Imprime un mensaje de error si no se puede abrir el archivo
            return 1;
        }

        char line[100];
        // Lee cada línea del archivo y ejecuta el comando correspondiente
        while (fgets(line, sizeof(line), file))
        {
            ejecutar_comando(line); // Ejecuta el comando de la línea actual
        }

        fclose(file); // Cierra el archivo después de leer todas las líneas
    }
    else
    {
        imprimir_error(); // Imprime un mensaje de error si se proporcionan demasiados argumentos
        return 1;
    }

    return 0;
}
