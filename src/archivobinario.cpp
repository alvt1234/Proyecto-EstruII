#include "archivobinario.h"
#include <iomanip>  
#include <thread>
#include <chrono>
#include <mutex>

std::string ArchivoBinario::comprimirDatos(const std::string& datos) {
    return huffman.compress(datos);
}

std::string ArchivoBinario::descomprimirDatos(const std::string& datosComprimidos) {
    return huffman.decompress(datosComprimidos, huffman.getCodes());
}
void ArchivoBinario::mostrarProductos(int idd) {
    std::ifstream archivo("Productos.bin", std::ios::binary);
    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo de productos.\n";
        return;
    }

    std::cout << "\n📦 LISTA DE PRODUCTOS GUARDADOS:\n";
    std::cout << "================================\n";

    int id, cantidad;
    char nombre[50], categoria[50];
    double precio;

    while (archivo.read(reinterpret_cast<char*>(&id), sizeof(int))) {
        archivo.read(nombre, sizeof(nombre));
        archivo.read(categoria, sizeof(categoria));
        archivo.read(reinterpret_cast<char*>(&precio), sizeof(double));
        archivo.read(reinterpret_cast<char*>(&cantidad), sizeof(int));

        nombre[sizeof(nombre) - 1] = '\0';     
        categoria[sizeof(categoria) - 1] = '\0';
        if(idd==id){
        std::cout << "ID: " << id << "\n";
        std::cout << "Nombre: " << nombre << "\n";
        std::cout << "Categoría: " << categoria << "\n";
        std::cout << "Precio: " << precio << "\n";
        std::cout << "Cantidad: " << cantidad << "\n";
        std::cout << "--------------------------------\n";
        break;
        }
    }

    archivo.close();
}
void ArchivoBinario::mostrarEmpleados() {
    std::ifstream archivo("empleados.bin", std::ios::binary);
    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo de empleados.\n";
        return;
    }

    int id;
    double salario;
    char nombre[50], departamento[50], puesto[50], estado[50];

    while (archivo.read(reinterpret_cast<char*>(&id), sizeof(int))) {
        archivo.read(nombre, sizeof(nombre));
        archivo.read(departamento, sizeof(departamento));
        archivo.read(puesto, sizeof(puesto));
        archivo.read(reinterpret_cast<char*>(&salario), sizeof(double));
        archivo.read(estado, sizeof(estado));

        nombre[sizeof(nombre) - 1] = '\0';
        departamento[sizeof(departamento) - 1] = '\0';
        puesto[sizeof(puesto) - 1] = '\0';
        estado[sizeof(estado) - 1] = '\0';

        std::cout << "ID: " << id << "\n";
        std::cout << "Nombre: " << nombre << "\n";
        std::cout << "Departamento: " << departamento << "\n";
        std::cout << "Puesto: " << puesto << "\n";
        std::cout << "Salario: " << salario << "\n";
        std::cout << "Estado: " << estado << "\n";
        std::cout << "---------------------------------\n";
    }

    archivo.close();
}


void ArchivoBinario::aggCliente(cliente c) {
    int id = c.getIdCliente();
    char nombre[50], telefono[50], correo[50], historial[100];
    double saldo=c.getSaldo();



    strncpy(nombre, c.getNombre().c_str(), sizeof(nombre) - 1);
    nombre[sizeof(nombre) - 1] = '\0';  // Aseguramos el terminador nulo
    strncpy(telefono, c.getTelefono().c_str(), sizeof(telefono) - 1);
    telefono[sizeof(telefono) - 1] = '\0'; 
    strncpy(correo, c.getCorreo().c_str(), sizeof(correo) - 1);
    correo[sizeof(correo) - 1] = '\0'; 
    strncpy(historial, c.gethistorialCompras().c_str(), sizeof(historial) - 1);
    historial[sizeof(historial) - 1] = '\0'; 

    std::ofstream archivo("clientes.bin", std::ios::out | std::ios::binary | std::ios::app);

    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo de clientes para agregar datos.\n";
        return;
    }

    // Escribimos los datos en binario
    archivo.write(reinterpret_cast<char*>(&id), sizeof(int));
    archivo.write(reinterpret_cast<char*>(&saldo), sizeof(double));
    archivo.write(nombre, sizeof(nombre));
    archivo.write(telefono, sizeof(telefono));
    archivo.write(correo, sizeof(correo));
    archivo.write(historial, sizeof(historial));

    archivo.close();
    std::cout << "Cliente guardado correctamente.\n";
}

