#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void imprimir_error()
{
    fprintf(stderr, "An error has occurred\n");
}

bool ejecutar_comando(char *comando)
{
    if (strcmp(comando, "exit") == 0)
    {
        return false;
    }

    // Aquí puedes agregar la lógica para procesar los comandos ingresados
    imprimir_error();
    return true;
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

            if (!ejecutar_comando(input))
            {
                return 0;
            }
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

            if (!ejecutar_comando(line))
            {
                return 0;
            }
        }

        fclose(file);
    }
    else
    {
        imprimir_error();
    }

    return 0;
}
