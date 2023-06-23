#include <iostream>
#include <set> // se utiliza la libreria set debido a un problema al mostrar los valores ordenados
#include <omp.h>

bool esPrimo(int num) { // funcion para verificar si un número es primo
    if (num <= 1) // si el número es menor o igual a 1 no es primo
        return false;
    
    if (num == 2 || num == 3) //si el número es 2 o 3 es primo 
        return true;
    
    if (num % 2 == 0 || num % 3 == 0) //ve si el número es divisible por 2 o divisible por 3
        return false;
    
    int divisor = 5;
    int incremento = 2;
    
    while (divisor * divisor <= num) { // mientras divisor sea menor o igual a num se mantiene el ciclo 
        if (num % divisor == 0)        // si el número es divisible por divisor no es primo
            return false;
        
        divisor = divisor + incremento;
        incremento = 6 - incremento;  // Alterna entre 2 y 4
    }
    
    return true;
}

void imprimirNumerosPrimos(int n) {
    std::set<int> primos; // se crea el conjunto set primos
    int hilos=omp_get_max_threads(); // se guarda en una variable la maxima cantidad de hilos que puede usarse
    #pragma omp parallel num_threads(hilos)  //crea una region paralela y se especifica la cantidad de hilos que va a usar
    {
    
        #pragma omp for //esto indica que el bucle for debe ejecutarse por multiples hilos en paralelo
        for (int i = 2; i <= n; i++) { // ciclo hasta el número 500000000 desde el número 2
            if (esPrimo(i)) { // si retorna true es primo
              #pragma omp critical  //esta seccion de codigo es ejecutada por un solo hilo a la vez
                primos.insert(i); // agrega los números al set "primos"
            }
        }
    }
    
    
    for (int imprimir : primos) { // ciclo para imprimir los números primos encontrados
        std::cout << imprimir << std::endl;
    }
    
    std::cout << "Cantidad de números primos: " << primos.size() << std::endl;
}

int main() {
	std::cout << "Cantidad de hilos: " <<  omp_get_max_threads()<< std::endl;
    imprimirNumerosPrimos(500000000);
    std::cout << std::endl << "=== Taller Recuperativo ===" << std::endl;
    std::cout << std::endl << "Mauricio Estrada";
    std::cout << std::endl << "Oscar Soto";
    std::cout << std::endl << "Rodrigo Vásquez" << std::endl;
    return 0;
}