bool ArchivoBinario::verificarIDcliente(int id) {
    std::ifstream archivo("clientes.bin", std::ios::in | std::ios::binary);  
    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo de clientes para lectura.\n";
        return false;
    }

    int idcliente;
    char nombre[50], telefono[50], correo[50], historial[100];
    double saldo;

    // Leemos los clientes en un ciclo hasta llegar al final del archivo
    while (archivo.read(reinterpret_cast<char*>(&idcliente), sizeof(int))) {
        archivo.read(reinterpret_cast<char*>(&saldo), sizeof(double));
        archivo.read(nombre, sizeof(nombre));
        archivo.read(telefono, sizeof(telefono));
        archivo.read(correo, sizeof(correo));
        archivo.read(historial, sizeof(historial));

        // Verificamos si el id coincide
        if (id == idcliente) {
            std::cout << "ID EXISTENTE\n";
            archivo.close();
            return true;
        }
    }

    archivo.close();
    return false;
}

void ArchivoBinario::cargarClientes(tabladispersion& clientes) {
    std::ifstream archivo("clientes.bin", std::ios::in | std::ios::binary);  
    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo de clientes para lectura.\n";
        return;
    }

    int idcliente;
    char nombre[50], telefono[50], correo[50], historial[100];
    double saldo;

    // Leemos los clientes en un ciclo hasta llegar al final del archivo
    while (archivo.read(reinterpret_cast<char*>(&idcliente), sizeof(int))) {
        archivo.read(reinterpret_cast<char*>(&saldo), sizeof(double));
        archivo.read(nombre, sizeof(nombre));
        archivo.read(telefono, sizeof(telefono));
        archivo.read(correo, sizeof(correo));
        archivo.read(historial, sizeof(historial));

  

        std::string info = "Nombre: " + std::string(nombre) + ", Correo: " + std::string(correo) +
                           ", Tel: " + std::string(telefono) + ", Saldo: " + std::to_string(saldo) +
                           ", Historial: " + std::string(historial);

        // Insertamos el cliente en la tabla de dispersión
        clientes.insertar(idcliente, info);
    }

    archivo.close();
}

void ArchivoBinario::aggproducto(producto p)
{
    int idproducto=p.getid(),cantidad=p.getcantidad();
    char nombre[50], categoria[50], estado[100];
    double precio=p.getprecio();

    strncpy(nombre, p.getnombre().c_str(), sizeof(nombre) - 1);
    nombre[sizeof(nombre) - 1] = '\0';  // Aseguramos el terminador nulo
    strncpy(categoria, p.getcategoria().c_str(), sizeof(categoria) - 1);
    categoria[sizeof(categoria) - 1] = '\0'; 
   
    
    std::ofstream archivo("Productos.bin", std::ios::out | std::ios::binary | std::ios::app);

    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo de clientes para agregar datos.\n";
        return;
    }

     // Escribimos los datos en binario
     archivo.write(reinterpret_cast<char*>(&idproducto), sizeof(int));
     archivo.write(nombre, sizeof(nombre));
     archivo.write(categoria, sizeof(categoria));
     archivo.write(reinterpret_cast<char*>(&precio), sizeof(double));
     archivo.write(reinterpret_cast<char*>(&cantidad), sizeof(int));
 
     archivo.close();
     std::cout << "Producto agregado correctamente.\n";
 

}

