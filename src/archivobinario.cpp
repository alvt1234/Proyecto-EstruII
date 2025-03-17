#include "archivobinario.h"
#include <iomanip>  // Para setw()



std::string ArchivoBinario::comprimirDatos(const std::string& datos) {
    return huffman.compress(datos);
}

std::string ArchivoBinario::descomprimirDatos(const std::string& datosComprimidos) {
    return huffman.decompress(datosComprimidos, huffman.getCodes());
}

void ArchivoBinario::aggCliente(cliente c) {
    int id = c.getIdCliente();
    double saldo = c.getSaldo();
    
    // Comprimir los datos de texto
    std::string nombreComprimido = comprimirDatos(c.getNombre());
    std::string telefonoComprimido = comprimirDatos(c.getTelefono());
    std::string correoComprimido = comprimirDatos(c.getCorreo());
    std::string historialComprimido = comprimirDatos(c.gethistorialCompras());
    
    // Guardar también los códigos Huffman para poder descomprimir después
    auto huffmanCodes = huffman.getCodes();
    
    std::ofstream archivo("clientes.bin", std::ios::out | std::ios::binary | std::ios::app);
    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo de clientes para agregar datos.\n";
        return;
    }
    
    // Escribir los datos comprimidos
    archivo.write(reinterpret_cast<char*>(&id), sizeof(int));
    archivo.write(reinterpret_cast<char*>(&saldo), sizeof(double));
    
    // Escribir longitudes de los datos comprimidos
    int nombreLen = nombreComprimido.length();
    int telefonoLen = telefonoComprimido.length();
    int correoLen = correoComprimido.length();
    int historialLen = historialComprimido.length();
    
    archivo.write(reinterpret_cast<char*>(&nombreLen), sizeof(int));
    archivo.write(nombreComprimido.c_str(), nombreLen);
    
    archivo.write(reinterpret_cast<char*>(&telefonoLen), sizeof(int));
    archivo.write(telefonoComprimido.c_str(), telefonoLen);
    
    archivo.write(reinterpret_cast<char*>(&correoLen), sizeof(int));
    archivo.write(correoComprimido.c_str(), correoLen);
    
    archivo.write(reinterpret_cast<char*>(&historialLen), sizeof(int));
    archivo.write(historialComprimido.c_str(), historialLen);
    
    // Guardar también la tabla de códigos Huffman
    int codesSize = huffmanCodes.size();
    archivo.write(reinterpret_cast<char*>(&codesSize), sizeof(int));
    
    for (const auto& pair : huffmanCodes) {
        char c = pair.first;
        std::string code = pair.second;
        int codeLen = code.length();
        
        archivo.write(&c, sizeof(char));
        archivo.write(reinterpret_cast<char*>(&codeLen), sizeof(int));
        archivo.write(code.c_str(), codeLen);
    }
    
    archivo.close();
    std::cout << "Cliente guardado correctamente con compresión Huffman.\n";
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
    double saldo;

    while (archivo.read(reinterpret_cast<char*>(&idcliente), sizeof(int))) {
        archivo.read(reinterpret_cast<char*>(&saldo), sizeof(double));
        
        // Leer longitudes y datos comprimidos
        int nombreLen, telefonoLen, correoLen, historialLen;
        
        archivo.read(reinterpret_cast<char*>(&nombreLen), sizeof(int));
        std::string nombreComprimido(nombreLen, ' ');
        archivo.read(&nombreComprimido[0], nombreLen);
        
        archivo.read(reinterpret_cast<char*>(&telefonoLen), sizeof(int));
        std::string telefonoComprimido(telefonoLen, ' ');
        archivo.read(&telefonoComprimido[0], telefonoLen);
        
        archivo.read(reinterpret_cast<char*>(&correoLen), sizeof(int));
        std::string correoComprimido(correoLen, ' ');
        archivo.read(&correoComprimido[0], correoLen);
        
        archivo.read(reinterpret_cast<char*>(&historialLen), sizeof(int));
        std::string historialComprimido(historialLen, ' ');
        archivo.read(&historialComprimido[0], historialLen);
        
        // Leer la tabla de códigos Huffman
        int codesSize;
        archivo.read(reinterpret_cast<char*>(&codesSize), sizeof(int));
        
        std::unordered_map<char, std::string> huffmanCodes;
        for (int i = 0; i < codesSize; i++) {
            char c;
            int codeLen;
            
            archivo.read(&c, sizeof(char));
            archivo.read(reinterpret_cast<char*>(&codeLen), sizeof(int));
            
            std::string code(codeLen, ' ');
            archivo.read(&code[0], codeLen);
            
            huffmanCodes[c] = code;
        }
        
        // Descomprimir los datos
        std::string nombre = huffman.decompress(nombreComprimido, huffmanCodes);
        std::string telefono = huffman.decompress(telefonoComprimido, huffmanCodes);
        std::string correo = huffman.decompress(correoComprimido, huffmanCodes);
        std::string historial = huffman.decompress(historialComprimido, huffmanCodes);

        // Crear la información del cliente
        std::string info = "Nombre: " + nombre + ", Correo: " + correo +
                           ", Tel: " + telefono + ", Saldo: " + std::to_string(saldo) +
                           ", Historial: " + historial;

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
        std::cout << "Empleado cargado: Nombre: " << nombre << ", Departamento: " << departamento 
                  << ", puesto: " << puesto << ", salario: " << salario 
                  << ", Estado: " << estado << std::endl;

        std::string info = "Nombre: " + std::string(nombre) + ", Departamento: " + std::string(departamento) +
                           ", Puesto: " + std::string(puesto) + ", Salario: " + std::to_string(salario) +
                           ", Estado: " + std::string(estado);

        // Insertamos el cliente en la tabla de dispersión
        empleado.insertar(idempleado);
    }

    archivo.close();
}

