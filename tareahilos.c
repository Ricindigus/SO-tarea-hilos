/*	Grupo 04 - Sistemas Operativos
	Denis Morales 07200100
	Franco Ccopa
	Pedro Cori
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 4096


int fiRepetido(int iNumero);
int fiBusquedaSecuencialHilos();

void * hiloBusqueda1( void *h );
void * hiloBusqueda2( void *h );
void * hiloBusqueda3( void *h );
void hiloBusqueda4( int *p);
void lanzarHilos();

int iEncontro = 0;
int iArreglo[N];
int iNumeroABuscar;

int main(int argc, char const *argv[])
{
	
	int iNumero;
	int i;

	//Se llena el arreglo sin numero repetidos
	for (i = 0; i < N; i++)
	{
		do{
			iNumero = rand() % 16384 + 1;
		}while(fiRepetido(iNumero));
		iArreglo[i] = iNumero;
		//vamos imprimiendo todos los numeros y sus indices 
		//para comprobar que se esta haciendo correctamente la busqueda
		//al momento de mirar los resultados
		printf("[%i]=%i ",i+1,iArreglo[i]);
		if(i % 10 == 0) printf("\n");
	}
	printf("\n");

	//Se pide el elemento a buscar en el arreglo
	printf("Ingrese numero a buscar: ");
	scanf("%i",&iNumeroABuscar);

	//se ejecuta el procedimiento para buscar el elemento y obtener la posicion en el arreglo
	int posicionDelElemento = fiBusquedaSecuencialHilos();

	//obtenida la posicion, se evalua si es correcta. Si lo es, se imprimira la posicion.
	if(posicionDelElemento == 0)
		printf("No se encontro el elemento\n");
	else
		printf("La posicion del elemento en el arreglo es: %i\n",posicionDelElemento);

	exit(0);
}

//funcion pedida para buscar el elemento en el arreglo
int fiBusquedaSecuencialHilos()
{
  	int posicion = -1;
  	//funcion que lanza los 4 hilos para hacer la busqueda,
  	//se hace paso de valor por referencia para que sea usada por los 4 hilos y alguno la modifique
  	lanzarHilos(&posicion);
  	//habiendose modificado la variable posicion en alguno de los hilos se retorna la misma.
  	return posicion + 1;
}

void lanzarHilos( int *p)
{
	pthread_t hilo1;
  	pthread_t hilo2;
  	pthread_t hilo3;
  	pthread_t hilo4;

  	int * pos = p;
  	int iHilo1, iHilo2, iHilo3, iHilo4;

  	//Se crean los hilos en busqueda del elemento
  	iHilo1 = pthread_create( &hilo1, NULL, hiloBusqueda1, (void *)pos );
  	iHilo2 = pthread_create( &hilo2, NULL, hiloBusqueda2, (void *)pos );
  	iHilo3 = pthread_create( &hilo3, NULL, hiloBusqueda3, (void *)pos );
  	
  	hiloBusqueda4(pos);

  	pthread_join( hilo1, NULL );
  	pthread_join( hilo2, NULL );
 	pthread_join( hilo3, NULL );
  		
}

void * hiloBusqueda1( void *h )
{
	int * posEncontrado = (int *) h;
	int i = 0;
	while(!iEncontro && i < 1024)
	{
		if(iArreglo[i] == iNumeroABuscar) 
		{
			iEncontro = 1;
			*posEncontrado = i;
		}
		i++;
	}
}
void * hiloBusqueda2( void *h )
{
	int * posEncontrado = (int *) h;
	int i = 1024;
	while(!iEncontro && i < 2048)
	{
		if(iArreglo[i] == iNumeroABuscar) 
		{
			iEncontro = 1;
			*posEncontrado = i;
		}
		i++;
	}
}
void * hiloBusqueda3( void *h )
{
	int * posEncontrado = (int *) h;
	int i = 2048;
	while(!iEncontro && i < 3072)
	{
		if(iArreglo[i] == iNumeroABuscar) 
		{
			iEncontro = 1;
			*posEncontrado = i;
		}
		i++;
	}
}
void hiloBusqueda4(int *p)
{
	int * posEncontrado = p;
	int i = 3072;
	while(!iEncontro && i < 4096)
	{
		if(iArreglo[i] == iNumeroABuscar) 
		{
			iEncontro = 1;
			*posEncontrado = i;
		}
		i++;
	}
}
//funcion para saber si un numero ya esta en el arreglo y asi evitar ingresar alguno repetido
int fiRepetido(int iNumero)
{
	int i = 0;
	int encontrado = 0;
	while(!encontrado && i < N)
	{
		if(iArreglo[i] == iNumero) encontrado = 1;
		i++;
	}
	return encontrado;
}
