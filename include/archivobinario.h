#include <fstream>
#include <iostream>
#include <cstring>
#include "cliente.h"
#include "tabladispersion.h"
#include "producto.h"
#include "pedido.h"
using namespace std;

class ArchivoBinario {
private:
    ofstream archivo;  

public:
    ArchivoBinario() {
        std::ofstream archivo("clientes.bin", std::ios::binary | std::ios::app);  
        std::ofstream archivoProducto("Productos.bin", std::ios::binary | std::ios::app);  
        std::ofstream archivoPedidos("pedidos.bin", std::ios::binary | std::ios::app);  
        if (!archivo || !archivoProducto || !archivoPedidos) {
            std::cerr << "Error al abrir el archivo clientes.bin" << std::endl;
        }
        archivo.close(); 
    }

    ~ArchivoBinario() {
        archivo.close(); 
    }
    void aggCliente(cliente c);
    bool verificarIDcliente(int id);
    void cargarClientes(tabladispersion& clientes);
    void aggproducto(producto p);
    bool verificarIDproducto(int id);
    void pedidos(pedido ped);
    bool verificarIDpedido(int id);
};
