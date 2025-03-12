#include "../include/pedido.h"

pedido::pedido() {}

//¿Porque los productos solicitados es un vector?, es la cantidad?, o es espacificar cada producto?
pedido::pedido(int idPedido, int idCliente, std::vector<int> productosSolicitados, std::string fechaEntrega, std::string estado) {
    this->idPedido = idPedido;
    this->idCliente = idCliente;
    this->productosSolicitados = productosSolicitados;
    this->fechaEntrega = fechaEntrega;
    this->estado = estado;
}


int pedido::getIdPedido() {
    return idPedido;
}

int pedido::getIdCliente() {
    return idCliente;
}

std::vector<int> pedido::getProductosSolicitados() {
    return productosSolicitados;
}

std::string pedido::getFechaEntrega() {
    return fechaEntrega;
}

std::string pedido::getEstado() {
    return estado;
}

void pedido::setIdPedido(int idPedido) {
    this->idPedido = idPedido;
}

void pedido::setIdCliente(int idCliente) {
    this->idCliente = idCliente;
}

void pedido::setProductosSolicitados(std::vector<int> productosSolicitados) {
    this->productosSolicitados = productosSolicitados;
}

void pedido::setFechaEntrega(std::string fechaEntrega) {
    this->fechaEntrega = fechaEntrega;
}

void pedido::setEstado(std::string estado) {
    this->estado = estado;
}
