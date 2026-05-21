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
    double dN = std::abs(p.y - (pos.y - alto  / 2));
    double dS = std::abs(p.y - (pos.y + alto  / 2));
    double dE = std::abs(p.x - (pos.x + ancho / 2));
    double dO = std::abs(p.x - (pos.x - ancho / 2));

    double minD = std::min({dN, dS, dE, dO});
    if (minD == dN) return LadoObst::NORTE;
    if (minD == dS) return LadoObst::SUR;
    if (minD == dE) return LadoObst::ESTE;
    return LadoObst::OESTE;
}
