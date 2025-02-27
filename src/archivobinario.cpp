#include "archivobinario.h"
#include <cstring>
void ArchivoBinario::aggCliente(cliente c)
{
    int id = c.getIdCliente();
    char nombre[50], telefono[15], correo[50], historial[100];
    double saldo = c.getSaldo();

    strncpy(nombre, c.getNombre().c_str(), sizeof(nombre) - 1);
    nombre[sizeof(nombre) - 1] = '\0';
    strncpy(telefono, c.getTelefono().c_str(), sizeof(telefono) - 1);
    telefono[sizeof(telefono) - 1] = '\0';
    strncpy(correo, c.getCorreo().c_str(), sizeof(correo) - 1);
    correo[sizeof(correo) - 1] = '\0';
    strncpy(historial, c.gethistorialCompras().c_str(), sizeof(historial) - 1);
    historial[sizeof(historial) - 1] = '\0';

    // Escribimos los datos en binario
    archivo.write(reinterpret_cast<char*>(&id), sizeof(int));
    archivo.write(reinterpret_cast<char*>(&saldo), sizeof(double));
    archivo.write(nombre, sizeof(nombre));
    archivo.write(telefono, sizeof(telefono));
    archivo.write(correo, sizeof(correo));
    archivo.write(historial, sizeof(historial));

    archivo.close();
    cout << "Cliente guardado correctamente.\n";
}