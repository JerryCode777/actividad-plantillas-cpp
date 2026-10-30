// Ejercicio 1: clase genérica Par<T1, T2>.
#include <iostream>
#include <string>
#include <vector>

#include "par.h"

int main() {
    std::cout << "===== EJERCICIO 1: CLASE GENÉRICA Par<T1, T2> =====\n\n";
    std::cout << std::boolalpha;  // muestra true/false en lugar de 1/0

    // El mismo código de Par sirve para cualquier combinación de tipos.
    Par<std::string, int> alumno("Ana Torres", 19);
    Par<double, double> coordenada(-16.39, -71.53);
    Par<char, bool> respuesta('A', true);
    Par<std::string, Par<int, int>> fecha("Inicio de clases", Par<int, int>(3, 2026));  // un Par dentro de otro

    std::cout << "Par<string, int>           alumno     = " << alumno << '\n'
              << "Par<double, double>        coordenada = " << coordenada << '\n'
              << "Par<char, bool>            respuesta  = " << respuesta << '\n'
              << "Par<string, Par<int, int>> fecha      = " << fecha << "\n\n";

    // Acceso y modificación de los valores.
    std::cout << "alumno.getPrimero() = " << alumno.getPrimero() << '\n'
              << "alumno.getSegundo() = " << alumno.getSegundo() << '\n';
    alumno.setSegundo(20);
    std::cout << "Después de setSegundo(20): " << alumno << '\n'
              << "alumno.intercambiado()   : " << alumno.intercambiado() << "  -> Par<int, string>\n\n";

    // Desde C++17 el compilador deduce T1 y T2 a partir de los argumentos (CTAD).
    Par deducido(3.5, std::string("metros"));
    std::cout << "Par deducido(3.5, \"metros\") = " << deducido << "  -> Par<double, string>\n"
              << "coordenada == (-16.39, -71.53): " << (coordenada == Par<double, double>(-16.39, -71.53))
              << "\n\n";

    // Un vector de pares: cursos con su número de créditos.
    std::vector<Par<std::string, int>> cursos = {
        {"Tecnología de Objetos", 4},
        {"Fundamentos de Sistemas de Información", 3},
        {"Estructuras de Datos", 4},
    };
    int totalCreditos = 0;
    std::cout << "Cursos y créditos:\n";
    for (const auto& curso : cursos) {
        std::cout << "  " << curso << '\n';
        totalCreditos += curso.getSegundo();
    }
    std::cout << "Total de créditos: " << totalCreditos << '\n';
    return 0;
}
