#include <windows.h>
#include <iostream>
#include <string>
using namespace std;

class archivobinario
{
private:
HANDLE hFile;
string nombreArchivo;
public:
    
    archivobinario(const string& nombre);
    void aggcliente(int idcliente,string cliente,string telefono,string correo,double saldo,string historialcompras);
    ~archivobinario();
};
