/*	Grupo 04 - Sistemas Operativos
	Denis Morales 07200100
	Franco Ccopa
	Pedro Cori
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 4096

int fiRepetido(int iNumero,int iArreglo[], int tamArreglo);
int fiBusquedaSecuencial(int iNumero,int iArreglo[], int tamArreglo);

int main(int argc, char const *argv[])
{
	int iArreglo[N];
	int iNumero;
	int i;
	
	//Se llena el arreglo sin numero repetidos
	for (i = 0; i < N; i++)
	{
		do{
			iNumero = rand() % 16384 + 1;
		}while(fiRepetido(iNumero,iArreglo,N));
		iArreglo[i] = iNumero;
		printf("(%i)[%i]\n",i,iArreglo[i]);
	}

	//Se busca un elemento en el arreglo
	int iNumeroABuscar;
	printf("Ingrese numero a buscar: ");
	scanf("%i",&iNumeroABuscar);
	int p = fiBusquedaSecuencial(iNumeroABuscar,iArreglo,N);
	if(p < 1)
		printf("El elemento no esta en el arreglo\n");
	else
		printf("La posicion del numero buscado es: %i\n",p );
}

int fiRepetido(int iNumero,int iArreglo[],int tamArreglo)
{
	int i = 0;
	int encontrado = 0;
	while(!encontrado && i < tamArreglo)
	{
		if(iArreglo[i] == iNumero) 
		{
			printf("Repetido %i, se debe buscar otro numero\n", iNumero);
			encontrado = 1;
		}
		i++;
	}
	return encontrado;
}

int fiBusquedaSecuencial(int iNumero,int iArreglo[], int tamArreglo)
{
	int posicion = -1,i = 0;
	int encontrado = 0;

	while(!encontrado && i < tamArreglo)
	{
		if(iArreglo[i] == iNumero) 
		{
			encontrado = 1;
			posicion = i;
		}
		i++;
	}
	return posicion + 1;
}

