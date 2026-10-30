#ifndef MINIMO_H
#define MINIMO_H

#include <cstring>

// Plantilla de función: el tipo T se deduce de los argumentos en cada llamada.
// Funciona con cualquier tipo que tenga el operador <; si no lo tiene, el error
// aparece al compilar, no al ejecutar.
template <typename T>
T minimo(T a, T b, T c) {
    T menor = a;
    if (b < menor) {
        menor = b;
    }
    if (c < menor) {
        menor = c;
    }
    return menor;
}

// Sobrecarga para cadenas de C. Sin ella, la plantilla compararía las direcciones de
// memoria de los punteros y no el texto. Ante una llamada con const char*, el compilador
// prefiere esta función normal a la plantilla.
inline const char* minimo(const char* a, const char* b, const char* c) {
    const char* menor = a;
    if (std::strcmp(b, menor) < 0) {
        menor = b;
    }
    if (std::strcmp(c, menor) < 0) {
        menor = c;
    }
    return menor;
}

#endif
