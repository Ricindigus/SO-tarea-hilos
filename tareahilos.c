#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 4096

int fiRepetido(int iNumero,int iArreglo[],int tamArreglo);

int main(int argc, char const *argv[])
{
	int iArreglo[N];
	int iNumero;
	int i;
	for (i = 0; i < N; i++)
	{
		do{
			iNumero = rand() % 16384 + 1;
		}while(fiRepetido(iNumero,iArreglo,N));
		iArreglo[i] = iNumero;
		printf("(%i)[%i]\n",i,iArreglo[i]);
	}
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