bool ArchivoBinario::verificarIDproducto(int id)
{
    std::ifstream archivo("Productos.bin", std::ios::in | std::ios::binary);
    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo de productos para verificar datos.\n";
        return false;
        }
        int idproducto;
        char nombre[50], categoria[50], estado[100];
        double precio;
        int cantidad;
        while (archivo.read(reinterpret_cast<char*>(&idproducto), sizeof(int))) {
            archivo.read(nombre, sizeof(nombre));
            archivo.read(categoria, sizeof(categoria));
            archivo.read(reinterpret_cast<char*>(&precio), sizeof(double));
            archivo.read(reinterpret_cast<char*>(&cantidad), sizeof(int));
            if (idproducto == id) {
                cout<<"ID PRODUCTO EXISTENTE\n";
                archivo.close();
                return true;
                }
        }
        archivo.close();
    return false;
}

void ArchivoBinario::pedidos(pedido ped) {
    int idpedido = ped.getIdPedido();
    int idcliente = ped.getIdCliente();  
    std::vector<int> productosSolicitados = ped.getProductosSolicitados(); 
    char fecha[50], estado[50];

   
    strncpy(fecha, ped.getFechaEntrega().c_str(), sizeof(fecha) - 1);
    fecha[sizeof(fecha) - 1] = '\0';  

    strncpy(estado, ped.getEstado().c_str(), sizeof(estado) - 1);
    estado[sizeof(estado) - 1] = '\0'; 

    std::ofstream archivo("pedidos.bin", std::ios::out | std::ios::binary | std::ios::app);

    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo de pedidos para agregar datos.\n";
        return;
    }

    archivo.write(reinterpret_cast<char*>(&idpedido), sizeof(int));
    archivo.write(reinterpret_cast<char*>(&idcliente), sizeof(int));
    archivo.write(fecha, sizeof(fecha));
    archivo.write(estado, sizeof(estado));

    int cantidadProductos = productosSolicitados.size();
    archivo.write(reinterpret_cast<char*>(&cantidadProductos), sizeof(int));

    for (int idProducto : productosSolicitados) {
        archivo.write(reinterpret_cast<char*>(&idProducto), sizeof(int));
    }

    archivo.close();
    std::cout << "Pedido guardado correctamente.\n";
}

bool ArchivoBinario::verificarIDpedido(int id)
{
    std::ifstream archivo("pedidos.bin", std::ios::in | std::ios::binary);
    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo de pedidos para verificar datos.\n";
        return false;
    }

    int idpedido, idcliente, numProductos;
    char fecha[50], estado[50];

    while (archivo.read(reinterpret_cast<char*>(&idpedido), sizeof(int))) {
        archivo.read(reinterpret_cast<char*>(&idcliente), sizeof(int));
        archivo.read(reinterpret_cast<char*>(&numProductos), sizeof(int));
        vector<int> productosSolicitados(numProductos);
        for (int i = 0; i < numProductos; ++i) {
            archivo.read(reinterpret_cast<char*>(&productosSolicitados[i]), sizeof(int));
        }
        archivo.read(fecha, sizeof(fecha));
        fecha[sizeof(fecha) - 1] = '\0';  

        archivo.read(estado, sizeof(estado));
        estado[sizeof(estado) - 1] = '\0';

        if (idpedido == id) {
            std::cout << "ID PEDIDO EXISTENTE\n";
            archivo.close();
            return true;
        }
    }

    archivo.close();
    return false;
}

void ArchivoBinario::buscarpedido(tabladispersion& clientes)
{
    std::ifstream archivo("pedidos.bin", std::ios::in | std::ios::binary);  
    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo de pedidos para lectura.\n";
        return;
    }

    int idpedido, idcliente, productosS;
    char fecha[50], estado[50];

    while (archivo.read(reinterpret_cast<char*>(&idpedido), sizeof(int))) {
        archivo.read(reinterpret_cast<char*>(&idcliente), sizeof(int));
        archivo.read(reinterpret_cast<char*>(&productosS), sizeof(int)); 

        std::vector<int> productosSolicitados(productosS); 
        for (int i = 0; i < productosS; ++i) {
            archivo.read(reinterpret_cast<char*>(&productosSolicitados[i]), sizeof(int));
        }

        archivo.read(fecha, sizeof(fecha));
        archivo.read(estado, sizeof(estado));

        fecha[sizeof(fecha) - 1] = '\0';
        estado[sizeof(estado) - 1] = '\0';

        std::string info = "ID CLIENTE: " + std::to_string(idcliente) + 
                           ", Productos: ";
        for (const auto& producto : productosSolicitados) {
            info += std::to_string(producto) + " ";
        }
        info += ", Fecha: " + std::string(fecha) + ", Estado: " + std::string(estado);

       clientes.insertar(idpedido, info);
    }

    archivo.close();  
}


