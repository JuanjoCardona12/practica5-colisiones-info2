#ifndef ENTIDAD_H
#define ENTIDAD_H

#include "vector2d.h"

class Entidad {
public:
    Entidad(Vector2D pos, double masa, int id)
        : pos(pos), masa(masa), id(id) {}

    virtual ~Entidad() = default;
    virtual void actualizar(double dt) = 0;

    Vector2D getPosicion() const { return pos; }
    double   getMasa()     const { return masa; }
    int      getId()       const { return id;   }
    void     setPosicion(Vector2D p) { pos = p; }

protected:
    Vector2D pos;
    double   masa;
    int      id;
};

#endif // ENTIDAD_H
