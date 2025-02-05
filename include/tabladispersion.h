#ifndef TABLA_DISPERSION_H
#define TABLA_DISPERSION_H

#include <vector>
#include <utility>

class tabladispersion {
private:
    static const int TABLE_SIZE = 10007;
    std::vector<std::pair<int, std::string>> tabla;
public:
    tabladispersion();

    void insertar(int clave, std::string valor);
    std::string buscar(int clave) const;
    void eliminar(int clave);
};

#endif
