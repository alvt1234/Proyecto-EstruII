#include "../include/sistemagestion.h"
#include <iostream>

sistemagestion::sistemagestion() : empleados(3), productos(3) {}

void sistemagestion::agregarEmpleado(int id) {
    empleados.insertar(id);
    std::cout << "Empleado con ID " << id << " agregado." << std::endl;
}

void sistemagestion::buscarEmpleado(int id) {
    if (empleados.buscar(id))
        std::cout << "Empleado con ID " << id << " encontrado." << std::endl;
    else
        std::cout << "Empleado con ID " << id << " NO encontrado." << std::endl;
}

void sistemagestion::mostrarEmpleados() {
    std::cout << "Lista de empleados: ";
    empleados.recorrer();
}

void sistemagestion::agregarProducto(int id) {
    productos.insertar(id);
    std::cout << "Producto con ID " << id << " agregado." << std::endl;
}

void sistemagestion::buscarProducto(int id) {
    if (productos.buscar(id))
        std::cout << "Producto con ID " << id << " encontrado." << std::endl;
    else
        std::cout << "Producto con ID " << id << " NO encontrado." << std::endl;
}

void sistemagestion::mostrarProductos() {
    std::cout << "Lista de productos: ";
    productos.recorrer();
}
