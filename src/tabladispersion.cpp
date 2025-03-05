#include "../include/tabladispersion.h"
#include <iostream>

//Redimensiona el vector 'tabla' para que tenga TABLE_SIZE buckets (listas vacías)
tabladispersion::tabladispersion() {
    tabla.resize(TABLE_SIZE);  
}
//Calcula el índice para la clave usando el operador módulo.
int tabladispersion::hashFuncion(int clave) const {
    return clave % TABLE_SIZE;  
}
/*
Primero calcula el índice correspondiente mediante hashFuncion. Luego,
recorre la lista en ese índice: si la clave ya existe, se actualiza el valor;
si no, se inserta el nuevo par al final de la lista.
*/
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
/*
Calcula el índice de la clave y recorre el bucket correspondiente. Si la clave se encuentra,
retorna el valor asociado; de lo contrario, retorna "No encontrado".
 */
std::string tabladispersion::buscar(int clave) const {
    int indice = hashFuncion(clave);
    for (const auto& par : tabla[indice]) {
        if (par.first == clave) {
            return par.second;  
        }
    }
    return "No encontrado";
}
//Elimina un par clave-valor
void tabladispersion::eliminar(int clave) {
    int indice = hashFuncion(clave);
    for (auto it = tabla[indice].begin(); it != tabla[indice].end(); ++it) {
        if (it->first == clave) {
            tabla[indice].erase(it);  
            return;
        }
    }
}
