#include "../include/venta.h" 

venta::venta() {}

venta::venta(int idVenta, int idCliente, std::vector<int> productosVendidos, std::vector<int> cantidades, double total, std::string fecha) {
    this->idVenta = idVenta;
    this->idCliente = idCliente;
    this->productosVendidos = productosVendidos;
    this->cantidades = cantidades;
    this->total = total;
    this->fecha = fecha;
}


int venta::getIdVenta() {
    return idVenta;
}

int venta::getIdCliente() {
    return idCliente;
}

std::vector<int> venta::getProductosVendidos() {
    return productosVendidos;
}

std::vector<int> venta::getCantidades() {
    return cantidades;
}

double venta::getTotal() {
    return total;
}

std::string venta::getFecha() {
    return fecha;
}

void venta::setIdVenta(int idVenta) {
    this->idVenta = idVenta;
}

void venta::setIdCliente(int idCliente) {
    this->idCliente = idCliente;
}

void venta::setProductosVendidos(std::vector<int> productosVendidos) {
    this->productosVendidos = productosVendidos;
}

void venta::setCantidades(std::vector<int> cantidades) {
    this->cantidades = cantidades;
}

void venta::setTotal(double total) {
    this->total = total;
}

void venta::setFecha(std::string fecha) {
    this->fecha = fecha;
}

