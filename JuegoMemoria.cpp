#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int pedirDatos()
{
	int numeroCartas;
	do
	{
		system("cls");
		printf("Por favor introduzca el numero de cartas con las que jugar: ");
		scanf("%d",&numeroCartas);
		if(numeroCartas%2 == 0)
		{
			if(numeroCartas <= 2)
			{
				printf("\nERROR! Introduzca un numero mayor a 2 de cartas\n\n");
			}
			else
			{
				return numeroCartas;
			}
		}
		else
		{
			printf("\nERROR! Introduzca un numero par de cartas\n\n");
		}
	}while(numeroCartas%2 != 0 || numeroCartas <= 2);
}

void llenarTablero(int *apunTablero, int tam)
{
	for(int i=0;i<2;i++)
	{
		for(int j=0;j<tam;j++)
		{
			*apunTablero = 0;
			apunTablero++;
		}
	}
}

void imprimirTablero(int *apunTablero, int tam)
{
	printf("\n==========TABLERO==========\n\n");
	for(int i=0;i<2;i++)
	{
		for(int j=0;j<tam;j++)
		{
			printf("[%d]  ",*apunTablero);
			apunTablero++;
		}
		printf("\n");
	}
}

void llenarTableroReal(int *apunTableroReal, int tam)
{
	int cont = 1;
	for(int i=0;i<2;i++)
	{
		for(int j=0;j<tam;j++)
		{
			*apunTableroReal = 0;
			apunTableroReal++;
		}
	}
	apunTableroReal-=2*tam;
	srand(time(NULL));
	int total = 0, numeroVeces = 0, aux = 2*tam;
	while(total < aux)
	{
		int r = ( rand() % (aux) ) + 1;
		apunTableroReal += (r-1);
		if(*apunTableroReal == 0)
		{
			*apunTableroReal = tam;
			numeroVeces++;
			if(numeroVeces == 2)
			{
				numeroVeces = 0;
				tam--;
			}
			total++;
		}
		apunTableroReal -= (r-1);
	}
}

void imprimirTableroReal(int *apunTableroReal, int tam)
{
	printf("\n==========TABLERO REAL==========\n\n");
	for(int i=0;i<2;i++)
	{
		for(int j=0;j<tam;j++)
		{
			printf("[%d]  ",*apunTableroReal);
			apunTableroReal++;
		}
		printf("\n");
	}
}

void jugar(int numParejas, int *apunTableroReal, int *apunTableroUsuario, int *apunTableroReal2, int *apunTableroUsuario2)
{
	int paresEncontrados=0;
	while(paresEncontrados != numParejas)
	{
		int cartaEscogida,cartaEscogida2;
		do
		{
			printf("\n\nIntroduzca el numero de la primera carta a voltear: ");
			scanf("%d",&cartaEscogida);
			apunTableroReal += (cartaEscogida-1);
			apunTableroUsuario += (cartaEscogida-1);
			if(*apunTableroUsuario != 0)
			{
				apunTableroReal -= (cartaEscogida-1);
				apunTableroUsuario -= (cartaEscogida-1);
				printf("\n\nEsta carta ya esta volteada!");
			}
		}while(*apunTableroUsuario != 0);
		do
		{
			printf("\n\nIntroduzca el numero de la segunda carta a voltear: ");
			scanf("%d",&cartaEscogida2);
			apunTableroReal2 += (cartaEscogida2-1);
			apunTableroUsuario2 += (cartaEscogida2-1);
			if(cartaEscogida2 == cartaEscogida || *apunTableroUsuario2 != 0)
			{
				apunTableroReal2 -= (cartaEscogida2-1);
				apunTableroUsuario2 -= (cartaEscogida2-1);
				printf("\n\nEsta carta ya esta volteada!");
			}
		}while(cartaEscogida2 == cartaEscogida || *apunTableroUsuario2 != 0);
		if(*apunTableroReal == *apunTableroReal2)
		{
			paresEncontrados++;
			*apunTableroUsuario = *apunTableroReal;
			*apunTableroUsuario2 = *apunTableroReal2;
			printf("\n\nHas encontrado una pareja!\n\n");
		}
		else
		{
			*apunTableroUsuario = *apunTableroReal;
			*apunTableroUsuario2 = *apunTableroReal2;
			apunTableroUsuario -= (cartaEscogida-1);
			imprimirTablero(apunTableroUsuario,numParejas);
			char ch;
			printf("\n\nPareja invalida! ");
			do
			{	
				printf("Presione enter para continuar\n\n");
				scanf("%c",&ch);
				ch = fgetc(stdin);
				if(ch == 0x0A)
				{
					system("cls");
					apunTableroUsuario += (cartaEscogida-1);
					*apunTableroUsuario = 0;
					*apunTableroUsuario2 = 0;
				}
			}while(ch != 0x0A);
		}
		apunTableroReal -= (cartaEscogida-1);
		apunTableroUsuario -= (cartaEscogida-1);
		apunTableroReal2 -= (cartaEscogida2-1);
		apunTableroUsuario2 -= (cartaEscogida2-1);
		imprimirTablero(apunTableroUsuario,numParejas);
	}
}

main()
{
	printf("============================JUEGO DE MEMORIA============================\n\n");
	char resp='r';
	do
	{
		int cartas = pedirDatos();
		int tablero[2][(cartas/2)];
		int tableroReal[2][(cartas/2)];
		int *apunTablero = tablero[0];
		int *apunTableroReal = tableroReal[0];
		llenarTablero(apunTablero,(cartas/2));
		llenarTableroReal(apunTableroReal,(cartas/2));
		imprimirTablero(apunTablero,(cartas/2));
		//imprimirTableroReal(apunTableroReal,(cartas/2));
		jugar((cartas/2),apunTableroReal,apunTablero,apunTableroReal,apunTablero);
		printf("\n\n=============Has encontrado todas las parejas! Has ganado el juego!=============\n\n");
		do
		{
			printf("\nPresione 's' para volver a jugar o 'n' para finalizar el juego: ");
			scanf("%c",&resp);
			resp = fgetc(stdin);
		}while(resp != 0x73 && resp != 0x53 && resp != 0x6e && resp != 0x4e);
	}while(resp == 0x73 || resp == 0x53);
}
