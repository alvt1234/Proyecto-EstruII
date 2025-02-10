#ifndef ARBOL_B_H
#define ARBOL_B_H

#include <vector>

class NodoB{
public:
    bool esHoja;
    std::vector<int> claves;
    std::vector<NodoB*> hijos;
    NodoB* siguiente;

    NodoB(bool hoja);
};

class arbolB{
private:
    NodoB* raiz;
    int grado;

public:

    arbolB(int _grado);
    void insertar(int clave);
    bool buscar(int clave) const;
    void eliminar(int clave);
    void recorrer() const;
};

#endif
