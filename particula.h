#ifndef PARTICULA_H
#define PARTICULA_H

#include "entidad.h"
#include "tipos.h"
#include <QColor>

class Particula : public Entidad {
public:
    Particula(int id, Vector2D pos, Vector2D vel,
              double masa, double radio, QColor color);

    void actualizar(double dt) override;

    void rebotarPared(LadoPared lado);
    void rebotarObstaculo(double e, LadoObst lado);
    void fusionar(Particula& otra);

    double   energiaCinetica() const;
    bool     estaActiva()      const { return activa; }
    double   getRadio()        const { return radio;  }
    QColor   getColor()        const { return color;  }
    Vector2D getVelocidad()    const { return vel;    }
    void     setVelocidad(Vector2D v) { vel = v;      }

private:
    Vector2D vel;
    double   radio;
    QColor   color;
    bool     activa = true;
};

#endif // PARTICULA_H