void ArchivoBinario::aggEmpleado(empleado e)
{
    int id = e.getid();
    char nombre[50], departamento[50], estado[50], puesto[50];
    double sueldo=e.getsalario();

    strncpy(nombre, e.getnombre().c_str(), sizeof(nombre) - 1);
    nombre[sizeof(nombre) - 1] = '\0';  
    strncpy(departamento, e.getdepartamento().c_str(), sizeof(departamento) - 1);
    departamento[sizeof(departamento) - 1] = '\0'; 
    strncpy(estado, e.getestado().c_str(), sizeof(estado) - 1);
    estado[sizeof(estado) - 1] = '\0'; 
    strncpy(puesto, e.getpuesto().c_str(), sizeof(puesto) - 1);
    puesto[sizeof(puesto) - 1] = '\0'; 

    std::ofstream archivo("empleados.bin", std::ios::out | std::ios::binary | std::ios::app);

    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo de empleados para agregar datos.\n";
        return;
    }

    archivo.write(reinterpret_cast<char*>(&id), sizeof(int));
    archivo.write(nombre, sizeof(nombre));
    archivo.write(departamento, sizeof(departamento));
    archivo.write(puesto, sizeof(puesto));
    archivo.write(reinterpret_cast<char*>(&sueldo), sizeof(double));
    archivo.write(estado, sizeof(estado));

    archivo.close();
    std::cout << "Cliente guardado correctamente.\n";
}

bool ArchivoBinario::verificarIDempleado(int id)
{
    std::ifstream archivo("empleados.bin", std::ios::in | std::ios::binary);
    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo de productos para verificar datos.\n";
        return false;
        }
        int idempleados;
        char nombre[50], departamento[50], puesto[100], estado[50];
        double salario;
        while (archivo.read(reinterpret_cast<char*>(&idempleados), sizeof(int))) {
            archivo.read(nombre, sizeof(nombre));
            archivo.read(departamento, sizeof(departamento));
            archivo.read(puesto, sizeof(puesto));
            archivo.read(reinterpret_cast<char*>(&salario), sizeof(double));
            archivo.read(estado, sizeof(estado));
            if (idempleados == id) {
                cout<<"ID EMPLEADO EXISTENTE\n";
                archivo.close();
                return true;
                }
        }
        archivo.close();
    return false;
}

void ArchivoBinario::ventas(venta v)
{
    int idventas = v.getIdVenta();
    int idcliente = v.getIdCliente();
    double total = v.getTotal();
    char fecha[50];

    strncpy(fecha, v.getFecha().c_str(), sizeof(fecha) - 1);
    fecha[sizeof(fecha) - 1] = '\0'; 

    vector<int> productosvendidos = v.getProductosVendidos();
    vector<int> cantidades = v.getCantidades();

    std::ofstream archivo("ventas.bin", std::ios::out | std::ios::binary | std::ios::app);

    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo de ventas para agregar datos.\n";
        return;
    }

    archivo.write(reinterpret_cast<char*>(&idventas), sizeof(int));
    archivo.write(reinterpret_cast<char*>(&idcliente), sizeof(int));
    archivo.write(reinterpret_cast<char*>(&total), sizeof(double));
    archivo.write(fecha, sizeof(fecha));

    int cantidadProductos = productosvendidos.size();
    archivo.write(reinterpret_cast<char*>(&cantidadProductos), sizeof(int));

    for (size_t i = 0; i < productosvendidos.size(); i++) {
        archivo.write(reinterpret_cast<char*>(&productosvendidos[i]), sizeof(int));
        archivo.write(reinterpret_cast<char*>(&cantidades[i]), sizeof(int));
      
    }

    archivo.close();
    std::cout << "Venta guardada correctamente.\n";    
}

