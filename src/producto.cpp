#include "producto.h"

producto::producto() : idProducto(0), nombre(""), categoria(""), precio(0), cantidadStock(0), estado("")
{
}


producto::producto(int id, string nombre, string categoria, double precio, int cantidad, string estado)
{   
    this->idProducto = id;
    this->nombre = nombre;
    this->categoria = categoria;
    this->precio = precio;
    this->cantidadStock = cantidad;
    this->estado = estado;
}

int producto::getid()
{
    return idProducto;
}

string producto::getnombre()
{
    return nombre;
}

string producto::getcategoria()
{
    return categoria;
}

double producto::getprecio()
{
    return precio;
}

int producto::getcantidad()
{
    return cantidadStock;
}

string producto::getestado()
{
    return estado;
}

void producto::setid(int id)
{
    this->idProducto = id;
}

void producto::setnombre(string nombre)
{
    this->nombre = nombre;
}

void producto::setcategoria(string categoria)
{
    this->categoria = categoria;
}

void producto::setprecio(double precio)
{
    this->precio = precio;
}   

void producto::setcantidad(int cantidad)
{
    this->cantidadStock = cantidad;
}

void producto::setestado(string estado)
{
    this->estado = estado;
}


