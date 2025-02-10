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
    string estado ;

 public:

    producto();
    producto(int id, string nombre, string categoria, double precio, int cantidad, string estado);

    //getters
    int getid();
    string getnombre();
    string getcategoria();
    double getprecio();
    int getcantidad();
    string getestado();

    //setters
    void setid(int id);
    void setnombre(string nombre);
    void setcategoria(string categoria);
    void setprecio(double precio);
    void setcantidad(int cantidad);
    void setestado(string estado);

};

#endif