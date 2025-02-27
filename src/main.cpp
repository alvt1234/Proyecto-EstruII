#include <iostream>
#include <string>
#include <vector>
#include "../include/venta.h"
#include "../include/cliente.h"
#include "../include/producto.h"
#include "../include/pedido.h"
#include "../include/empleado.h"
#include "../include/archivobinario.h"
#include "../include/arbolB.h"  

using namespace std; 

arbolB empleados(3);  //arbolB para empleados de grado 3
arbolB productos(3);  //arbolB para productos de grado 3
ArchivoBinario archivo;

void Empleados() {
    cout << "Gestión de Empleados:\n";
    cout << "1. Agregar empleado\n";
    cout << "2. Buscar empleado\n";
    cout << "3. Eliminar empleado\n";
    cout << "4. Mostrar empleados\n";
    cout << "0. Regresar al menú principal\n";

    int opcion;
    cin >> opcion;

    switch (opcion) {
        case 1: {  // Agregar empleado
            int id;
            cout << "Ingrese ID del empleado: ";
            cin >> id;
            empleados.insertar(id); // 🔹 Agregar al Árbol B
            cout << "Empleado con ID " << id << " agregado.\n";
            break;
        }
        case 2: {  // Buscar empleado
            int id;
            cout << "Ingrese ID del empleado a buscar: ";
            cin >> id;
            if (empleados.buscar(id)) {
                cout << "Empleado con ID " << id << " encontrado.\n";
            } else {
                cout << "Empleado con ID " << id << " NO encontrado.\n";
            }
            break;
        }
        case 3: {  // Eliminar empleado
            int id;
            cout << "Ingrese ID del empleado a eliminar: ";
            cin >> id;
            empleados.eliminar(id);
            cout << "Empleado con ID " << id << " eliminado.\n";
            break;
        }
        case 4: {  // Mostrar empleados
            cout << "Lista de empleados en orden: ";
            empleados.recorrer();
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
    cout << "4. Mostrar productos\n";
    cout << "0. Regresar al menú principal\n";

    int opcion;
    cin >> opcion;

    switch (opcion) {
        case 1: {  
            int id,categoria,cantidad;
            double precio;
            string nombre,estado;
            cout << "Ingrese ID del producto: ";
            cin >> id;
            cout<<" Nombre producto: ";
            cin >>nombre;
            cout <<" Categoria: ";
            cin>> categoria;
            cout << "Precio: ";
            cin>> precio;
            cout << "Cantidad: ";
            cin>> cantidad;
            cout<< "Estado: ";
            cin>> estado;
            productos.insertar(id); // 🔹 Agregar al Árbol B
            cout << "Producto con ID " << id << " agregado.\n";
            break;
        }
        case 2: {  
            int id;
            cout << "Ingrese ID del producto a buscar: ";
            cin >> id;
            if (productos.buscar(id)) {
                cout << "Producto con ID " << id << " encontrado.\n";

            } else {
                cout << "Producto con ID " << id << " NO encontrado.\n";
            }
            break;
        }
        case 3: {  
            int id;
            cout << "Ingrese ID del producto a eliminar: ";
            cin >> id;
            productos.eliminar(id);
            cout << "Producto con ID " << id << " eliminado.\n";
            break;
        }
        case 4: {  
            cout << "Lista de productos en orden: ";
            productos.recorrer();
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
    cout << "2. Buscar cliente\n";
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
            
            archivo.aggCliente(cli);
            break;
        }
        case 2: {
            cout<<"====Buscar Cliente===";
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
                break;
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


