#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

#define esc 27

void abrirArchivo(FILE *);
void menu();
void puntoAyC(FILE *, char);
void removePunto(char *);
void puntoB(FILE *);
float fpromedio(float, float);
void puntoC(FILE *, char *, char);
void puntoD(FILE *);
float *variaciones(FILE *);
char *replaceChar(char *, char, char);
float mayor(float *lista);
float menor(float *lista);
void tipoDeAccion(FILE *, char *, char);

int main(int argc, char *argv[])
{
    FILE *archivo;
    char opcion;

    archivo = fopen("./EJEMPLO.HTML", "rt");
    abrirArchivo(archivo);

    // scanf("%c", &opcion);
    do
    {
        menu();
        opcion = getch();

        switch (opcion)
        {
        case 'a':
        case 'A':
            puntoAyC(archivo, 'a');
            break;
        case 'b':
        case 'B':
            puntoB(archivo);
            break;
        case 'c':
        case 'C':
            puntoAyC(archivo, 'c');
            break;
        case 'd':
        case 'D':
            puntoD(archivo);
            break;
        case esc:
            break;
        default:
            printf("\n \nElegi alguna de las opciones correctamente! \n \n");
            break;
        }
    } while (opcion != esc);

    fclose(archivo);
    return 0;
}

void abrirArchivo(FILE *file)
{
    if (file == NULL)
    {
        printf("Error al abrir el archivo HTML\n");
        exit(0);
    }
    else
    {
        printf("Archivo HTML abierto correctamente! \n");
        rewind(file);
        return;
    }
}

void menu()
{
    printf("\nElija una opcion: \n");
    printf("A - Acciones cuyo precio al contado al momento de apertura supera los $200 \n");
    printf("B - Listado del promedio de cotizacion de compra y venta de todas las acciones al contado en un archivo .CSV\n");
    printf("C - Lo mismo que el A, pero en formato html \n");
    printf("%s", "D - Acciones que tienen menor y mayor % de variacion \n");
    printf("Esc - Salir \n");
    printf("\n");
}

void puntoAyC(FILE *f, char punto)
{
    char text[100], *textHTML;
    char lastWord[10] = "</table>";
    char *acciones, *precio, accion[20] = "", compra[15], venta[15];

    FILE *html;
    char header[] = "<HTML>\n 	<BODY>\n		<H1> Punto C </H1>\n		<br/>\n		<table border=\"1\" id=\"lideres\" class=\"tabla_cierre\"> <thead><tr class=\"header_table\">\n<th style=\"background-color:white\">Especie</th></tr></thead><tbody>";
    char closeTable[] = "</tbody>\n</table>\n     </BODY>\n</HTML>";
    long numbytes;

    if (punto == 'c')
    {
        html = fopen("./puntoC.html", "w+");
        if (html == NULL)
        {
            printf("Error al crear/abrir el archivo HTML\n");
            exit(0);
        }
        else
        {
            fseek(html, 0L, SEEK_END); // Me trae el tamaño del archivo todo este bloque
            numbytes = ftell(html);
            fseek(html, 0L, SEEK_SET);

            fread(textHTML, sizeof(char), numbytes, html); // Guarda en text lo que hay en f1

            if (numbytes == 0)
            {
                fputs(header, html);
            }
        }
    }
    if (punto == 'a')
    {
        printf("Acciones cuyo precio supera los $200:\n");
    }
    

    while (strstr(text, lastWord) == NULL)
    {
        fscanf(f, "%s", text);
        if (strstr(text, "onclick=\"link('") != NULL)
        {
            acciones = strtok(text, "onclick=\"link('");
            strncpy(accion, acciones, 19);
            do
            {
                fscanf(f, "%s", text);
            } while (strstr(text, "center;\">") == NULL);

            if (strstr(text, "center;\">Cdo.") != NULL)
            {
                do
                {
                    fscanf(f, "%s", text);
                } while (strstr(text, "class=\"ultimo_cierre\"") == NULL);

                do
                {
                    fscanf(f, "%s", text);
                } while (strstr(text, "class=\"ultimo_cierre\"") == NULL);

                precio = strtok(text, "class=\"ultimo_cierre\">");
                precio = strtok(precio, "</");
                removePunto(precio);
                replaceChar(precio, ',', '.');
                strncpy(compra, precio, 14);

                do
                {
                    fscanf(f, "%s", text);
                } while (strstr(text, "class=\"ultimo_cierre\"") == NULL);
                precio = strtok(text, "class=\"ultimo_cierre\">");
                precio = strtok(precio, "</");
                removePunto(precio);
                replaceChar(precio, ',', '.');
                strncpy(venta, precio, 14);

                do
                {
                    fscanf(f, "%s", text);
                } while (strstr(text, "fa-arrow") == NULL);

                precio = strtok(text, "fa-arrow-updownright\"></i></td><td>");
                removePunto(precio);
                replaceChar(precio, ',', '.');

                if (atof(precio) > 200)
                {
                    if (punto == 'a')
                    {
                        printf("-%s \n", accion);
                    }

                    if (punto == 'c')
                    {

                        if (atof(compra) < atof(precio) && atof(venta) < atof(precio))
                        {
                            puntoC(html, accion, 'v');
                        }
                        else
                        {
                            puntoC(html, accion, 'n');
                        }
                    }
                }
            }
        }
    }
    if (punto == 'c')
    {
        fputs(closeTable, html);
        printf("HTML creado correctamente! \n");
        fclose(html);
    }

    rewind(f);
    return;
}

