#include "../include/arbolB.h"
#include <algorithm> 

NodoB::NodoB(bool hoja) {
    esHoja = hoja;
}

arbolB::arbolB(int _grado) {
    grado = _grado;
    raiz = new NodoB(true);
}

// Recorrer el árbol en orden
void arbolB::recorrer(NodoB* nodo) const {
    if (nodo == nullptr) return;
    for (size_t i = 0; i < nodo->claves.size(); i++) {
        if (!nodo->esHoja) recorrer(nodo->hijos[i]);
        std::cout << nodo->claves[i] << " ";
    }
    if (!nodo->esHoja) recorrer(nodo->hijos[nodo->claves.size()]);
}

// Llamado público de recorrer
void arbolB::recorrer() const {
    recorrer(raiz);
    std::cout << std::endl;
}

// Buscar una clave en el árbol
bool arbolB::buscar(NodoB* nodo, int clave) const {
    if (nodo == nullptr) return false;
    for (int c : nodo->claves) {
        if (c == clave) return true;
    }
    if (nodo->esHoja) return false;
    return buscar(nodo->hijos[0], clave);
}

// Llamado público de buscar
bool arbolB::buscar(int clave) const {
    return buscar(raiz, clave);
}

// Insertar una clave en el árbol
NodoB* arbolB::insertarNodo(NodoB* nodo, int clave) {
    nodo->claves.push_back(clave);
    std::sort(nodo->claves.begin(), nodo->claves.end());
    return nodo;
}

// Llamado público de insertar
void arbolB::insertar(int clave) {
    raiz = insertarNodo(raiz, clave);
}

// Eliminar una clave del árbol
NodoB* arbolB::eliminarNodo(NodoB* nodo, int clave) {
    for (auto it = nodo->claves.begin(); it != nodo->claves.end(); ++it) {
        if (*it == clave) {
            nodo->claves.erase(it);  // Elimina la clave del nodo
            return nodo;
        }
    }
    if (!nodo->hijos.empty()) nodo->hijos[0] = eliminarNodo(nodo->hijos[0], clave);
    return nodo;
}

// Llamado público de eliminar
void arbolB::eliminar(int clave) {
    raiz = eliminarNodo(raiz, clave);
    std::cout << "Clave " << clave << " eliminada del árbol B.\n";
}