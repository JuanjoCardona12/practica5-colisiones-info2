#ifndef OBSTACULO_H
#define OBSTACULO_H

#include "entidad.h"
#include "tipos.h"
#include <QRectF>

class Obstaculo : public Entidad {
public:
    Obstaculo(int id, Vector2D pos, double ancho, double alto,
              double coefRestitucion = 0.6);

    void actualizar(double dt) override {}

    bool     colisionaCon(Vector2D posParticula, double radio) const;
    LadoObst ladoImpacto(Vector2D posParticula) const;

    double getCoefRestitucion() const { return coefRest; }
    double getAncho()           const { return ancho;    }
    double getAlto()            const { return alto;     }
    QRectF getBounds()          const;

private:
    double ancho, alto;
    double coefRest;
};

#endif // OBSTACULO_H