void ArchivoBinario::reportesClientes(){
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
}

void ArchivoBinario::reportesEmpleados(){
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
}

void ArchivoBinario::reportesProductos(){

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
    
}

void ArchivoBinario::reportesVentas() {
    std::ifstream archivo("ventas.bin", std::ios::in | std::ios::binary);
    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo de ventas para generar el reporte.\n";
        return;
    }

    int idventa, idcliente, idproducto, cantidad, cantidadProductos;
    double precio, subtotal, total;
    char fecha[50];

    std::cout << "--------REPORTE DE LAS VENTAS--------\n";
    std::cout << std::left << std::setw(10) << "ID Venta"
              << std::setw(15) << "ID Cliente"
              << std::setw(10) << "Total"
              << std::setw(15) << "Fecha"
              << std::setw(15) << "ID Producto"
              << std::setw(10) << "Cantidad"
              << std::setw(10) << "Precio"
              << std::setw(10) << "Subtotal"
              << "\n";
    std::cout << "--------------------------------------------------\n";

    while (archivo.read(reinterpret_cast<char*>(&idventa), sizeof(int))) {
        archivo.read(reinterpret_cast<char*>(&idcliente), sizeof(int));
        archivo.read(reinterpret_cast<char*>(&total), sizeof(double));
        archivo.read(fecha, sizeof(fecha));

        archivo.read(reinterpret_cast<char*>(&cantidadProductos), sizeof(int));

        std::cout << std::left << std::setw(10) << idventa
                  << std::setw(15) << idcliente
                  << std::setw(10) << total
                  << std::setw(15) << fecha
                  << "\n";

        for (int i = 0; i < cantidadProductos; i++) {
            archivo.read(reinterpret_cast<char*>(&idproducto), sizeof(int));
            archivo.read(reinterpret_cast<char*>(&cantidad), sizeof(int));
            archivo.read(reinterpret_cast<char*>(&precio), sizeof(double));
            archivo.read(reinterpret_cast<char*>(&subtotal), sizeof(double));

            std::cout << std::setw(40) << " "  // Espacio para alinear con la primera línea
                      << std::setw(15) << idproducto
                      << std::setw(10) << cantidad
                      << std::setw(10) << precio
                      << std::setw(10) << subtotal
                      << "\n";
        }

        std::cout << "--------------------------------------------------\n";
    }

    archivo.close();
    std::cout << "FIN DEL REPORTE\n";
}

    