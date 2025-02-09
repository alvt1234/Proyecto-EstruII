#include "../include/arbolB.h"
#include <iostream>
#include <algorithm>

NodoB::NodoB(bool hoja){
     esHoja=hoja;
    siguiente=nullptr;
}

arbolB::arbolB(int _grado){
    grado= _grado;
    raiz=new NodoB(true);
}

void arbolB::insertar(int clave){
    if(raiz->claves.size()< grado-1){
        raiz->claves.push_back(clave);
        std::sort(raiz->claves.begin(),raiz->claves.end());
    }else{
        //division de nodos
    
    }
}

bool arbolB::buscar(int clave)const{
    NodoB* actual=raiz;
    while(actual !=nullptr){
        for(int c : actual->claves){
             if(c==clave) return true;
        }
        actual=actual->hijos.empty() ? nullptr : actual->hijos[0];
    }
    return false;
}

void arbolB::recorrer() const{
    NodoB* actual=raiz;
    while(actual!=nullptr){
        for(int c : actual->claves){
            std::cout <<c<<"";
        }
        std::cout <<"| ";
        actual=actual->siguiente;
    }
    std::cout <<std::endl;
    
}