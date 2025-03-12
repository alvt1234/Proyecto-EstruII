#include "archivobinario.h"

void ArchivoBinario::aggCliente(cliente c) {
    int id = c.getIdCliente();
    char nombre[50], telefono[15], correo[50], historial[100];
    double saldo = c.getSaldo();

    // Usamos strncpy para evitar desbordamiento de búfer y aseguramos que se
    // agregue el terminador nulo al final de las cadenas.
    strncpy(nombre, c.getNombre().c_str(), sizeof(nombre) - 1);
    nombre[sizeof(nombre) - 1] = '\0';  // Aseguramos el terminador nulo
    strncpy(telefono, c.getTelefono().c_str(), sizeof(telefono) - 1);
    telefono[sizeof(telefono) - 1] = '\0'; 
    strncpy(correo, c.getCorreo().c_str(), sizeof(correo) - 1);
    correo[sizeof(correo) - 1] = '\0'; 
    strncpy(historial, c.gethistorialCompras().c_str(), sizeof(historial) - 1);
    historial[sizeof(historial) - 1] = '\0'; 

    std::ofstream archivo("clientes.bin", std::ios::out | std::ios::binary | std::ios::app);

    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo de clientes para agregar datos.\n";
        return;
    }

    // Escribimos los datos en binario
    archivo.write(reinterpret_cast<char*>(&id), sizeof(int));
    archivo.write(reinterpret_cast<char*>(&saldo), sizeof(double));
    archivo.write(nombre, sizeof(nombre));
    archivo.write(telefono, sizeof(telefono));
    archivo.write(correo, sizeof(correo));
    archivo.write(historial, sizeof(historial));

    archivo.close();
    std::cout << "Cliente guardado correctamente.\n";
}

bool ArchivoBinario::verificarIDcliente(int id) {
    std::ifstream archivo("clientes.bin", std::ios::in | std::ios::binary);  
    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo de clientes para lectura.\n";
        return false;
    }

    int idcliente;
    char nombre[50], telefono[15], correo[50], historial[100];
    double saldo;

    // Leemos los clientes en un ciclo hasta llegar al final del archivo
    while (archivo.read(reinterpret_cast<char*>(&idcliente), sizeof(int))) {
        archivo.read(reinterpret_cast<char*>(&saldo), sizeof(double));
        archivo.read(nombre, sizeof(nombre));
        archivo.read(telefono, sizeof(telefono));
        archivo.read(correo, sizeof(correo));
        archivo.read(historial, sizeof(historial));

        // Verificamos si el id coincide
        if (id == idcliente) {
            std::cout << "ID EXISTENTE\n";
            archivo.close();
            return true;
        }
    }

    archivo.close();
    return false;
}void ArchivoBinario::cargarClientes(tabladispersion& clientes) {
    std::ifstream archivo("clientes.bin", std::ios::in | std::ios::binary);  
    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo de clientes para lectura.\n";
        return;
    }

    int idcliente;
    char nombre[50], telefono[50], correo[50], historial[100];
    double saldo;

    // Leemos los clientes en un ciclo hasta llegar al final del archivo
    while (archivo.read(reinterpret_cast<char*>(&idcliente), sizeof(int))) {
        archivo.read(reinterpret_cast<char*>(&saldo), sizeof(double));
        archivo.read(nombre, sizeof(nombre));
        archivo.read(telefono, sizeof(telefono));
        archivo.read(correo, sizeof(correo));
        archivo.read(historial, sizeof(historial));

        // Verifica si los datos fueron leídos correctamente
        std::cout << "Cliente cargado: Nombre: " << nombre << ", Correo: " << correo 
                  << ", Tel: " << telefono << ", Saldo: " << saldo 
                  << ", Historial: " << historial << std::endl;

        std::string info = "Nombre: " + std::string(nombre) + ", Correo: " + std::string(correo) +
                           ", Tel: " + std::string(telefono) + ", Saldo: " + std::to_string(saldo) +
                           ", Historial: " + std::string(historial);

        // Insertamos el cliente en la tabla de dispersión
        clientes.insertar(idcliente, info);
    }

    archivo.close();
}
