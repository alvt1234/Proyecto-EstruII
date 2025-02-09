#include "../include/empleado.h"
#include <iostream>

empleado::empleado() : id(0), nombre(""), departamento(""), puesto(""), salario(0), estado("inactivo") {}


empleado::empleado(int id, string nombre, string departamento, string puesto, double salario, string estado)
{
    this -> id = id;
    this -> nombre = nombre;
    this -> departamento = departamento;
    this -> puesto = puesto;
    this -> salario = salario;
    this -> estado = estado;
}


int empleado::getid()
{
    return id;
}

string empleado::getnombre()
{
    return nombre;
}

string empleado::getdepartamento()
{
    return departamento;
}

string empleado::getpuesto()
{
    return puesto;
}

double empleado::getsalario()
{
    return salario;
}

string empleado::getestado()
{
    return estado;
}

void empleado::setid(int id)
{
    this -> id = id;
}

void empleado::setnombre(string nombre)
{
    this -> nombre = nombre;
}

void empleado::setdepartamento(string departamento)
{
    this -> departamento = departamento;
}

void empleado::setpuesto(string puesto)
{
    this -> puesto = puesto;
}

void empleado::setsalario(double salario)
{
    this -> salario = salario;
}

void empleado::setestado(string estado)
{
    this -> estado = estado;
}
