#include "path_utils.h"
#include <unistd.h>
#include <stdbool.h>

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

bool es_path_ejecutable(char *comando)
{
    return obtener_path_ejecutable(comando) != NULL;
}

char *obtener_path_ejecutable(const char *comando)
{
    // Iterar sobre los directorios en el path
    for (int i = 0; i < path.length; i++)
    {
        size_t ruta_completa_len = strlen(path.path[i]) + strlen(comando) + 2;
        char ruta_completa[ruta_completa_len];
        snprintf(ruta_completa, sizeof(ruta_completa), "%s/%s", path.path[i], comando);

        // Verificar si el archivo es accesible
        if (access(ruta_completa, X_OK) == 0)
        {
            char *ruta_completa_copy = malloc(strlen(ruta_completa) + 1);
            strcpy(ruta_completa_copy, ruta_completa);
            return ruta_completa_copy;
        }
    }
    // El ejecutable no fue encontrado en ninguna de las rutas del path
    return NULL;
}