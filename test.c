
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct erow 
{
    int size ; 
    char *chars  ; 
}erow;


struct shellConfig 
{    
    int screencols;
    int numrows; 
    erow *row;   
};

struct shellConfig E ;


void shellAppendRow (char *s, size_t len)
{
    //printf("%d\n" ,E.numrows);
    int size = sizeof(erow) * (E.numrows + 1);
    erow *  tmp; 
    tmp = realloc(E.row, size); /* es aqui dinde me da el error */
    if (tmp == NULL)
    {
        perror ("error al reservar memoria");
        exit(1);
    }
    else
    {
        E.row = tmp;
    }
    
    int at = E.numrows;
    E.row[at].size = len;
    E.row[at].chars = malloc(len + 1);
    memcpy(E.row[at].chars, s, len);
    E.row[at].chars[len] = '\0';
    E.numrows++;
}

size_t strncpyaux (char *dest ,const char *src , size_t n , size_t pos)
{
    size_t i;
    size_t r;
    size_t c=0;

    for ( i=0 ; src[i]!='\0' && i < pos; i++ );

    for (; i<pos +n && src[i]!='\0'; i++)
    {
        dest[c++] = src[i];
    }
    for (i=c ; i < pos+ n ; i ++)
    {
        dest[i] = '\0';
    }
    return c ;
}


void printrows ()
{
    int i = 0 ; 
    for (i = 0 ; i < E.numrows ; i++)
    {
        printf("%s\n" , E.row[i].chars);
    }
}

void shellAppendString (char *s ,size_t len)
{
    size_t curr = 0 , auxcurr;
    char *str = NULL; 
    
    while (curr < len)
    {
        str = malloc (E.screencols);
        auxcurr = strncpyaux(str,s,E.screencols,curr);
        curr += auxcurr;
        shellAppendRow(str, auxcurr);
        free (str);
        printf("%ld -> %ld\n",auxcurr,curr);
    }  
}

int main () 
{
    char * src = "estoesunapruebaparaverenquefallaalhacerrealloc";
  
    E.row = NULL;
    E.screencols = 30;
    shellAppendString(src,strlen(src));

    printrows();
    return 0 ;
}
