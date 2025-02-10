#include "../include/archivobinario.h"

archivobinario::archivobinario(const string &nombre) : nombreArchivo(nombre), hFile(INVALID_HANDLE_VALUE)
{
    hFile = CreateFileA(nombre.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    
    if (hFile == INVALID_HANDLE_VALUE) {
        DWORD error_code = GetLastError();
        std::cout << "Error al abrir el archivo " << nombre << ". Código de error: " << error_code << std::endl;
    } else {
        std::cout << "Archivo " << nombre << " abierto correctamente." << std::endl;
    }
}
void archivobinario::aggcliente(int idcliente, string cliente, string telefono, string correo, double saldo, string historialcompras)
{
    if (hFile == INVALID_HANDLE_VALUE) {
        std::cerr << "El archivo no está abierto correctamente." << std::endl;
        return;
    }

    LARGE_INTEGER fileSize;
    if (!GetFileSizeEx(hFile, &fileSize)) {
        DWORD error_code = GetLastError();
        std::cerr << "Error al obtener el tamaño del archivo. Código de error: " << error_code << std::endl;
        return;
    }

    SetFilePointer(hFile, fileSize.QuadPart, NULL, FILE_BEGIN); 

    std::string datos = "ID: " + std::to_string(idcliente) + ", Cliente: " + cliente
        + ", Telefono: " + telefono + ", Correo: " + correo
        + ", Saldo: " + std::to_string(saldo) + ", Historial: " + historialcompras + "\n";

    DWORD bytesEscritos;
    BOOL resultado = WriteFile(hFile, datos.c_str(), datos.size(), &bytesEscritos, NULL);

    if (resultado) {
        std::cout << "Datos escritos correctamente en el archivo." << std::endl;
        std::cout << "Bytes escritos: " << bytesEscritos << std::endl;
    } else {
        DWORD error_code = GetLastError();
        std::cerr << "Error al escribir en el archivo. Código de error: " << error_code << std::endl;
        std::cerr << "Descripción del error: " << strerror(error_code) << std::endl;
    }
}

archivobinario::~archivobinario()
{
    if (hFile != INVALID_HANDLE_VALUE) {
        CloseHandle(hFile);
        std::cout << "Archivo " << nombreArchivo << " cerrado correctamente." << std::endl;
    }
}
