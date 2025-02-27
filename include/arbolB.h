#ifndef ARBOLB_H
#define ARBOLB_H

#include <iostream>
#include <vector>
#include <algorithm> 

class NodoB {
public:
    bool esHoja;  
    std::vector<int> claves;  
    std::vector<NodoB*> hijos;  

    NodoB(bool hoja);
};

class arbolB {
private:
    NodoB* raiz;  
    int grado;  

    void recorrer(NodoB* nodo) const;  //auxiliar para recorrer el árbol
    bool buscar(NodoB* nodo, int clave) const;  //auxiliar para buscar
    NodoB* insertarNodo(NodoB* nodo, int clave);  //auxiliar para insertar
    NodoB* eliminarNodo(NodoB* nodo, int clave);  //auxiliar para eliminar

public:
    arbolB(int _grado);
    
    void insertar(int clave);  //Insertar clave en el árbol
    bool buscar(int clave) const;  //Buscar clave en el árbol
    void recorrer() const;  //Recorrer el árbol en orden
    void eliminar(int clave);  //Eliminar clave del árbol
};

#endif
