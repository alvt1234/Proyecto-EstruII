#ifndef PRODUCTO_H
#define PRODUCTO_H
#include <iostream>
#include <string>
using namespace std;

class producto {
    private:
    int idProducto;
    string nombre;
    string categoria;
    double precio;
    int cantidadStock;

 public:

    producto();
    producto(int id, string nombre, string categoria, double precio, int cantidad);

    //getters
    int getid();
    string getnombre();
    string getcategoria();
    double getprecio();
    int getcantidad();

    //setters
    void setid(int id);
    void setnombre(string nombre);
    void setcategoria(string categoria);
    void setprecio(double precio);
    void setcantidad(int cantidad);

};

#endif