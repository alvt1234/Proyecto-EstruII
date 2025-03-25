#include <fstream>
#include <iostream>
#include <cstring>
#include "cliente.h"
#include "tabladispersion.h"
#include "producto.h"
#include "pedido.h"
#include "empleado.h"
#include "venta.h"
#include "arbolB.h"
#include "huffman.h"
#include <iomanip>
using namespace std;

class ArchivoBinario {
private:
    ofstream archivo;  

public:
    HuffmanCompression huffman;
    
    // Metodos para comprimir descomprimir 
    std::string comprimirDatos(const std::string& datos);
    std::string descomprimirDatos(const std::string& datosComprimidos);
    
    ArchivoBinario() {
        std::ofstream archivo("clientes.bin", std::ios::binary | std::ios::app);  
        std::ofstream archivoProducto("Productos.bin", std::ios::binary | std::ios::app);  
        std::ofstream archivoPedidos("pedidos.bin", std::ios::binary | std::ios::app);  
        std::ofstream archivoEmpleados("empleados.bin", std::ios::binary | std::ios::app); 
        std::ofstream archivoventas("ventas.bin", std::ios::binary | std::ios::app); 
        if (!archivo || !archivoProducto || !archivoPedidos || !archivoEmpleados || !archivoventas) {
            std::cerr << "Error al abrir el archivo clientes.bin" << std::endl;
        }
        archivo.close(); 
    }

    ~ArchivoBinario() {
        archivo.close(); 
    }
    void mostrarEmpleados();
    void mostrarProductos();
    void aggCliente(cliente c);
    bool verificarIDcliente(int id);
    void cargarClientes(tabladispersion& clientes);
    void aggproducto(producto p);
    bool verificarIDproducto(int id);
    void pedidos(pedido ped);
    bool verificarIDpedido(int id);
    void buscarpedido(tabladispersion& clientes);
    void aggEmpleado(empleado e);
    bool verificarIDempleado(int id);
    void ventas(venta v);
    bool verificarIDventas(int id);
    void buscarEmpleado(arbolB& empleado);
   void reportesClientes();
   void reportesEmpleados();
   void reportesProductos();
   void reportesPedidos();
    void reportesVentas();
};
