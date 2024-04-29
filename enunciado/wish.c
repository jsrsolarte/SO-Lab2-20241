#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void imprimir_error()
{
    fprintf(stderr, "An error has occurred\n");
}

void ejecutar_comando(char *comando)
{
    if (strcmp(comando, "exit") == 0)
    {
        return exit(0);
    }

    // Aquí puedes agregar la lógica para procesar los comandos ingresados
    imprimir_error();
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
            input[strcspn(input, "\n")] = '\0';

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
            line[strcspn(line, "\n")] = '\0';

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
