#include "path_utils.h"

Path path = {
    .path = (char *[]){"/bin"},
    .length = 1};

void cambiar_path(char **nuevo_path, int nuevo_tamanio)
{
    // Asignar el nuevo conjunto de rutas al campo path
    path.path = nuevo_path;
    path.length = nuevo_tamanio;
}

void imprimir_path()
{
    for (int i = 0; i < path.length; i++)
    {
        printf("%s\n", path.path[i]);
    }
}