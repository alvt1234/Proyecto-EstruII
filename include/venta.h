#ifndef VENTA_H
#define VENTA_H
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class venta {
private:
    int idVenta;
    int idCliente;
    std::vector<int> productosVendidos;
    std::vector<int> cantidades;
    double total;
    std::string fecha;
   

public:
    venta();
    venta(int idVenta, int idCliente, std::vector<int> productosVendidos, std::vector<int> cantidades, double total, std::string fecha);
    int getIdVenta();
    int getIdCliente();
    std::vector<int> getProductosVendidos();
    std::vector<int> getCantidades();
    double getTotal();
    string getFecha();
    void setIdVenta(int idVenta);
    void setIdCliente(int idCliente);
    void setProductosVendidos(std::vector<int> productosVendidos);
    void setCantidades(std::vector<int> cantidades);
    void setTotal(double total);
    void setFecha(std::string fecha);
    void setPrecios(std::vector<double> precios);   // Agregado
    void setSubtotales(std::vector<double> subtotales); // Agregado
};

#endif // VENTA_H