void removePunto(char *str)
{
    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        if (str[i] == '.')
        {
            for (int j = i; j < len; j++)
            {
                str[j] = str[j + 1];
            }
            len--;
            i--;
        }
    }
}

void puntoB(FILE *f)
{
    FILE *excel;
    char text[100], lastWord[10] = "</table>", accion[20] = "", compra[15], venta[15], promedio[15];
    char *acciones, *precio;

    excel = fopen("./puntoB.csv", "w+");
    abrirArchivo(excel);

    if (excel == NULL)
    {
        printf("Error al crear/abrir el archivo CSV\n");
        exit(0);
    }
    else
    {
        printf("Creando Excel... \n");

        fputs("Especie; Precio de compra; Precio de venta; Apertura; Promedio\n", excel);

        while (strstr(text, lastWord) == NULL)
        {
            fscanf(f, "%s", text);
            if (strstr(text, "onclick=\"link('") != NULL)
            {
                acciones = strtok(text, "onclick=\"link('");
                strncpy(accion, acciones, 19);
                do
                {
                    fscanf(f, "%s", text);
                } while (strstr(text, "center;\">") == NULL);

                if (strstr(text, "center;\">Cdo.") != NULL)
                {
                    fputs(accion, excel);
                    fputs("; ", excel);
                    do
                    {
                        fscanf(f, "%s", text);
                    } while (strstr(text, "class=\"ultimo_cierre\"") == NULL);

                    do
                    {
                        fscanf(f, "%s", text);
                    } while (strstr(text, "class=\"ultimo_cierre\"") == NULL);

                    precio = strtok(text, "class=\"ultimo_cierre\">");
                    precio = strtok(precio, "</");
                    removePunto(precio);
                    strncpy(compra, precio, 14);
                    fputs(compra, excel);
                    fputs("; ", excel);

                    do
                    {
                        fscanf(f, "%s", text);
                    } while (strstr(text, "class=\"ultimo_cierre\"") == NULL);
                    precio = strtok(text, "class=\"ultimo_cierre\">");
                    precio = strtok(precio, "</");
                    removePunto(precio);
                    strncpy(venta, precio, 14);
                    fputs(venta, excel);
                    fputs("; ", excel);

                    do
                    {
                        fscanf(f, "%s", text);
                    } while (strstr(text, "fa-arrow") == NULL);

                    precio = strtok(text, "fa-arrow-updownright\"></i></td><td>");
                    removePunto(precio);
                    fputs(precio, excel);
                    fputs("; ", excel);

                    sprintf(promedio, "%0.2f", fpromedio(atof(compra), atof(venta)));
                    replaceChar(promedio, '.', ',');
                    fputs(promedio, excel);
                    fputs(";\n", excel);

                    fscanf(f, "%s", text);
                }
            }
        }
        rewind(f);
        fclose(excel);
        printf("CSV creado correctamente! \n");
        return;
    }
}

