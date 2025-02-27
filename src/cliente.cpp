#include "../include/cliente.h"
#include "../include/archivobinario.h"

cliente::cliente(): idCliente(0), nombre(""), telefono(""), correo(""), saldo(0), historialCompras("")
{
}

cliente::cliente(int id, string nombre, string telefono, string correo, double saldo, string historial)
{
    //archivobinario archivo("clientes.txt");
    this -> idCliente = id;
    this -> nombre = nombre;
    this -> telefono = telefono;
    this -> correo = correo;
    this -> saldo = saldo;
    this -> historialCompras = historial;
    //archivo.aggcliente(id,nombre,telefono,correo,saldo,historial);
}

/*cliente::cliente(int,string, string, string, string, string, string, string, string, string)
{
    this -> idCliente = idCliente;
    this -> nombre = nombre;
    this -> telefono = telefono;
    this -> correo = correo;
    this -> saldo = saldo;
    this -> historialCompras = historialCompras;

}
*/
void cliente::setIdCliente(int idCliente)
{
    this -> idCliente = idCliente;
}

void cliente::setNombre(string nombre)
{
    this -> nombre = nombre;
}

void cliente::setTelefono(string telefono)
{
    this -> telefono = telefono;
}

void cliente::setCorreo(string correo)
{
    this -> correo = correo;
}

void cliente::sethistorialCompras(string historialCompras)
{
    this -> historialCompras = historialCompras;
}

void cliente::setSaldo(double saldo)
{
    this -> saldo = saldo;
}

int cliente::getIdCliente()
{
    return idCliente;
}

string cliente::gethistorialCompras()
{
    return historialCompras;
}

string cliente::getNombre()
{
    return nombre;
}

string cliente::getTelefono()
{
    return telefono;
}

string cliente::getCorreo()
{
    return correo;
}

double cliente::getSaldo()
{
    return saldo;
}


