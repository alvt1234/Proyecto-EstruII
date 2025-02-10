#include "../include/tabladispersion.h"
#include <iostream>

tabladispersion::tabladispersion() {
    tabla.resize(TABLE_SIZE);  
}

int tabladispersion::hashFuncion(int clave) const {
    return clave % TABLE_SIZE;  
}

void tabladispersion::insertar(int clave, const std::string& valor) {
    int indice = hashFuncion(clave);
    for (auto& par : tabla[indice]) {
        if (par.first == clave) {
            par.second = valor; 
            return;
        }
    }
    tabla[indice].emplace_back(clave, valor);  
}

std::string tabladispersion::buscar(int clave) const {
    int indice = hashFuncion(clave);
    for (const auto& par : tabla[indice]) {
        if (par.first == clave) {
            return par.second;  
        }
    }
    return "No encontrado";
}

void tabladispersion::eliminar(int clave) {
    int indice = hashFuncion(clave);
    for (auto it = tabla[indice].begin(); it != tabla[indice].end(); ++it) {
        if (it->first == clave) {
            tabla[indice].erase(it);  
            return;
        }
    }
}
