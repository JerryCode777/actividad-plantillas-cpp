# Actividad · Plantillas, metaprogramación y patrón CRTP en C++

> **Grupo 1** · Universidad Nacional de San Agustín de Arequipa · Escuela Profesional de Ingeniería de Sistemas · 2026

| | |
|---|---|
| **Curso** | Tecnología de Objetos |
| **Docente** | Mg. Maribel Molina Barriga |
| **Lenguaje** | C++17 |
| **Entregables** | 4 ejercicios propuestos · Informe APA |

---

## Contenido
1. [Ejercicios](#ejercicios)
2. [Estructura del repositorio](#estructura-del-repositorio)
3. [Compilar y ejecutar](#compilar-y-ejecutar)
4. [Explicación de cada ejercicio](#explicación-de-cada-ejercicio)
5. [Resumen de conceptos](#resumen-de-conceptos)
6. [Distribución del trabajo](#distribución-del-trabajo)
7. [Integrantes](#integrantes)

---

## Ejercicios

| N.º | Enunciado | Solución |
|-----|-----------|----------|
| 1 | Implementar una clase genérica `Par<T1, T2>` (clase plantilla) que almacene dos valores de distinto tipo sin repetir código | [`ejercicio1-par/`](ejercicio1-par/) |
| 2 | Diseñar una función `minimo()` genérica con tres parámetros que retorne el menor de ellos | [`ejercicio2-minimo/`](ejercicio2-minimo/) |
| 3 | Realizar un ejemplo de metaprogramación para calcular la potencia n^m en tiempo de compilación usando `constexpr` | [`ejercicio3-potencia-constexpr/`](ejercicio3-potencia-constexpr/) |
| 4 | Implementar el patrón **CRTP** para crear clases derivadas con métodos personalizados | [`ejercicio4-crtp/`](ejercicio4-crtp/) |

## Estructura del repositorio

```
actividad-plantillas-cpp/
├── ejercicio1-par/
│   ├── par.h                     Clase plantilla Par<T1, T2>
│   └── main.cpp                  Pruebas con distintos tipos
├── ejercicio2-minimo/
│   ├── minimo.h                  Plantilla minimo(a, b, c) + sobrecarga const char*
│   └── main.cpp                  Pruebas con int, double, char, string y un tipo propio
├── ejercicio3-potencia-constexpr/
│   ├── potencia.h                potencia() constexpr y plantilla Potencia<N, M>
│   └── main.cpp                  static_assert y cálculo en compilación y ejecución
├── ejercicio4-crtp/
│   ├── figuras.h                 Figura<Derivada>, Contador<Derivada> y figuras
│   └── main.cpp                  Métodos comunes y personalizados
├── informe/                      Informe en formato APA (.docx)
└── Makefile
```

## Compilar y ejecutar

Requisito: compilador con C++17 (`g++` de MinGW en Windows, `clang++` en macOS o `g++` en Linux).

**Con make**
```bash
make                    # compila los 4 ejercicios en bin/
make run-ejercicio1     # Par<T1, T2>
make run-ejercicio2     # minimo()
make run-ejercicio3     # potencia constexpr
make run-ejercicio4     # CRTP
```

**Sin make**
```bash
g++ -std=c++17 -Wall ejercicio1-par/main.cpp -o ejercicio1_par
g++ -std=c++17 -Wall ejercicio2-minimo/main.cpp -o ejercicio2_minimo
g++ -std=c++17 -Wall ejercicio3-potencia-constexpr/main.cpp -o ejercicio3_potencia
g++ -std=c++17 -Wall ejercicio4-crtp/main.cpp -o ejercicio4_crtp
```

> En Windows, si las tildes se ven mal en la consola, ejecuten `chcp 65001` antes del programa.

## Explicación de cada ejercicio

### 1. Clase genérica `Par<T1, T2>`
```cpp
template <typename T1, typename T2>
class Par {
public:
    Par(T1 primero, T2 segundo);
    const T1& getPrimero() const;
    const T2& getSegundo() const;
    Par<T2, T1> intercambiado() const;   // (a, b) -> (b, a)
    friend std::ostream& operator<<(std::ostream& os, const Par& par);
private:
    T1 primero_;
    T2 segundo_;
};
```
Una sola definición sirve para `Par<std::string, int>`, `Par<double, double>`, `Par<char, bool>` e incluso `Par<std::string, Par<int, int>>`: el compilador genera una clase distinta por cada combinación de tipos. Desde C++17 los tipos también se pueden deducir: `Par p(3.5, std::string("metros"));`.

### 2. Función genérica `minimo()`
```cpp
template <typename T>
T minimo(T a, T b, T c);                                         // cualquier T con operador <
const char* minimo(const char* a, const char* b, const char* c); // compara texto, no punteros
```
El tipo `T` se deduce en cada llamada (`int`, `double`, `char`, `std::string` o un `struct Alumno` con `operator<`). La sobrecarga para `const char*` evita que se comparen direcciones de memoria. Con tipos mezclados se indica el tipo: `minimo<double>(3, 2.5, 4)`.

### 3. Potencia n^m en tiempo de compilación
```cpp
constexpr long long potencia(long long n, unsigned m) {
    return m == 0 ? 1 : n * potencia(n, m - 1);
}

template <long long N, unsigned M>
struct Potencia { static constexpr long long valor = N * Potencia<N, M - 1>::valor; };
template <long long N>
struct Potencia<N, 0> { static constexpr long long valor = 1; };   // caso base

static_assert(potencia(2, 10) == 1024);   // se verifica al compilar
```
Se muestran dos técnicas: la función `constexpr` (que también se puede usar en tiempo de ejecución) y la metaprogramación clásica con plantillas recursivas y una especialización como caso base. `static_assert` y `std::array<int, potencia(2, 3)>` prueban que el valor se conoce al compilar.

### 4. Patrón CRTP
```cpp
template <typename Derivada>
class Figura {
public:
    double area() const { return static_cast<const Derivada&>(*this).calcularArea(); }
    void describir() const;            // algoritmo común
};

class Circulo : public Figura<Circulo> {
public:
    double calcularArea() const;       // lo que pide la base
    double diametro() const;           // método personalizado
};
```
La base recibe a su propia derivada como parámetro de plantilla, así que llama a sus métodos con `static_cast` y sin funciones virtuales (**polimorfismo estático**). Las derivadas `Circulo`, `Rectangulo` y `Triangulo` implementan `calcularArea()`, `calcularPerimetro()` y `nombre()`, y agregan sus métodos propios: `diametro()`, `esCuadrado()`, `diagonal()` y `tipo()`. Un segundo uso del patrón, `Contador<Derivada>`, lleva la cuenta de los objetos de cada clase por separado.

## Resumen de conceptos

| Concepto | Sintaxis | Para qué sirve | Ejercicio |
|----------|----------|----------------|-----------|
| Plantilla de clase | `template <typename T1, typename T2> class Par` | Una clase para muchos tipos | 1 |
| Deducción de argumentos (CTAD) | `Par p(3.5, std::string("m"));` | Omitir los tipos al crear el objeto | 1 |
| Plantilla de función | `template <typename T> T minimo(T, T, T)` | Una función para muchos tipos | 2 |
| Sobrecarga sobre plantilla | `const char* minimo(const char*, ...)` | Comportamiento especial para un tipo | 2 |
| `constexpr` | `constexpr long long potencia(...)` | Calcular en tiempo de compilación | 3 |
| Especialización de plantilla | `struct Potencia<N, 0>` | Caso base de la metaprogramación | 3 |
| `static_assert` | `static_assert(potencia(2, 10) == 1024);` | Verificar al compilar | 3 |
| CRTP | `class Circulo : public Figura<Circulo>` | Polimorfismo estático sin `virtual` | 4 |

## Distribución del trabajo

| Integrante | Responsabilidad |
|------------|-----------------|
| Quispe Mamani Jose Gabriel | Ejercicio 1: clase genérica `Par<T1, T2>` |
| Solsol Choque Fernando Rafael | Ejercicio 2: función genérica `minimo()` |
| Schreiber Landeo Diego Hans | Ejercicio 3: potencia con `constexpr` |
| Ramos Ochochoque Elkin Eder B. | Ejercicio 4: patrón CRTP |
| Huaynacho Mango Jerry Anderson | Integración, documentación e informe |

## Integrantes
| Apellidos y nombres | Usuario GitHub |
|---------------------|----------------|
| Huaynacho Mango Jerry Anderson | JerryCode777 |
| Quispe Mamani Jose Gabriel | J-Gabriel-Quispe-M |
| Ramos Ochochoque Elkin Eder B. | elkinramos8 |
| Schreiber Landeo Diego Hans | Diego-Schreiber |
| Solsol Choque Fernando Rafael | Fernando-Solsol |
