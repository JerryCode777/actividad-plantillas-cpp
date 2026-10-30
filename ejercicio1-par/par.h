#ifndef PAR_H
#define PAR_H

#include <ostream>
#include <utility>

// Clase plantilla Par<T1, T2>: guarda dos valores que pueden ser de tipos distintos.
// El código se escribe una sola vez; el compilador genera una clase diferente por cada
// combinación de tipos que se use (Par<std::string, int>, Par<double, double>, ...).
// Las plantillas se definen completas en el .h porque el compilador necesita ver todo
// el código para poder generar cada versión.
template <typename T1, typename T2>
class Par {
public:
    // std::move evita copiar dos veces los valores grandes, como un std::string.
    Par(T1 primero, T2 segundo) : primero_(std::move(primero)), segundo_(std::move(segundo)) {}

    // Getters const: consultan el par sin modificarlo. Devuelven referencia constante
    // para no copiar el valor, sea del tipo que sea.
    const T1& getPrimero() const { return primero_; }
    const T2& getSegundo() const { return segundo_; }

    void setPrimero(T1 valor) { primero_ = std::move(valor); }
    void setSegundo(T2 valor) { segundo_ = std::move(valor); }

    // Devuelve un par nuevo con los valores invertidos: de Par<T1, T2> se obtiene Par<T2, T1>.
    Par<T2, T1> intercambiado() const { return Par<T2, T1>(segundo_, primero_); }

    // Dos pares son iguales si lo son sus dos componentes. Solo compila si T1 y T2
    // tienen operador ==: la plantilla impone ese requisito a los tipos que recibe.
    bool operator==(const Par& otro) const {
        return primero_ == otro.primero_ && segundo_ == otro.segundo_;
    }

    // Muestra el par con el formato (primero, segundo). Se define dentro de la clase para
    // que exista una función friend por cada Par<T1, T2> que se instancie. Como usa << sobre
    // sus componentes, también funciona con un Par dentro de otro Par.
    friend std::ostream& operator<<(std::ostream& os, const Par& par) {
        return os << '(' << par.primero_ << ", " << par.segundo_ << ')';
    }

private:
    T1 primero_;
    T2 segundo_;
};

#endif
