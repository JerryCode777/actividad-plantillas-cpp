#ifndef POTENCIA_H
#define POTENCIA_H

// Función constexpr: si n y m se conocen al compilar, el compilador calcula el resultado
// y lo escribe directamente en el programa; si no, se ejecuta como una función normal.
// Usa la definición recursiva n^m = n * n^(m-1), con n^0 = 1.
constexpr long long potencia(long long n, unsigned m) {
    return m == 0 ? 1 : n * potencia(n, m - 1);
}

// Metaprogramación con plantillas: la "recursión" ocurre entre instanciaciones de la
// plantilla. Para calcular Potencia<2, 3> el compilador necesita Potencia<2, 2>, luego
// Potencia<2, 1> y así hasta Potencia<2, 0>.
template <long long N, unsigned M>
struct Potencia {
    static constexpr long long valor = N * Potencia<N, M - 1>::valor;
};

// Especialización para M = 0: es el caso base que detiene la recursión.
template <long long N>
struct Potencia<N, 0> {
    static constexpr long long valor = 1;
};

#endif
