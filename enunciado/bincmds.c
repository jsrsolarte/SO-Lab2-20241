#include "bincmds.h"
#include "utils.h"
#include <stdbool.h>
#include <unistd.h>

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
    else
    {
        imprimir_error();
    }
}