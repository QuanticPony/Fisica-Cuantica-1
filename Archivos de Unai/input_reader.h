#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#ifndef URAN_INPUT_H_INCLUDED
#define URAN_INPUT_H_INCLUDED

typedef struct input_reader
{
    /* data */
}input_reader;


int lee_configuracion(input_reader *Config)
{
    /**Copiamos el fichero para poder leerlo y editarlo**/
    FILE *F;    //Archivo que tiene los parametros del programa
    unsigned int Fsize;
    char *Fcopy;

    F = fopen("config.conf", "rt");

    //Vemos el tama�o del archivo
    fseek(F, 0, SEEK_END);
    Fsize = ftell(F);
    rewind(F);

    //Asignamos tama�o a la copia del archivo
    Fcopy = (char *)malloc(sizeof(char) * Fsize);

    fread(Fcopy, 1, Fsize, F);

    fclose(F);

    /**Archivo copiado a Fcopy. Ahora leemos lo que pasa:**/






    char *p;
    char s[25];

    /**Obtencion de parametros previos del programa**/

    strcpy(s, "N_atoms=");
    p = strstr(Fcopy, s);
    Config->N = atoi(p + strlen(s));
    if (Config->N < 1)
    {
        printf("ERROR:valor de N_atoms invalido\n");
        free(Fcopy);
        return 0;
    }

    strcpy(s, "M_neutrons=");
    p = strstr(Fcopy, s);
    Config->M = atoi(p + strlen(s));
    if (Config->M < 1)
    {
        printf("ERROR:valor de M_neutrons invalido\n");
        free(Fcopy);
        return 0;
    }


    strcpy(s, "Lx=");
    p = strstr(Fcopy, s);
    Config->Lx = atof(p + strlen(s));
    if (Config->Lx < 0)
    {
        printf("ERROR:valor de Lx no valido\n");
        free(Fcopy);
        return 0;
    }

    strcpy(s, "Ly=");
    p = strstr(Fcopy, s);
    Config->Ly = atof(p + strlen(s));
    if (Config->Ly < 0)
    {
        printf("ERROR:valor de Ly no valido\n");
        free(Fcopy);
        return 0;
    }

    strcpy(s, "Lz=");
    p = strstr(Fcopy, s);
    Config->Lz = atof(p + strlen(s));
    if (Config->Lz < 1)
    {
        printf("ERROR:valor de Lz no valido\n");
        free(Fcopy);
        return 0;
    }

    strcpy(s, "de=");
    p = strstr(Fcopy, s);
    Config->de = atof(p + strlen(s));
    if (Config->de < 0)
    {
        printf("ERROR:valor de 'de' no valido\n");
        free(Fcopy);
        return 0;
    }

    strcpy(s, "time=");
    p = strstr(Fcopy, s);
    Config->t_total = atof(p + strlen(s));
    if (Config->t_total <= 0)
    {
        printf("ERROR:valor de time no valido\n");
        free(Fcopy);
        return 0;
    }

    strcpy(s, "dh=");
    p = strstr(Fcopy, s);
    Config->dh = atof(p + strlen(s));
    if (Config->dh <= 0)
    {
        printf("ERROR:valor de dh no valido\n");
        free(Fcopy);
        return 0;
    }

    strcpy(s, "Niter=");
    p = strstr(Fcopy, s);
    Config->Niter = atoi(p + strlen(s));
    if (Config->Niter < 1)
    {
        printf("ERROR:valor de Niter no valido\n");
        free(Fcopy);
        return 0;
    }


    free(Fcopy);
    return 1;
}

#endif //URAN_INPUT_H_INCLUDED