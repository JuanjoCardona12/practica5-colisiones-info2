#include "obstaculo.h"
#include <cmath>
#include <algorithm>

Obstaculo::Obstaculo(int id, Vector2D pos, double ancho, double alto, double e)
    : Entidad(pos, 1e12, id), ancho(ancho), alto(alto), coefRest(e) {}

QRectF Obstaculo::getBounds() const {
    return QRectF(pos.x - ancho / 2, pos.y - alto / 2, ancho, alto);
}

bool Obstaculo::colisionaCon(Vector2D p, double radio) const {
    double cx = std::clamp(p.x, pos.x - ancho / 2, pos.x + ancho / 2);
    double cy = std::clamp(p.y, pos.y - alto  / 2, pos.y + alto  / 2);
    double dx = p.x - cx;
    double dy = p.y - cy;
    return (dx * dx + dy * dy) <= (radio * radio);
}

LadoObst Obstaculo::ladoImpacto(Vector2D p) const {
    // Distancia con signo positivo = partícula está fuera de ese lado.
    // Cuando está dentro (penetración), el valor menos negativo indica
    // el lado con menor profundidad de penetración → lado correcto.
    double dN = (pos.y - alto  / 2) - p.y;
    double dS = p.y - (pos.y + alto  / 2);
    double dE = p.x - (pos.x + ancho / 2);
    double dO = (pos.x - ancho / 2) - p.x;

    double maxD = std::max({dN, dS, dE, dO});
    if (maxD == dN) return LadoObst::NORTE;
    if (maxD == dS) return LadoObst::SUR;
    if (maxD == dE) return LadoObst::ESTE;
    return LadoObst::OESTE;
}
