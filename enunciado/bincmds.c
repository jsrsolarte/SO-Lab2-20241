#include "bincmds.h"
#include "utils.h"
#include <stdbool.h>
#include <unistd.h>

char *path = "/bin";

bool es_buildin_cmd(char *comando)
{
    if (strcmp(comando, "exit") == 0)
    {
        return true;
    }
    else if (strcmp(comando, "cd") == 0)
    {
        return true;
    }
    else if (strcmp(comando, "path") == 0)
    {
        return true;
    }
    else if (strcmp(comando, "pathprt") == 0)
    {
        return true;
    }
    return false;
}

void ejecutar_buildin_cmd(char **comando, int palabras_comando)
{
    if (strcmp(comando[0], "exit") == 0)
    {
        if (palabras_comando == 1)
        {
            exit(0);
        }
        else
        {
            imprimir_error();
        }
    }
    else if (strcmp(comando[0], "cd") == 0)
    {
        if (palabras_comando == 2)
        {
            if (chdir(comando[1]) != 0)
            {
                imprimir_error();
            }
        }
        else
        {
            imprimir_error();
        }
    }
    else if (strcmp(comando[0], "path") == 0)
    {
        // Si solo hay una palabra en el comando, simplemente asignamos esa palabra a path
        if (palabras_comando == 1)
        {
            path = malloc(1);
            if (path == NULL)
            {
                printf("Error: No se pudo asignar memoria.\n");
                exit(1);
            }
            path[0] = '\0';
        }
        else
        {
            // Calculamos el tamaño necesario para la nueva cadena
            int newSize = 1; // Para el terminador nulo inicial

            // Calculamos el tamaño total de la nueva cadena y el separador ';' entre cada string
            for (int i = 1; i < palabras_comando; i++)
            {
                newSize += strlen(comando[i]) + 1; // +1 para el separador ';'
            }

            // Si path aún no está asignado, asignamos memoria inicial
            if (path == NULL)
            {
                path = malloc(newSize);
                if (path == NULL)
                {
                    printf("Error: No se pudo asignar memoria.\n");
                    exit(1);
                }
            }
            else
            {
                // Si ya hay memoria asignada, la ajustamos con realloc
                char *temp = realloc(path, newSize);
                if (temp == NULL)
                {
                    printf("Error: No se pudo asignar memoria.\n");
                    exit(1);
                }
                path = temp;
            }

            // Inicializamos path
            path[0] = '\0';

            // Concatenamos cada cadena con ';' excepto la última
            strcat(path, comando[1]);
            for (int i = 2; i < palabras_comando; i++)
            {
                strcat(path, ";");
                strcat(path, comando[i]);
            }
        }
    }
    else if (strcmp(comando[0], "pathprt") == 0)
    {
        printf("%s\n", path);
    }

    else
    {
        imprimir_error();
    }
}

char *obtener_path()
{
    return path;
}
