#include "archivobinario.h"

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

        // Verifica si los datos fueron leídos correctamente
        std::cout << "Cliente cargado: Nombre: " << nombre << ", Correo: " << correo 
                  << ", Tel: " << telefono << ", Saldo: " << saldo 
                  << ", Historial: " << historial << std::endl;

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
    int idproducto=p.getid(),cantidad;
    char nombre[50], categoria[50], estado[100];
    double precio;

    strncpy(nombre, p.getnombre().c_str(), sizeof(nombre) - 1);
    nombre[sizeof(nombre) - 1] = '\0';  // Aseguramos el terminador nulo
    strncpy(categoria, p.getcategoria().c_str(), sizeof(categoria) - 1);
    categoria[sizeof(categoria) - 1] = '\0'; 
    strncpy(estado, p.getestado().c_str(), sizeof(estado) - 1);
    estado[sizeof(estado) - 1] = '\0'; 
    
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
     archivo.write(estado, sizeof(estado));
 
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
            archivo.read(estado, sizeof(estado));
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

void ArchivoBinario::aggEmpleado(empleado e)
{
    int id = e.getid();
    char nombre[50], departamento[50], estado[50], puesto[50];
    double sueldo;

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
