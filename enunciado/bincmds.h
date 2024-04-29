#include <stdbool.h>
#ifndef BINCMDS_H
#define BINCMDS_H

bool es_buildin_cmd(char *comando);
void ejecutar_buildin_cmd(char **comando, int palabras_comando);

char * obtener_path();

#include "bincmds.c"
#endif