bool ArchivoBinario::verificarIDventas(int id)
{
    std::ifstream archivo("ventas.bin", std::ios::in | std::ios::binary);
    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo de ventas para verificar datos.\n";
        return false;
    }

    int idventas, idcliente, cantidadProductos, idproducto, cantidad;
    char fecha[50];
    double total;

    while (archivo.read(reinterpret_cast<char*>(&idventas), sizeof(int))) {
        archivo.read(reinterpret_cast<char*>(&idcliente), sizeof(int));
        archivo.read(reinterpret_cast<char*>(&total), sizeof(double));
        archivo.read(fecha, sizeof(fecha));

        archivo.read(reinterpret_cast<char*>(&cantidadProductos), sizeof(int));
        
        for (int i = 0; i < cantidadProductos; i++) {
            archivo.read(reinterpret_cast<char*>(&idproducto), sizeof(int));
            archivo.read(reinterpret_cast<char*>(&cantidad), sizeof(int));
         
        }

        if (idventas == id) {
            std::cout << "ID VENTA EXISTENTE\n";
            archivo.close();
            return true;
        }
    }

    archivo.close();
    return false;
}

void ArchivoBinario::buscarEmpleado(arbolB& empleado)
{
    std::ifstream archivo("empleados.bin", std::ios::in | std::ios::binary);  
    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo de empleado para lectura.\n";
        return;
    }

    int idempleado;
    char nombre[50], departamento[50], puesto[50], estado[50];
    double salario;

    // Leemos los clientes en un ciclo hasta llegar al final del archivo
    while (archivo.read(reinterpret_cast<char*>(&idempleado), sizeof(int))) {
        archivo.read(nombre, sizeof(nombre));
        archivo.read(departamento, sizeof(departamento));
        archivo.read(puesto, sizeof(puesto));
        archivo.read(reinterpret_cast<char*>(&salario), sizeof(double));
        archivo.read(estado, sizeof(estado));

        // Verifica si los datos fueron leídos correctamente
        /*std::cout << "Empleado cargado: Nombre: " << nombre << ", Departamento: " << departamento 
                  << ", puesto: " << puesto << ", salario: " << salario 
                  << ", Estado: " << estado << std::endl;*/

        std::string info = "Nombre: " + std::string(nombre) + ", Departamento: " + std::string(departamento) +
                           ", Puesto: " + std::string(puesto) + ", Salario: " + std::to_string(salario) +
                           ", Estado: " + std::string(estado);

        // Insertamos el cliente en la tabla de dispersión
        empleado.insertar(idempleado);
    }

    archivo.close();
}

void ArchivoBinario::reportesClientes(){

    auto start = std::chrono::high_resolution_clock::now();
    //abrimos para leerlo
    std::ifstream archivo("clientes.bin", std::ios::in | std::ios::binary);
    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo de clientes para generar el reporte.\n";
        return;
    }

    int idcliente;
    char nombre[50], direccion[50], telefono[50], correo[50], historial[100];
    double saldo;


    cout<<"--------REPORTE DE LOS CLIENTES--------\n";
    cout << std::left << std::setw(10) << "ID"
              << std::setw(20) << "Nombre"
              << std::setw(15) << "Teléfono"
              << std::setw(25) << "Correo"
              << std::setw(10) << "Saldo"
              << std::setw(20) << "Historial" << "\n";
    cout<<"--------------------------------------------------\n";

    while (archivo.read(reinterpret_cast<char*>(&idcliente), sizeof(int))) {
        archivo.read(reinterpret_cast<char*>(&saldo), sizeof(double));
        archivo.read(nombre, sizeof(nombre));
        archivo.read(telefono, sizeof(telefono));
        archivo.read(correo, sizeof(correo));
        archivo.read(historial, sizeof(historial));

        cout << std::left << std::setw(10) << idcliente
        << std::setw(20) << nombre
        << std::setw(15) << telefono
        << std::setw(25) << correo
        << std::setw(10) << saldo
        << std::setw(20) << historial << "\n";
    }

    archivo.close();
    cout<<"----------------------------------------------------\n";
    cout<<"FIN DEL REPORTE\n";

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "Tiempo de lectura: " << duration.count() << " ms\n";
    archivo.close();
}

void ArchivoBinario::reportesEmpleados(){
    auto start = std::chrono::high_resolution_clock::now();
    //abrimos para leerlo
    std::ifstream archivo("empleados.bin", std::ios::in | std::ios::binary);
    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo de empleados para generar el reporte.\n";
        return;
    }

    int idempleado;
    char nombre[50], departamento[50], puesto[50], estado[50];
    double salario;

    cout<<"--------REPORTE DE LOS EMPLEADOS--------\n";
    cout << std::left << std::setw(10) << "ID"
              << std::setw(20) << "Nombre"
              << std::setw(20) << "Departamento"
              << std::setw(20) << "Puesto"
              << std::setw(10) << "Salario"
              << std::setw(15) << "Estado" << "\n";
    cout<<"--------------------------------------------------\n";
    while (archivo.read(reinterpret_cast<char*>(&idempleado), sizeof(int))) {
        archivo.read(nombre, sizeof(nombre));
        archivo.read(departamento, sizeof(departamento));
        archivo.read(puesto, sizeof(puesto));
        archivo.read(reinterpret_cast<char*>(&salario), sizeof(double));
        archivo.read(estado, sizeof(estado));

        std::cout << std::left << std::setw(10) << idempleado
                  << std::setw(20) << nombre
                  << std::setw(20) << departamento
                  << std::setw(20) << puesto
                  << std::setw(10) << salario
                  << std::setw(15) << estado << "\n";
    }
    archivo.close();
    cout<<"----------------------------------------------------\n";
    cout<<"FIN DEL REPORTE\n";

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "Tiempo de lectura: " << duration.count() << " ms\n";
    archivo.close();
}

void ArchivoBinario::reportesProductos(){
    auto start = std::chrono::high_resolution_clock::now();
    //abrimos para leerlo
    std::ifstream archivo("productos.bin", std::ios::in | std::ios::binary);
    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo de productos para generar el reporte.\n";
        return;
    }
    int idproducto;
    char nombre[50], estado[50], categoria[50];
    double precio;
    int cantidad;

    cout<<"--------REPORTE DE LOS PRODUCTOS--------\n";
    cout << std::left << std::setw(10) << "ID"
              << std::setw(20) << "Nombre"
              << std::setw(20) << "Categoría"
              << std::setw(10) << "Precio"
              << std::setw(10) << "Cantidad" << "\n";
    cout<<"--------------------------------------------------\n";
    while (archivo.read(reinterpret_cast<char*>(&idproducto), sizeof(int))) {
        archivo.read(nombre, sizeof(nombre));       
        archivo.read(categoria, sizeof(categoria));
        archivo.read(reinterpret_cast<char*>(&precio), sizeof(double));
        archivo.read(reinterpret_cast<char*>(&cantidad), sizeof(int));
        std::cout << std::left << std::setw(10) << idproducto
                  << std::setw(20) << nombre
                  << std::setw(20) << categoria
                  << std::setw(10) << precio
                  << std::setw(10) << cantidad << "\n";
        }
    archivo.close();
    cout<<"----------------------------------------------------\n";
    cout<<"FIN DEL REPORTE\n";
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "Tiempo de lectura: " << duration.count() << " ms\n";
    archivo.close();
}

