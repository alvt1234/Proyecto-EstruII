#ifndef ARBOL_B_H
#define ARBOL_B_H

#include <vector>

class BNode {
public:
    bool esHoja;
    std::vector<int> claves;
    std::vector<BNode*> hijos;
    BNode *siguiente;

    BNode(bool hoja);
};

class arbolB {
private:
    BNode *raiz;
    int grado;
public:
    arbolB(int grado);

    void insertar(int clave);
    bool buscar(int clave) const;
    void eliminar(int clave);
    void recorrer() const;
};

#endif
