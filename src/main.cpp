#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <thread>   
#include <chrono>
#include "../include/venta.h"
#include "../include/cliente.h"
#include "../include/producto.h"
#include "../include/pedido.h"
#include "../include/empleado.h"
#include "../include/archivobinario.h"
#include "../include/arbolB.h"  
#include "../include/tabladispersion.h" 
using namespace std; 

arbolB empleados(3);  //arbolB para empleados de grado 3
arbolB productos(3);  //arbolB para productos de grado 3
ArchivoBinario archivo;
tabladispersion clientes;
tabladispersion pedidos;



void Empleados() {
    cout << "Gestión de Empleados:\n";
    cout << "1. Agregar empleado\n";
    cout << "2. Buscar empleado\n";
    cout << "3. Eliminar empleado\n";
    cout << "4. Mostrar empleados\n";
    cout << "0. Regresar al menu principal\n";

    int opcion;
    cin >> opcion;
    int id;
    string nombre, departamento, puesto,estado;
    double sueldo;
    switch (opcion) {
        case 1: {  // Agregar empleado
            int id;
            string nombre, departamento, puesto,estado;
            double sueldo;
            cout << "Ingrese ID del empleado: \n";
            cin >> id;
            if(archivo.verificarIDempleado(id)){
                break;
            }
            cout << "Ingrese nombre del empleado: \n";
            cin.ignore();
            getline(cin, nombre);
            cout << "Ingrese departamento del empleado: " << endl;
            getline(cin, departamento);
            cout << "Ingrese puesto del empleado: \n";
            getline(cin, puesto);
            cout << "Ingrese estado del empleado: \n";
            getline(cin, estado);
            cout << "Ingrese sueldo del empleado: \n";
            cin >> sueldo;
            empleado emp(id,nombre,departamento,puesto,sueldo,estado);
            archivo.aggEmpleado(emp);            
            empleados.insertar(id); // 🔹 Agregar al Árbol B
            cout << "Empleado con ID " << id << " agregado.\n";
            break;
        }
        case 2: {  // Buscar empleado
            int id;
            cout << "Ingrese ID del empleado a buscar: ";
            cin >> id;
            if (empleados.buscar(id)) {
                archivo.buscarEmpleado(empleados);
               
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
        case 4: {  // mostrar empleado
            archivo.mostrarEmpleados();
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
    cout << "0. Regresar al menu principal\n";

    int opcion;
    cin >> opcion;

    switch (opcion) {
        case 1: {  
            int id,cantidad;
            double precio;
            string nombre,estado,categoria;
            cout << "Ingrese ID del producto: ";
            cin >> id;
            if(archivo.verificarIDproducto(id)){
                break;
            }
            cout<<" Nombre producto: ";
            cin >>nombre;
            cout <<" Categoria: ";
            cin>> categoria;
            cout << "Precio: ";
            cin>> precio;
            cout << "Cantidad: ";
            cin>> cantidad;
           
            productos.insertar(id); // 🔹 Agregar al Árbol B
            cout << "Producto con ID " << id << " agregado.\n";
            producto nuevoproducto(id,nombre,categoria,precio,cantidad);
            archivo.aggproducto(nuevoproducto);
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
            cout << "Lista de productos: ";
            archivo.mostrarProductos();
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
    cout << "3. Eliminar cliente\n";
    cout << "0. Regresar al menu principal\n";
    
    int opcion;
    cin >> opcion;
    
    switch (opcion) {
        case 1: {
            int id;
            string nombre, correo, telefono, historialCompras;
            double saldo;
            
            cout << "Ingrese ID del cliente: ";
            cin >> id;
            if(archivo.verificarIDcliente(id)){
                break;
            }
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
            cliente nuevoCliente(id, nombre, telefono, correo, saldo, historialCompras);
            archivo.aggCliente(nuevoCliente);
            // Creamos un resumen de la información del cliente
            string info = "Nombre: " + nombre + ", Correo: " + correo + 
                          ", Telefono'-': " + telefono + ", Saldo: " + to_string(saldo) +
                          ", Historial: " + historialCompras;
            // Insertamos en la tabla de dispersión
            clientes.insertar(id, info);
            cout << "Cliente agregado.\n";
            break;
        }
        case 2: {
            int id;
            
            cout << "Ingrese ID del cliente a buscar: ";
            cin >> id;
            string resultado = clientes.buscar(id);
            if (resultado != "No encontrado")
                cout << "Cliente encontrado: " << resultado << endl;
            else
                cout << "Cliente no encontrado.\n";
            break;
        }
        case 3: {
            int id;
            cout << "Ingrese ID del cliente a eliminar: ";
            cin >> id;
            clientes.eliminar(id);
            cout << "Cliente eliminado.\n";
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
    cout << "0. Regresar al menu principal\n";
    
    int opcion;
    cin >> opcion;
    
    switch (opcion) {
        case 1: {
            int idVenta, idCliente;
            vector<int> productosVendidos;
            vector<int> cantidades;

            cout << "Ingrese ID de la venta: ";
            cin >> idVenta;
            if(archivo.verificarIDventas(idVenta)){
                break;
            }
            cout << "Ingrese ID del cliente: ";
            cin >> idCliente;
            if(!archivo.verificarIDcliente(idCliente)){
                cout<<"Cliente inexistente";
                break;
            }
            int cantidadProductos;
            cout << "¿Cuántos productos desea vender? ";
            cin >> cantidadProductos;

            for (int i = 0; i < cantidadProductos; ++i) {
                int idProducto, cantidad;
                cout << "Ingrese ID del producto " << i + 1 << ": ";
                cin >> idProducto;
                if(!archivo.verificarIDproducto(idProducto)){
                    cout<<"Producto inexistente \n";
                    i--;
                    continue;
                }else{
                productosVendidos.push_back(idProducto);
                cout << "Ingrese cantidad de este producto: ";
                cin >> cantidad;
                cantidades.push_back(cantidad);
                }
                
            }

            double total;
            cout << "Ingrese el total de la venta: ";
            cin >> total;

            string fecha;
            cout << "Ingrese la fecha de la venta (año/mes/dia): ";
            cin >> fecha;
            venta ven(idVenta, idCliente, productosVendidos, cantidades, total, fecha);
            archivo.ventas(ven);
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
    cout << "0. Regresar al menu principal\n";
    
    int opcion;
    cin >> opcion;
    
    switch (opcion) {
        case 1: {
            int idPedido, idCliente;
            vector<int> productosSolicitados;
            int cantidadProductos;

            cout << "Ingrese ID del pedido: ";
            cin >> idPedido;
            if(archivo.verificarIDpedido(idPedido)){
                break;
            }
            cout << "Ingrese ID del cliente: ";
            cin >> idCliente;
            if(!archivo.verificarIDcliente(idCliente)){
                cout << "El cliente no existe.\n";
                break;
            }
            cout << "Cantidad de productos a pedir: ";
            cin >> cantidadProductos;
            for (int i = 0; i < cantidadProductos; ++i) {
                int idProducto;
                cout << "Ingrese ID del producto " << i + 1 << ": ";
                cin >> idProducto;
                if(!archivo.verificarIDproducto(idProducto)){
                    cout << "El producto no existe.\n";
                    i--;
                }else
                productosSolicitados.push_back(idProducto);
            }

            string fechaEntrega;
            cout << "Ingrese la fecha de entrega (año-mes-dia): ";
            cin >> fechaEntrega;

            string estado;
            cout << "Ingrese el estado del pedido (pendiente/procesado/enviado): ";
            cin >> estado;
            
            string pedidoInfo = "ID Cliente: " + to_string(idCliente) + 
                                ", Fecha: " + fechaEntrega + 
                                ", Estado: " + estado;
            // Insertamos el pedido en la tabla de dispersión
            pedidos.insertar(idPedido, pedidoInfo);
            pedido pedido(idPedido,idCliente,productosSolicitados,fechaEntrega,estado);
            archivo.pedidos(pedido);
            cout << "Pedido registrado.\n";
            break;
        }
        case 2: {
            int id;
            cout << "Ingrese ID del pedido a buscar: ";
            cin >> id;
            string resultado = pedidos.buscar(id);
            if (resultado != "No encontrado")
                cout << "Pedido encontrado: " << resultado << endl;
            else
                cout << "Pedido no encontrado.\n";
            break;
        }
        case 3: {
            int id;
            cout << "Ingrese ID del pedido a eliminar: ";
            cin >> id;
            pedidos.eliminar(id);
            cout << "Pedido eliminado.\n";
            break;
        }
        case 0:
            return;
        default:
            cout << "Opción no válida.\n";
    }
}

void reportes(ArchivoBinario& archivo){

    cout << "GENERAR REPORETES:\n";
    cout << "1. Reportes Clientes\n";
    cout << "2. Reporte Empleados\n";
    cout << "3. Reporte Productos\n";
    cout << "4. Reporte Ventas\n";
    cout << "5. Reporte General (Paralelo)\n";
    cout << "6. Reporte Pedidos\n";
    cout << "0. Regresar al menu principal\n";
    
    int opcion;
    cout<<"Ingrese una opcion: ";
    cin >> opcion;

    switch (opcion) {
        case 1: {
            archivo.reportesClientes();
            break;
        }
        case 2: {
           archivo.reportesEmpleados();
            break;
        }
        case 3: {
            archivo.reportesProductos();
            break;
        }
        case 4: {
            archivo.reportesVentas();
            break;
        }
        case 5: {
            
            auto start = std::chrono::high_resolution_clock::now();
            
            std::thread t1(&ArchivoBinario::reportesClientes, &archivo);
            std::thread t2(&ArchivoBinario::reportesEmpleados, &archivo);
            std::thread t3(&ArchivoBinario::reportesProductos, &archivo);
            std::thread t4(&ArchivoBinario::reportesVentas, &archivo);

            t1.join();
            t2.join();
            t3.join();
            t4.join();

            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = end - start;
            std::cout << "Tiempo total de lectura paralela: " << duration.count() << " ms\n";
            break;
        }
        case 6: {
            archivo.reportesPedidos();
            break;
        }
        case 0:
            return;
        default:
            cout << "Opción no valida.\n";
    }

}

int main(){
    int opcion;
    archivo.cargarClientes(clientes);
    archivo.buscarEmpleado(empleados);
    archivo.buscarpedido(pedidos);
    while (true){
    cout << "*************************************************\n";
    cout << "*                                               *\n";
    cout << "*         Bienvenido al menu de gestion         *\n";
    cout << "*                                               *\n";
    cout << "*************************************************\n";
    cout << "*                                               *\n";
    cout << "*           Seleccione una opcion:              *\n";
    cout << "*                                               *\n";
    cout << "* 1. Clientes                                   *\n";
    cout << "* 2. Productos                                  *\n";
    cout << "* 3. Pedidos                                    *\n";
    cout << "* 4. Empleados                                  *\n";
    cout << "* 5. Ventas                                     *\n";
    cout << "* 6. Reportes                                   *\n";
    cout << "* 7. Salir                                      *\n";
    cout << "*                                               *\n";
    cout << "*************************************************\n";
    cout << "Ingrese una opcion: ";
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
                reportes(archivo);
                break;
            case 7:
                cout << "Saliendo\n";  
                return 0;  
            default:
                cout << "Opcion no valida.\n";
                break;
        }
    }
}


