// ParaleloArreglos.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//Alumno: Raul Alejandro Velasquez Ortiz
//Matrícula: 0A1794524
//Computo en la Nube
//Tarea 1. Programación de una solución paralela
#include "pch.h"
#include <iostream>
#include <omp.h>

// Definir constantes para el tamaño de los arreglos, el tamaño del bloque y la cantidad de elementos a mostrar
#define N 1000
#define chunk 100
#define mostrar 10

// Función para imprimir un rango específico de un arreglo
void imprimeArreglo(float *d, int inicio, int fin);

int main()
{
	// Mensaje inicial
	std::cout << "Sumando Arreglos en Paralelo!\n";

	// Declarar arreglos de entrada (a, b) y arreglo de salida (c)
	float a[N], b[N], c[N];
	int i;

	// Inicializar los arreglos a y b
	for (i = 0; i < N; i++)
	{
		a[i] = i * 10;
		b[i] = (i + 3) * 3.7;
	}

	// Imprimir los primeros "mostrar" valores de los arreglos a y b
	std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo a: " << std::endl;
	imprimeArreglo(a, 0, mostrar);

	std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo b: " << std::endl;
	imprimeArreglo(b, 0, mostrar);

	// Iniciar la región paralela con dos hilos, compartiendo los arreglos a, b, y c
#pragma omp parallel num_threads(2) shared(a, b, c)
	{
		// Obtener el identificador del hilo
		int tid = omp_get_thread_num();  // Obtener el identificador del hilo

		// Distribuir el trabajo entre los hilos de manera equitativa usando "schedule(static, chunk)"
#pragma omp for schedule(static, chunk)
		for (i = 0; i < N; i++)
		{
			c[i] = a[i] + b[i];
		}

		// Imprimir las sumas realizadas por hilo del arreglo c
#pragma omp critical
		{
			std::cout << "Suma realizada por el hilo " << tid << " de los " << mostrar << " valores del arreglo c: " << std::endl;
			// Imprimir el rango específico de elementos del arreglo c asignado al hilo
			if (tid == 0)
			{
				imprimeArreglo(c, tid * (mostrar / 2), (tid + 1) * (mostrar / 2) + mostrar % 2);
			}
			else
			{
				imprimeArreglo(c, tid * (mostrar / 2) + mostrar % 2, (tid + 1) * (mostrar / 2) + mostrar % 2);
			}
		}
	}
	// Finalizar la región paralela
	return 0;
}
// Definición de la función para imprimir un rango específico de un arreglo
void imprimeArreglo(float *d, int inicio, int fin)
{
	for (int x = inicio; x < fin; x++)
		std::cout << d[x] << " - ";
	std::cout << std::endl;
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln