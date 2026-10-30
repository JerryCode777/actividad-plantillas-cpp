// Ejercicio 4: patrón CRTP para crear clases derivadas con métodos personalizados.
#include <iomanip>
#include <iostream>

#include "figuras.h"

int main() {
    std::cout << "===== EJERCICIO 4: PATRÓN CRTP =====\n\n";
    std::cout << std::fixed << std::setprecision(2);

    Circulo circulo(3);
    Rectangulo rectangulo(4, 3);
    Rectangulo cuadrado(5, 5);
    Triangulo rectanguloPitagorico(3, 4, 5);
    Triangulo equilatero(6, 6, 6);

    // describir() está en la base Figura, pero usa los métodos de cada derivada.
    std::cout << "Métodos comunes heredados de Figura<Derivada>:\n";
    imprimirFigura(circulo);
    imprimirFigura(rectangulo);
    imprimirFigura(cuadrado);
    imprimirFigura(rectanguloPitagorico);
    imprimirFigura(equilatero);

    // Métodos personalizados: solo existen en su clase.
    std::cout << "\nMétodos personalizados de cada clase derivada:\n"
              << "  circulo.diametro()           = " << circulo.diametro() << '\n'
              << "  rectangulo.diagonal()        = " << rectangulo.diagonal() << '\n'
              << std::boolalpha
              << "  rectangulo.esCuadrado()      = " << rectangulo.esCuadrado() << '\n'
              << "  cuadrado.esCuadrado()        = " << cuadrado.esCuadrado() << '\n'
              << "  rectanguloPitagorico.tipo()  = " << rectanguloPitagorico.tipo() << '\n'
              << "  equilatero.tipo()            = " << equilatero.tipo() << "\n\n";

    // Contador<Derivada>: cada clase lleva la cuenta de sus propios objetos.
    std::cout << "Objetos creados por clase (Contador<Derivada>):\n"
              << "  Circulo: " << Circulo::creados() << " | Rectangulo: " << Rectangulo::creados()
              << " | Triangulo: " << Triangulo::creados() << "\n\n";

    // Sin funciones virtuales no hay puntero a tabla virtual: el objeto ocupa solo sus atributos.
    std::cout << "Tamaño en memoria (sin tabla virtual):\n"
              << "  sizeof(Circulo)    = " << sizeof(Circulo) << " bytes (1 double)\n"
              << "  sizeof(Rectangulo) = " << sizeof(Rectangulo) << " bytes (2 double)\n"
              << "  sizeof(Triangulo)  = " << sizeof(Triangulo) << " bytes (3 double)\n";
    return 0;
}
