#ifndef CLIENTE_H
#define CLIENTE_H

#include <iostream>
#include <string>
using namespace std;

class cliente {
    private:
        int idCliente;
        string nombre;
        string telefono;
        string correo;
        double saldo;
        string historialCompras;
       
    public:
        cliente();
        cliente(int id, string nombre, string telefono, string correo, double saldo, string historial);

        void setIdCliente(int);
        void setNombre(string);
        void setTelefono(string);
        void setCorreo(string);
        void sethistorialCompras(string);
        void setSaldo(double);
        int getIdCliente();
        
        string gethistorialCompras();
        string getNombre();
        string getTelefono();
        string getCorreo();
        double getSaldo();

};

#endif