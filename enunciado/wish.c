#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bincmds.h"
#include "utils.h"
#include <sys/wait.h>

void ejecutar_comando(char *linea_comando)
{
    linea_comando = terminar_en_nueva_linea(linea_comando);

    int cantidad_palabras;
    char **comando = dividir_por_espacios(linea_comando, &cantidad_palabras);

    if (es_buildin_cmd(comando[0]))
    {
        ejecutar_buildin_cmd(comando, cantidad_palabras);
    }
    else if (es_path_cmd(comando[0]))
    {
        char *comando_path = obtener_comando_en_path(comando[0]);

        int pid = fork();
        if (pid == 0)
        {
            execv(comando_path, comando);
            // Si execv falla, imprime un mensaje de error y sale
            imprimir_error();
        }
        else if (pid < 0)
        {
            imprimir_error();
        }
        else
        {
            wait(NULL); // Espera a que el proceso hijo termine
        }
    }

    else
    {
        imprimir_error();
    }

    free(comando);
}

int main(int argc, char *argv[])
{
    char input[100];

    if (argc == 1)
    {
        while (1)
        {
            printf("wish> ");
            fgets(input, sizeof(input), stdin);

            ejecutar_comando(input);
        }
    }
    else if (argc == 2)
    {
        FILE *file = fopen(argv[1], "r");
        if (file == NULL)
        {
            imprimir_error();
        }

        char line[100];
        while (fgets(line, sizeof(line), file))
        {
            ejecutar_comando(line);
        }

        fclose(file);
    }
    else
    {
        imprimir_error();
    }

    return 0;
}
