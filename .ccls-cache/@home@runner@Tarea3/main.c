#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include "hashmap.h"
#include "list.h"
#include "treemap.h"

int lower_than_string(void* , void*);
char* quitarSalto(char* linea);

typedef struct{
  char nombre[30];
  char fecha[30];
  void* valoracion;
  void* precio;
}Videojuego;



int main(void) {
  
  int opcion;
  Pair *aux;
  Videojuego *v;
  
  HashMap* mapaJuegos = createMap(100);
  TreeMap* mapPrecio = createTreeMap(lower_than_string);
  TreeMap* mapValoracion = createTreeMap(lower_than_string);

  
  
  while(opcion!=0)
  {
    do{
      /*Menú que muestra en pantalla las opciones que podemos 
      realizar*/
      printf("\n Introduzca una opción (1-9)");
      printf("\n 1.Importar archivo de juegos");
      printf("\n 2.Agregar juego");
      printf("\n 3.Mostrar juegos por precio");
      printf("\n 4.Filtrar juegos por valoración");
      printf("\n 5.Mostrar juegos del año");
      printf("\n 6.Buscar juego");
      printf("\n 7.Exportar datos");
      printf("\n 0.Salir");
      printf("\n");
  
      fflush(stdin);
      scanf("%i",&opcion);
      getchar(); 
      printf("\n");
    }while (opcion>10 && opcion<1);
  
    switch(opcion)
    {
      case 2://agregar
      v = (Videojuego*) malloc(sizeof(Videojuego));
        
      printf("Ingrese nombre del videojuego: ");
      fgets(v->nombre,30,stdin);
      strcpy(v->nombre, quitarSalto(v->nombre));
        
      printf("Ingrese año de salida: ");
      fgets(v->fecha,30,stdin);
      strcpy(v->fecha, quitarSalto(v->fecha));
        
      printf("Ingrese valoración del videojuego: ");
      scanf("%i", (int*)&v->valoracion);
        
      printf("Ingrese precio del videojuego: ");
      scanf("%i",(int*)&v->precio);
        
      void *precio;
      precio = v->precio;
      aux  = searchMap(mapaJuegos, v->nombre);
      if(aux == NULL)
      {
        insertMap(mapaJuegos, v->nombre, v);

        insertTreeMap(mapPrecio, v->precio, v->nombre);
        insertTreeMap(mapValoracion,v->valoracion, v->nombre);
        
      }
        
      break;
    }
  }

  
  return 0;
}

int lower_than_string(void* key1, void* key2)
{
    char* k1=(char*) key1;
    char* k2=(char*) key2;
    if(strcmp(k1,k2)<0) return 1;
    return 0;
}

char* quitarSalto(char* linea)
{
  if ((strlen(linea) > 0) && (linea[strlen(linea) - 1] == '\n'))
  {
    linea[strlen(linea) - 1] = '\0';
  }
  return(linea);
}
    