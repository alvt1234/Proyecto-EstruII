#include <iostream>
#include <string>
#include <vector>
#include "venta.h"
#include "cliente.h"
#include "producto.h"
#include "pedido.h"
#include "empleado.h"
using namespace std; 


void Empleados() {
    cout << "Gestión de Empleados:\n";
    cout << "1. Agregar empleado\n";
    cout << "2. Eliminar empleado\n";
    cout << "0. Regresar al menú principal\n";
    
    int opcion;
    cin >> opcion;
    
    switch (opcion) {
        case 1: {
            int id;
            string nombre, departamento, puesto, estado;
            double salario;
            cout << "Ingrese ID: ";
            cin >> id;
            cout << "Ingrese nombre: ";
            cin.ignore(); 
            getline(cin, nombre);
            cout << "Ingrese departamento: ";
            getline(cin, departamento);
            cout << "Ingrese puesto: ";
            getline(cin, puesto);
            cout << "Ingrese salario: ";
            cin >> salario;
            cout << "Ingrese estado (activo/inactivo): ";
            cin >> estado;

            empleado emp(id, nombre, departamento, puesto, salario, estado);
            cout << "Empleado agregado.\n";
            break;
        }
        case 2: {
            int id;
            cout << "Ingrese ID del empleado a eliminar: ";
            cin >> id;
            cout << "Empleado eliminado\n";
            break;
        }
        case 0:
            return;
        default:
            cout << "Opción no válida.\n";
    }
}


void gestionarInventarios() {
    cout << "Gestión de Inventarios:\n";
    cout << "1. Agregar producto\n";
    cout << "2. Buscar producto\n";
    cout << "3. Eliminar producto\n";
    cout << "0. Regresar al menú principal\n";
    
    int opcion;
    cin >> opcion;
    
    switch (opcion) {
        case 1: {
            int id;
            string nombre, categoria, estado;
            double precio;
            int cantidad;
            cout << "Ingrese ID del producto: ";
            cin >> id;
            cout << "Ingrese nombre del producto: ";
            cin.ignore(); 
            getline(cin, nombre);
            cout << "Ingrese categoría: ";
            getline(cin, categoria);
            cout << "Ingrese precio: ";
            cin >> precio;
            cout << "Ingrese cantidad en stock: ";
            cin >> cantidad;
            cout << "Ingrese estado (disponible/discontinuado): ";
            cin >> estado;

            producto prod(id, nombre, categoria, precio, cantidad, estado);
            cout << "Producto agregado.\n";
            break;
        }
        case 2: {
            int id;
            cout << "Ingrese ID del producto a buscar: ";
            cin >> id;
            cout << "Producto encontrado (simulado).\n";
            break;
        }
        case 3: {
            int id;
            cout << "Ingrese ID del producto a eliminar: ";
            cin >> id;
            cout << "Producto eliminado.\n";
            break;
        }
        case 0:
            return;
        default:
            cout << "Opción no válida.\n";
    }
}


void gestionarClientes() {
    cout << "Gestión de Clientes:\n";
    cout << "1. Agregar cliente\n";
    cout << "0. Regresar al menú principal\n";
    
    int opcion;
    cin >> opcion;
    
    switch (opcion) {
        case 1: {
            int id;
            string nombre, correo, telefono, historialCompras;
            double saldo;
            
            cout << "Ingrese ID del cliente: ";
            cin >> id;
            cout << "Ingrese nombre del cliente: ";
            cin.ignore();  
            getline(cin, nombre);
            cout << "Ingrese correo: ";
            getline(cin, correo);
            cout << "Ingrese teléfono: ";
            getline(cin, telefono);
            cout << "Ingrese saldo: ";
            cin >> saldo;
            cout << "Ingrese historial de compras: ";
            cin.ignore(); 
            getline(cin, historialCompras);

          
            cliente cli(id, nombre, correo, telefono, saldo, historialCompras);
            cout << "Cliente agregado.\n";
            break;
        }
        
        case 0:
            return;
        default:
            cout << "Opción no válida.\n";
    }  
}


