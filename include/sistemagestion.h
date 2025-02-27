#ifndef SISTEMAGESTION_H
#define SISTEMAGESTION_H

#include "arbolB.h"

class sistemagestion {
private:
    ArbolB empleados;
    ArbolB productos;

public:
    sistemagestion();
    void agregarEmpleado(int id);
    void buscarEmpleado(int id);
    void mostrarEmpleados();
    
    void agregarProducto(int id);
    void buscarProducto(int id);
    void mostrarProductos();
};

#endif
