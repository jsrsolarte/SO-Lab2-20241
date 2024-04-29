#include <stdio.h>
#include <string.h>

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
            if (strcmp(input, "exit") == 0)
            {
                return 0;
            }

            // Aquí puedes agregar la lógica para procesar los comandos ingresados
            fprintf(stderr, "An error has occurred\n");
        }
    }
    else if (argc == 2)
    {
        FILE *file = fopen(argv[1], "r");
        if (file == NULL)
        {
            fprintf(stderr, "An error has occurred\n");
            return 1;
        }

        char line[100];
        while (fgets(line, sizeof(line), file))
        {
            line[strcspn(line, "\n")] = '\0';

            if (strcmp(line, "exit") == 0)
            {
                return 0;
            }

            // Aquí puedes agregar la lógica para procesar cada línea del archivo
            fprintf(stderr, "An error has occurred\n");
        }

        fclose(file);
    }
    else
    {
        fprintf(stderr, "An error has occurred\n");
        return 1;
    }

    return 0;
}
