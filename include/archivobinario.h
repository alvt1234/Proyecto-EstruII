#include <fstream>
#include <iostream>
#include <cstring>
#include "cliente.h"
#include "tabladispersion.h"
using namespace std;

class ArchivoBinario {
private:
    ofstream archivo;  

public:
    ArchivoBinario() {
        std::ofstream archivo("clientes.bin", std::ios::binary | std::ios::app);  
        if (!archivo) {
            std::cerr << "Error al abrir el archivo clientes.bin" << std::endl;
        }
        // El archivo se abre en modo "append" para no sobrescribir los datos existentes
        archivo.close(); 
    }

    ~ArchivoBinario() {
        archivo.close(); 
    }
    void aggCliente(cliente c);
    bool verificarIDcliente(int id);
    void cargarClientes(tabladispersion& clientes);
};
