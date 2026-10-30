// Ejercicio 2: función genérica minimo() con tres parámetros.
#include <iostream>
#include <string>

#include "minimo.h"

// Tipo propio: para usarlo con minimo() basta con definir el operador <.
struct Alumno {
    std::string nombre;
    double nota;
};

// Un alumno es "menor" que otro si tiene menor nota.
bool operator<(const Alumno& a, const Alumno& b) { return a.nota < b.nota; }

int main() {
    std::cout << "===== EJERCICIO 2: FUNCIÓN GENÉRICA minimo() =====\n\n";

    // En cada llamada el compilador deduce T y genera la versión correspondiente.
    std::cout << "minimo(8, 3, 5)                      = " << minimo(8, 3, 5) << "   (T = int)\n"
              << "minimo(2.75, 1.5, 9.0)               = " << minimo(2.75, 1.5, 9.0) << "   (T = double)\n"
              << "minimo('m', 'c', 'x')                = " << minimo('m', 'c', 'x') << "   (T = char)\n";

    std::string a = "tecnología", b = "objetos", c = "plantillas";
    std::cout << "minimo(string \"tecnología\", ...)     = " << minimo(a, b, c) << "   (T = std::string)\n";

    // Usa la sobrecarga para const char*: compara el texto, no las direcciones.
    std::cout << "minimo(\"pera\", \"manzana\", \"uva\")     = " << minimo("pera", "manzana", "uva")
              << "   (sobrecarga const char*)\n";

    // Con tipos mezclados no se puede deducir un único T: se indica explícitamente.
    std::cout << "minimo<double>(3, 2.5, 4)            = " << minimo<double>(3, 2.5, 4)
              << "   (T indicado explícitamente)\n\n";

    // Con un tipo propio que define el operador <.
    Alumno menor = minimo(Alumno{"Ana", 16.5}, Alumno{"Luis", 14.0}, Alumno{"Carla", 18.0});
    std::cout << "Alumno con menor nota: " << menor.nombre << " (" << menor.nota << ")   (T = Alumno)\n\n";

    // Con datos ingresados por el usuario.
    int x, y, z;
    std::cout << "Ingrese tres números enteros: ";
    if (std::cin >> x >> y >> z) {
        std::cout << "El menor es: " << minimo(x, y, z) << '\n';
    } else {
        std::cout << "Debe ingresar tres números enteros.\n";
    }
    return 0;
}