void gestionarVentas() {
    cout << "Gestión de Ventas:\n";
    cout << "1. Realizar venta\n";
    cout << "0. Regresar al menú principal\n";
    
    int opcion;
    cin >> opcion;
    
    switch (opcion) {
        case 1: {
            int idVenta, idCliente;
            vector<int> productosVendidos;
            vector<int> cantidades;

            cout << "Ingrese ID de la venta: ";
            cin >> idVenta;
            cout << "Ingrese ID del cliente: ";
            cin >> idCliente;

            int cantidadProductos;
            cout << "¿Cuántos productos desea vender? ";
            cin >> cantidadProductos;

            for (int i = 0; i < cantidadProductos; ++i) {
                int idProducto, cantidad;
                cout << "Ingrese ID del producto " << i + 1 << ": ";
                cin >> idProducto;
                productosVendidos.push_back(idProducto);

                cout << "Ingrese cantidad de este producto: ";
                cin >> cantidad;
                cantidades.push_back(cantidad);
            }

            double total;
            cout << "Ingrese el total de la venta: ";
            cin >> total;

            string fecha;
            cout << "Ingrese la fecha de la venta (año-mes-dia): ";
            cin >> fecha;
            venta ven(idVenta, idCliente, productosVendidos, cantidades, total, fecha);
            cout << "Venta realizada.\n";
            break;
        }
        case 0:
            return;
        default:
            cout << "Opción no válida.\n";
    }

}


void gestionarPedidos() {
    cout << "Gestión de Pedidos:\n";
    cout << "1. Realizar pedido\n";
    cout << "2. Buscar pedido\n";
    cout << "3. Eliminar pedido\n";
    cout << "0. Regresar al menú principal\n";
    
    int opcion;
    cin >> opcion;
    
    switch (opcion) {
        case 1: {
            int idPedido, idCliente;
            vector<int> productosSolicitados;
            int cantidadProductos;

            cout << "Ingrese ID del pedido: ";
            cin >> idPedido;
            cout << "Ingrese ID del cliente: ";
            cin >> idCliente;

            cout << "Cantidad de productos a pedir:  ";
            cin >> cantidadProductos;
            for (int i = 0; i < cantidadProductos; ++i) {
                int idProducto;
                cout << "Ingrese ID del producto " << i + 1 << ": "; // i + 1 para mostrar el número de producto
                cin >> idProducto;
                productosSolicitados.push_back(idProducto);
            }

            string fechaEntrega;
            cout << "Ingrese la fecha de entrega (año-mes-dia): ";
            cin >> fechaEntrega;

            string estado;
            cout << "Ingrese el estado del pedido (pendiente/procesado/enviado): ";
            cin >> estado;
            pedido ped(idPedido, idCliente, productosSolicitados, fechaEntrega, estado);
            cout << "Pedido hecho.\n";
            break;
        }
        case 2: {
            int id;
            cout << "Ingrese ID del pedido a buscar: ";
            cin >> id;
            cout << "Pedido encontrado\n";
            break;
        }
        case 3: {
            int id;
            cout << "Ingrese ID del pedido a eliminar: ";
            cin >> id;
            cout << "Pedido eliminado\n";
            break;
        }
        case 0:
            return;
        default:
            cout << "Opción no válida.\n";
    }
}


int main(){
    int opcion;

    while (true){
    cout << "*************************************************\n";
    cout << "*                                               *\n";
    cout << "*           Bienvenido al menú de gestión       *\n";
    cout << "*                                               *\n";
    cout << "*************************************************\n";
    cout << "*                                               *\n";
    cout << "*           Seleccione una opción:               *\n";
    cout << "*                                               *\n";
    cout << "* 1. Clientes                                    *\n";
    cout << "* 2. Productos                                   *\n";
    cout << "* 3. Pedidos                                    *\n";
    cout << "* 4. Empleados                                  *\n";
    cout << "* 5. Ventas                                     *\n";
    cout << "* 6. Salir                                      *\n";
    cout << "*                                               *\n";
    cout << "*************************************************\n";
    cout << "Ingrese una opción: ";
    cin >> opcion;
        switch (opcion){
            case 1:
                gestionarClientes();  
                break;
            case 2:
                gestionarInventarios();  
                break;
            case 3:
                gestionarPedidos();  
                break;
            case 4:
                Empleados();  
            case 5:
                gestionarVentas();
                break;
            case 6:
                cout << "Saliendo\n";  
                return 0; 
            default:
                cout << "Opción no válida.\n";
                break;
        }
    }
}
