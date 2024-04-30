#include "pthcmds.h"
#include "path_utils.h"
#include <stdbool.h>

void ejecutar_comando_path(char **comando, int palabras_comando)
{
    char *comando_path = obtener_path_ejecutable(comando[0]);

    // Separar los comandos
    bool redireccion = tiene_redireccion(comando, palabras_comando);

    int pid = fork();
    if (pid == 0)
    {

        if (redireccion)
        {
            char *file_redireccion = NULL;
            file_redireccion = separar_por_redireccion(comando, palabras_comando);
            if (file_redireccion != NULL)
            {
                redirigir_salida(file_redireccion);
            }
            else
            {
                imprimir_error();
                return;
            }
        }

        execv(comando_path, comando);
        imprimir_error();

        // Si execv falla, imprime un mensaje de error y sale
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