float fpromedio(float a, float b)
{
    float resultado;

    resultado = (a + b) / 2;
    return resultado;
}

void puntoC(FILE *html, char accion[], char color)
{
    char body[] = "<tr><td style=\"text-align: center;";
    char verde[] = "color: #10da10\">";
    char closeRow[] = "</td>\n";

    if (color == 'v')
    {
        fputs(body, html);
        fputs(verde, html);
        fputs(accion, html);
        fputs(closeRow, html);
    }
    else
    {
        fputs(body, html);
        fputs("\">", html);
        fputs(accion, html);
        fputs(closeRow, html);
    }

    return;
}

void puntoD(FILE *f)
{
    float *listanums = variaciones(f);

    rewind(f);

    float elMayor = mayor(listanums);
    float elMenor = menor(listanums);
    char elMayorChar[5] = "0,00", elMenorChar[5] = "0,00";

    // gcvt(elMayor, 3, elMayorChar);
    sprintf(elMayorChar, "%0.2f", elMayor);
    replaceChar(elMayorChar, '.', ',');

    tipoDeAccion(f, elMayorChar, 'b');
    rewind(f);
    // gcvt(elMenor, 3, elMenorChar);
    sprintf(elMenorChar, "%0.2f", elMenor);
    replaceChar(elMenorChar, '.', ',');
    tipoDeAccion(f, elMenorChar, 's');
    return;
}

float *variaciones(FILE *f)
{
    char text[100];
    char lastWord[10] = "</table>";
    char *vari;
    static float pvari[60] = {0};
    int i = 0;

    while (strstr(text, lastWord) == NULL)
    {
        fscanf(f, "%s", text);
        if (strstr(text, "style=\"color:#10da10;\">") != NULL || strstr(text, "style=\"color:#e94b46;\">") != NULL || strstr(text, "style=\"color:#267cfc;\">") != NULL)
        {
            vari = strtok(text, ">");
            vari = strtok(NULL, " ");
            vari[strlen(vari) - 1] = '\0';
            vari = replaceChar(vari, ',', '.');
            pvari[i] = fabs(atof(vari));
            i++;
        }
    }
    for (i; i <= 60; i++)
    {
        pvari[i] = 0;
    }

    return pvari;
}

char *replaceChar(char *s, char toReplace, char theReplace)
{
    int i = 0;

    while (s[i] != '\0')
    {
        if (s[i] == toReplace)
        {
            s[i] = theReplace;
        }
        i++;
    }

    return s;
}

float mayor(float lista[])
{
    float mayor = lista[0];
    int i = 0;

    for (i = 0; i < 60; i++)
    {
        if (mayor < lista[i])
        {
            mayor = lista[i];
        }
    }
    return mayor;
}

float menor(float lista[])
{
    float menor = lista[0];
    int i = 0;

    for (i = 0; i < 60; i++)
    {
        if (menor > lista[i])
        {
            menor = lista[i];
        }
    }
    return menor;
}

void tipoDeAccion(FILE *f, char num[], char type)
{
    char text[100];
    char lastWord[10] = "</table>";
    char *acciones;
    char accion[20] = "", *tipo;

    if (type == 'b')
    {
        tipo = "mayor";
    }
    if (type == 's')
    {
        tipo = "menor";
    }

    while (strstr(text, lastWord) == NULL)
    {
        fscanf(f, "%s", text);

        if (strstr(text, "onclick=\"link('") != NULL)
        {
            acciones = strtok(text, "onclick=\"link('");
            strncpy(accion, acciones, 19);
            while (strstr(text, "style=\"color:") == NULL)
            {
                fscanf(f, "%s", text);
            }

            if (strstr(text, num))
            {
                printf("%s %s %s", "Accion/accioneses con", tipo, "% de variacion: ");
                // printf("%s %s", tipo, "% de variacion: ");
                printf("%s con %s", accion, num);
                printf("%s", "%.\n");
            }
        }
    }
}