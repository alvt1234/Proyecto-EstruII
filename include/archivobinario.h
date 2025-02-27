#include <fstream>
#include <iostream>
#include "cliente.h"
using namespace std;

class ArchivoBinario {
private:
    ofstream archivo;  

public:
    ArchivoBinario() {
        archivo.open("clientes.bin", ios::binary);
        if (!archivo) {
            cerr << "Error al abrir el archivo clientes.bin" << endl;
        }
    }

    ~ArchivoBinario() {
        archivo.close(); 
    }
    void aggCliente(cliente c);
};