void ArchivoBinario::reportesVentas() {
    auto start = std::chrono::high_resolution_clock::now();
    std::ifstream archivo("ventas.bin", std::ios::in | std::ios::binary);
    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo de ventas para generar el reporte.\n";
        return;
    }

    int idventa, idcliente, cantidadProductos;
    double total;
    char fecha[50];

    std::cout << "--------REPORTE DE LAS VENTAS--------\n";
    std::cout << std::left 
              << std::setw(15) << "ID Venta"
              << std::setw(15) << "ID Cliente"
              << std::setw(15) << "Total"
              << std::setw(20) << "Fecha"
              << std::setw(20) << "Productos" 
              << std::setw(15) << "Cantidades" << "\n";
    std::cout << "--------------------------------------------------------------------------------\n";

    while (archivo.read(reinterpret_cast<char*>(&idventa), sizeof(int))) {
        archivo.read(reinterpret_cast<char*>(&idcliente), sizeof(int));
        archivo.read(reinterpret_cast<char*>(&total), sizeof(double));
        archivo.read(fecha, sizeof(fecha));
        archivo.read(reinterpret_cast<char*>(&cantidadProductos), sizeof(int));

        // Imprimir información principal de la venta
        std::cout << std::left 
                  << std::setw(15) << idventa
                  << std::setw(15) << idcliente
                  << std::setw(15) << std::fixed << std::setprecision(2) << total
                  << std::setw(20) << fecha;

        // Leer e imprimir productos y cantidades
        std::string productos = "";
        std::string cantidades = "";
        
        for (int i = 0; i < cantidadProductos; i++) {
            int idproducto, cantidad;
            archivo.read(reinterpret_cast<char*>(&idproducto), sizeof(int));
            archivo.read(reinterpret_cast<char*>(&cantidad), sizeof(int));
            
            productos += std::to_string(idproducto);
            cantidades += std::to_string(cantidad);
            
            if (i < cantidadProductos - 1) {
                productos += ", ";
                cantidades += ", ";
            }
        }

        std::cout << std::setw(20) << productos 
                  << std::setw(15) << cantidades << "\n";
        
        std::cout << "--------------------------------------------------------------------------------\n";
    }

    archivo.close();
    std::cout << "FIN DEL REPORTE\n";
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "Tiempo de lectura: " << duration.count() << " ms\n";
    archivo.close();
} 
void ArchivoBinario::reportesPedidos() {
    auto start = std::chrono::high_resolution_clock::now();
    std::ifstream archivo("pedidos.bin", std::ios::in | std::ios::binary);
    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo de pedidos para generar el reporte.\n";
        return;
    }

    int idpedido, idcliente, cantidadProductos;
    char fecha[50], estado[50];
    double total;

    std::cout << "--------REPORTE DE LOS PEDIDOS--------\n";
    std::cout << "---------------------------------------\n";
    std::cout << std::setw(10) << "ID PEDIDO"
              << std::setw(20) << "ID CLIENTE"
              << std::setw(20) << "FECHA"
              << std::setw(15) << "ESTADO"
              << std::setw(15) << "PRODUCTOS SOLICITADOS"
              << std::setw(15) << "Cantidades" << "\n";
    std::cout << "---------------------------------------\n";

    while (archivo.read(reinterpret_cast<char*>(&idpedido), sizeof(int))) {
        archivo.read(reinterpret_cast<char*>(&idcliente), sizeof(int));
        archivo.read(fecha, sizeof(fecha));
        archivo.read(estado, sizeof(estado));
        archivo.read(reinterpret_cast<char*>(&cantidadProductos), sizeof(int));
       

        // Mostrar información básica del pedido
        std::cout << std::setw(10) << idpedido
                  << std::setw(20) << idcliente
                  << std::setw(20) << fecha
                  << std::setw(15) << estado;

        // Leer los productos solicitados (IDs de productos)
        std::vector<int> productosSolicitados;
        for (int i = 0; i < cantidadProductos; i++) {
            int idproducto;
            archivo.read(reinterpret_cast<char*>(&idproducto), sizeof(int));
            productosSolicitados.push_back(idproducto);
        }

        // Mostrar los productos solicitados
        std::string productos = "";
        for (size_t i = 0; i < productosSolicitados.size(); i++) {
            productos += std::to_string(productosSolicitados[i]);
            if (i < productosSolicitados.size() - 1) {
                productos += ", ";
            }
        }

        // Mostrar la información de productos solicitados y cantidades
        std::cout << std::setw(20) << productos
                  << std::setw(15) << cantidadProductos
                  << "\n";

        std::cout << "---------------------------------------\n";
    }

    archivo.close();
    std::cout << "FIN DEL REPORTE\n";

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "Tiempo de lectura: " << duration.count() << " ms\n";
}