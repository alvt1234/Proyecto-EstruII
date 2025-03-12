#ifndef PEDIDO_H
#define PEDIDO_H
#include <vector>
#include <string>
using namespace std; 

class pedido {
private:
    int idPedido;
    int idCliente;
    vector<int> productosSolicitados;
    string fechaEntrega;
    string estado; 

public:
    pedido();
    pedido(int idPedido, int idCliente, std::vector<int> productosSolicitados, std::string fechaEntrega, std::string estado);

    // Getters
    int getIdPedido();
    int getIdCliente();
    vector<int> getProductosSolicitados();
    string getFechaEntrega();
    string getEstado();
    // Setters
    void setIdPedido(int idPedido);
    void setIdCliente(int idCliente);
    void setProductosSolicitados(std::vector<int> productosSolicitados);
    void setFechaEntrega(std::string fechaEntrega);
    void setEstado(std::string estado);
};
#endif


