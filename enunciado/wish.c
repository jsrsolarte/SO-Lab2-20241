#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "bincmds.h" // Incluye los prototipos de funciones para comandos internos
#include "utils.h"   // Incluye los prototipos de funciones utilitarias
#include "pthcmds.h" // Incluye los prototipos de funciones para comandos externos

void procesar_linea_comandos(char *linea_comando)
{

    // Eliminar el espacio en blanco al principio y al final de la línea de comando
    linea_comando = quitar_espacion_blanco(linea_comando);

    if (linea_comando != NULL && strlen(linea_comando) > 0)
    {

        int cantidad_palabras;
        // Divide la línea de comando en palabras individuales
        char **comando = dividir_por_caracter(linea_comando, ' ', &cantidad_palabras);

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
}

// Función para ejecutar un comando dado
void ejecutar_comando(char *linea_comando)
{
    int cantidad_lineas;
    char **lineas_comandos = dividir_por_caracter(linea_comando, '&', &cantidad_lineas);

    if (cantidad_lineas == 1)
    {
        procesar_linea_comandos(linea_comando);
    }
    else
    {
        pid_t *pid_array = malloc(cantidad_lineas * sizeof(pid_t));

        if (pid_array == NULL)
        {
            perror("Error en la asignación de memoria");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < cantidad_lineas; i++)
        {
            pid_t pid = fork(); // Crear un nuevo proceso hijo

            if (pid < 0)
            {
                perror("Error en fork");
                exit(EXIT_FAILURE);
            }
            else if (pid == 0)
            {
                // En el proceso hijo, procesar la línea de comando correspondiente
                procesar_linea_comandos(lineas_comandos[i]);
                exit(EXIT_SUCCESS); // Importante: salir del proceso hijo después de ejecutar la línea de comando
            }
            else
            {
                // En el proceso padre, almacenar el PID del proceso hijo en el array
                pid_array[i] = pid;
            }
        }

        // Esperar a que todos los procesos hijos terminen
        for (int i = 0; i < cantidad_lineas; i++)
        {
            waitpid(pid_array[i], NULL, 0);
        }

        free(pid_array);
    }
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
