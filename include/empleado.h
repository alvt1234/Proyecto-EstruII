#ifndef EMPLEADO_H
#define EMPLEADO_H

#include <iostream>
#include <string>
using namespace std;

class empleado {
    private:
    int id;
    string nombre;
    string departamento;
    string puesto;
    double salario;
    string estado ;

 public:

    empleado();
    empleado(int id, string nombre, string departamento, string puesto, double salario, string estado);

    //getters
    int getid();
    string getnombre();
    string getdepartamento();
    string getpuesto();
    double getsalario();
    string getestado();

    //setters
    void setid(int id);
    void setnombre(string nombre);
    void setdepartamento(string departamento);
    void setpuesto(string puesto);
    void setsalario(double salario);
    void setestado(string estado);

};
#endif // EMPLEADO_H
