#ifndef TABLA_DISPERSION_H
#define TABLA_DISPERSION_H
#include <string>  
#include <vector>
#include <utility>
#include <list>

class tabladispersion {
private:
    static const int TABLE_SIZE = 10007;
    std::vector<std::list<std::pair<int, std::string>>> tabla; 

    
    int hashFuncion(int clave) const;
public:
    tabladispersion();

    void insertar(int clave, const std::string& valor);
    std::string buscar(int clave) const;
    void eliminar(int clave);
};

#endif
