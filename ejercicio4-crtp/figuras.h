#ifndef FIGURAS_H
#define FIGURAS_H

#include <cmath>
#include <iostream>
#include <string>

// CRTP (Curiously Recurring Template Pattern): la clase base recibe como parámetro de
// plantilla a su propia clase derivada, por ejemplo  class Circulo : public Figura<Circulo>.
// Así la base conoce el tipo exacto de la derivada y puede llamar a sus métodos con
// static_cast, sin funciones virtuales: la llamada se resuelve al compilar
// (polimorfismo estático).
template <typename Derivada>
class Figura {
public:
    // Métodos comunes: delegan en los métodos personalizados de cada derivada.
    double area() const { return derivada().calcularArea(); }
    double perimetro() const { return derivada().calcularPerimetro(); }

    // Algoritmo común para todas las figuras, que usa el nombre que define cada derivada.
    void describir() const {
        std::cout << derivada().nombre() << " | área: " << area() << " | perímetro: " << perimetro() << '\n';
    }

private:
    // Convierte *this en la clase derivada. Es seguro porque, por el patrón,
    // Derivada siempre hereda de Figura<Derivada>.
    const Derivada& derivada() const { return static_cast<const Derivada&>(*this); }
};

// Segundo uso del CRTP: un contador de objetos. Cada derivada tiene su propio contador,
// porque Contador<Circulo> y Contador<Rectangulo> son clases distintas.
template <typename Derivada>
class Contador {
public:
    Contador() { ++creados_; }
    Contador(const Contador&) { ++creados_; }
    static int creados() { return creados_; }

private:
    inline static int creados_ = 0;  // inline static (C++17): se define aquí mismo
};

constexpr double kPi = 3.14159265358979;

class Circulo : public Figura<Circulo>, public Contador<Circulo> {
public:
    explicit Circulo(double radio) : radio_(radio) {}

    // Métodos que Figura<Circulo> necesita.
    std::string nombre() const { return "Círculo"; }
    double calcularArea() const { return kPi * radio_ * radio_; }
    double calcularPerimetro() const { return 2 * kPi * radio_; }

    // Método personalizado, propio de esta clase.
    double diametro() const { return 2 * radio_; }

private:
    double radio_;
};

class Rectangulo : public Figura<Rectangulo>, public Contador<Rectangulo> {
public:
    Rectangulo(double base, double altura) : base_(base), altura_(altura) {}

    std::string nombre() const { return esCuadrado() ? "Cuadrado" : "Rectángulo"; }
    double calcularArea() const { return base_ * altura_; }
    double calcularPerimetro() const { return 2 * (base_ + altura_); }

    // Métodos personalizados.
    bool esCuadrado() const { return base_ == altura_; }
    double diagonal() const { return std::sqrt(base_ * base_ + altura_ * altura_); }

private:
    double base_;
    double altura_;
};

class Triangulo : public Figura<Triangulo>, public Contador<Triangulo> {
public:
    Triangulo(double a, double b, double c) : a_(a), b_(b), c_(c) {}

    std::string nombre() const { return "Triángulo " + tipo(); }

    // Fórmula de Herón: área a partir de los tres lados.
    double calcularArea() const {
        double s = calcularPerimetro() / 2;
        return std::sqrt(s * (s - a_) * (s - b_) * (s - c_));
    }
    double calcularPerimetro() const { return a_ + b_ + c_; }

    // Método personalizado: clasifica el triángulo según sus lados.
    std::string tipo() const {
        if (a_ == b_ && b_ == c_) {
            return "equilátero";
        }
        if (a_ == b_ || b_ == c_ || a_ == c_) {
            return "isósceles";
        }
        return "escaleno";
    }

private:
    double a_;
    double b_;
    double c_;
};

// Función genérica que acepta cualquier Figura<D>. El compilador genera una versión
// por cada tipo de figura, y la llamada a describir() no pasa por una tabla virtual.
template <typename D>
void imprimirFigura(const Figura<D>& figura) {
    std::cout << "  ";
    figura.describir();
}

#endif
