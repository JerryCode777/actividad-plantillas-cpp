// Ejercicio 3: metaprogramación para calcular n^m en tiempo de compilación con constexpr.
#include <array>
#include <iostream>

#include "potencia.h"

// static_assert se evalúa al compilar: si alguna condición fuera falsa, el programa no
// compilaría. Es la prueba de que estos valores se calculan antes de ejecutar.
constexpr long long kDosALaDiez = potencia(2, 10);
static_assert(kDosALaDiez == 1024, "2^10 debe ser 1024");
static_assert(potencia(5, 0) == 1, "n^0 debe ser 1");
static_assert(Potencia<3, 4>::valor == 81, "3^4 debe ser 81");

int main() {
    std::cout << "===== EJERCICIO 3: POTENCIA n^m EN TIEMPO DE COMPILACIÓN =====\n\n";

    // Todos estos valores ya están calculados dentro del ejecutable.
    constexpr long long kDiezALaSeis = potencia(10, 6);
    constexpr long long kTresALaCinco = potencia(3, 5);
    std::cout << "Con la función constexpr potencia(n, m):\n"
              << "  potencia(2, 10) = " << kDosALaDiez << '\n'
              << "  potencia(10, 6) = " << kDiezALaSeis << '\n'
              << "  potencia(3, 5)  = " << kTresALaCinco << '\n'
              << "  potencia(5, 0)  = " << potencia(5, 0) << "\n\n";

    std::cout << "Con la plantilla Potencia<N, M>::valor:\n"
              << "  Potencia<3, 4>::valor  = " << Potencia<3, 4>::valor << '\n'
              << "  Potencia<2, 16>::valor = " << Potencia<2, 16>::valor << '\n'
              << "  Potencia<7, 3>::valor  = " << Potencia<7, 3>::valor << "\n\n";

    // Un valor constexpr se puede usar donde el lenguaje exige una constante,
    // por ejemplo como tamaño de un std::array.
    std::array<int, potencia(2, 3)> casillas{};
    std::cout << "std::array<int, potencia(2, 3)> tiene " << casillas.size() << " elementos\n\n";

    // La misma función constexpr también se puede usar con datos que solo se conocen
    // al ejecutar el programa; en ese caso se calcula en tiempo de ejecución.
    long long n;
    unsigned m;
    std::cout << "En tiempo de ejecución, ingrese la base n y el exponente m: ";
    if (std::cin >> n >> m) {
        std::cout << n << '^' << m << " = " << potencia(n, m) << '\n';
    } else {
        std::cout << "Debe ingresar dos números enteros (m no negativo).\n";
    }
    return 0;
}
