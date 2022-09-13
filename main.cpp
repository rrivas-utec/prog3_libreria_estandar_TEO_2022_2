#include <iostream>
#include <vector>
#include <list>
using namespace std;
// 1. PARÁMETROS TIPO
template <class Type>
Type sumar(Type a, Type b) {
    return a + b;
}

// 2. PARÁMETROS NO TIPO
int restar(int a, int b) {      // Parámetros de una función
    return a - b;               // Se obtienen en tipo de ejecución
}

template <int a, int b>         // Parámetros de template NO-Tipo
int restar () {                 // Se obtienen en tipo de compilación
    return a - b;
}

template <typename T, int N>
int array_size(T (&)[N]) {      // int arr1 [4]  // int sumar (int, int)
    return N;
}

template <typename T, int sz_A, int sz_B>
auto&& unir_arreglos(T (&a)[sz_A], T(&b)[sz_B]) {   // auto&& es una auto RValue referencia que permite detectar
                                                    // con mayor precision el tipo de datos hasta RValue referencias
    static T result [sz_A + sz_B] = {};
    auto j = 0;
    for (auto i = 0; i < sz_A; ++i)
        result[j++] = a[i];
    for (auto i = 0; i < sz_B; ++i)
        result[j++] = b[i];
    return result;
}
void swap(int& a, int& b) {    // Referencia L-Value
    int t = a;
    a = b;
    b = t;
}

// Asignación LValue = RValue
int sumar_2 (const int& a, const int& b) {    // Referencia Constante (L-Value, R-Value)
    return a + b;
}

int multiplicar(int&& a, int&& b) { // Referencia R-Value
    a *= 10;
    b *= 10;
    return a * b;
}

// 3. PARÁMETROS TEMPLATE
//template<typename T, template <class...> class ContainerType>
/*
 1. Solo se deducen si los tipos se encuentra en la lista de parámetros
 2. Se colocan los deducibles a la derecha
 3. Como ayuda a los NO deducible se le puede colocar un valor por defecto
*/
template<
        template <typename...> class ContainerType=vector,  // ContainerType
        typename T                                          // T
        >
ContainerType<T> generar_contenedor(int sz, T value) {
    ContainerType<T> result(sz);
    for (auto& item: result) item = value;
    return result;

}

template<typename T, template <typename...> typename ContainerType=vector>
void imprimir_contenedor(ContainerType<T> vec) {
    for (const auto& item : vec)
        cout << item << " ";
    cout << endl;
}


int main() {
    int arr1 [4] = {1, 2, 3, 4};
    int arr2 [6] = {5, 6, 7, 8, 9, 10};

    // arreglo estático
    auto&& arr3 = unir_arreglos(arr1, arr2);
    cout << "Size: " << array_size(arr3) << endl;

    cout << sizeof(arr1)/sizeof(int) << endl;
    cout << sizeof(arr2)/sizeof(int) << endl;
    cout << array_size(arr1) << endl;
    cout << array_size(arr2) << endl;

    int x = 10;
    int y = 20;
    int z = 10 + 20; // El 10 + 20 se convierte LValue

    cout << sumar_2(x, y) << endl;  // RValue
    cout << sumar_2(10, 40) << endl; // RValue
    cout << 10 + 20 << endl;         // Se mantiene como RValue
    int w = sumar_2(10, 20);
    w += 12;
    cout << multiplicar(1 + 2, sumar_2(1, 4)) << endl;

    auto cnt1 = generar_contenedor(5, 11);
    auto cnt2 = generar_contenedor(5, 'A');
    auto cnt3 = generar_contenedor<list>(5, 11);
    imprimir_contenedor(cnt1);
    imprimir_contenedor(cnt2);
    imprimir_contenedor(cnt3);

    return 0;
}
