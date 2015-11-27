/*	Grupo 04 - Sistemas Operativos
	Morales Retamozo, Denis Ricardo		07200100
	Cori Amesquita, Pedro				13200152
	Ccopa Marín, Franco Aldair			13200145
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define TAMANIO 4096


int fiRepetido(int iNumero);
int fiBusquedaSecuencialHilos();

void * fpvhiloBusqueda1( void *h );
void * fpvhiloBusqueda2( void *h );
void * fpvhiloBusqueda3( void *h );
void fvhiloBusqueda4( int *p);
void fvlanzarHilos();

int iEncontro = 0;
int aiArreglo[TAMANIO];
int iNumeroABuscar;

int main(int argc, char const *argv[])
{
	
	int iNumero;
	int iIterador;
	int iPosicionDelElemento;

	//Se llena el arreglo sin numero repetidos
	for (iIterador = 0; iIterador < TAMANIO; iIterador++)
	{
		do{
			iNumero = rand() % 16384 + 1;
		}while(fiRepetido(iNumero));
		aiArreglo[iIterador] = iNumero;
		//vamos imprimiendo todos los numeros y sus indices 
		//para comprobar que se esta haciendo correctamente la busqueda
		//al momento de mirar los resultados
		printf("[%i]=%i ",iIterador+1,aiArreglo[iIterador]);
		if(iIterador % 10 == 0) printf("\n");
	}
	printf("\n");

	//Se pide el elemento a buscar en el arreglo
	printf("Ingrese numero a buscar: ");
	scanf("%i",&iNumeroABuscar);

	//se ejecuta el procedimiento para buscar el elemento y obtener la posicion en el arreglo
	iPosicionDelElemento = fiBusquedaSecuencialHilos();

	//obtenida la posicion, se evalua si es correcta. Si lo es, se imprimira la posicion.
	if(iPosicionDelElemento == 0)
		printf("No se encontro el elemento\n");
	else
		printf("La posicion del elemento en el arreglo es: %i\n",iPosicionDelElemento);

	exit(0);
}

//funcion pedida para buscar el elemento en el arreglo
int fiBusquedaSecuencialHilos()
{
  	int iPosicion = -1;
  	//funcion que lanza los 4 hilos para hacer la busqueda,
  	//se hace paso de valor por referencia para que sea usada por los 4 hilos y alguno la modifique
  	fvlanzarHilos(&iPosicion);
  	//habiendose modificado la variable posicion en alguno de los hilos se retorna la misma.
  	return iPosicion + 1;
}

void fvlanzarHilos( int *p)
{
	pthread_t ptHilo1;
  	pthread_t ptHilo2;
  	pthread_t ptHilo3;

  	int * piPosicion = p;
  	int iRetH1, iRetH2, iRetH3;

  	//Se crean los hilos en busqueda del elemento
  	iRetH1 = pthread_create( &ptHilo1, NULL, fpvhiloBusqueda1, (void *)piPosicion );
  	iRetH2 = pthread_create( &ptHilo2, NULL, fpvhiloBusqueda2, (void *)piPosicion );
  	iRetH3 = pthread_create( &ptHilo3, NULL, fpvhiloBusqueda3, (void *)piPosicion );
  	
  	fvhiloBusqueda4(piPosicion);

  	pthread_join( ptHilo1, NULL );
  	pthread_join( ptHilo2, NULL );
 	pthread_join( ptHilo3, NULL );
  		
}

void * fpvhiloBusqueda1( void *h )
{
	//pasamos la direccion al puntero para poder modificar la variable posicion definida en fiBusquedaSecuencialHilos
	int * piPosEncontrado = (int *) h;
	int iIterador = 0;
	while(!iEncontro && iIterador < 1024)
	{
		if(aiArreglo[iIterador] == iNumeroABuscar) 
		{
			iEncontro = 1;
			*piPosEncontrado = iIterador;// una vez encontrado se modifica la variable posicion
		}
		iIterador++;
	}
}
void * fpvhiloBusqueda2( void *h )
{
	//pasamos la direccion al puntero para poder modificar la variable posicion definida en fiBusquedaSecuencialHilos
	int * piPosEncontrado = (int *) h;
	int iIterador = 1024;
	while(!iEncontro && iIterador < 2048)
	{
		if(aiArreglo[iIterador] == iNumeroABuscar) 
		{
			iEncontro = 1;
			*piPosEncontrado = iIterador;// una vez encontrado se modifica la variable posicion
		}
		iIterador++;
	}
}
void * fpvhiloBusqueda3( void *h )
{
	//pasamos la direccion al puntero para poder modificar la variable posicion definida en fiBusquedaSecuencialHilos
	int * piPosEncontrado = (int *) h;
	int iIterador = 2048;
	while(!iEncontro && iIterador < 3072)
	{
		if(aiArreglo[iIterador] == iNumeroABuscar) 
		{
			iEncontro = 1;
			*piPosEncontrado = iIterador;// una vez encontrado se modifica la variable posicion
		}
		iIterador++;
	}
}
void fvhiloBusqueda4(int *p)
{
	//pasamos la direccion al puntero para poder modificar la variable posicion definida en fiBusquedaSecuencialHilos
	int * piPosEncontrado = p;
	int iIterador = 3072;
	while(!iEncontro && iIterador < 4096)
	{
		if(aiArreglo[iIterador] == iNumeroABuscar) 
		{
			iEncontro = 1;
			*piPosEncontrado = iIterador;// una vez encontrado se modifica la variable posicion
		}
		iIterador++;
	}
}
//funcion para saber si un numero ya esta en el arreglo y asi evitar ingresar alguno repetido
int fiRepetido(int iNumBuscado)
{
	int iIterador = 0;
	int iFueEncontrado = 0;
	while(!iFueEncontrado && iIterador < TAMANIO)
	{
		if(aiArreglo[iIterador] == iNumBuscado) iFueEncontrado = 1;
		iIterador++;
	}
	return iFueEncontrado;
}
