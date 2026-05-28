#include "detectorcolisiones.h"

DetectorColisiones::DetectorColisiones(double w, double h, QObject* parent)
    : QObject(parent), anchoCaja(w), altoCaja(h) {}

void DetectorColisiones::chequearParedes(Particula& p) {
    Vector2D pos = p.getPosicion();
    double   r   = p.getRadio();

    if (pos.x - r < 0) {
        p.setPosicion({r, pos.y});
        p.rebotarPared(LadoPared::IZQUIERDA);
        emit colisionDetectada("PARED_IZQ", p.getId(), -1, 0);
    } else if (pos.x + r > anchoCaja) {
        p.setPosicion({anchoCaja - r, pos.y});
        p.rebotarPared(LadoPared::DERECHA);
        emit colisionDetectada("PARED_DER", p.getId(), -1, 0);
    }

    pos = p.getPosicion();
    if (pos.y - r < 0) {
        p.setPosicion({pos.x, r});
        p.rebotarPared(LadoPared::ARRIBA);
        emit colisionDetectada("PARED_ARR", p.getId(), -1, 0);
    } else if (pos.y + r > altoCaja) {
        p.setPosicion({pos.x, altoCaja - r});
        p.rebotarPared(LadoPared::ABAJO);
        emit colisionDetectada("PARED_ABA", p.getId(), -1, 0);
    }
}

bool DetectorColisiones::chequearObstaculo(Particula& p, const Obstaculo& obs) {
    if (!obs.colisionaCon(p.getPosicion(), p.getRadio())) return false;

    LadoObst lado = obs.ladoImpacto(p.getPosicion());
    p.rebotarObstaculo(obs.getCoefRestitucion(), lado);

    Vector2D pos = p.getPosicion();
    double   r   = p.getRadio();
    double   ox  = obs.getPosicion().x;
    double   oy  = obs.getPosicion().y;

    switch (lado) {
    case LadoObst::NORTE: p.setPosicion({pos.x, oy - obs.getAlto()  / 2 - r - 1}); break;
    case LadoObst::SUR:   p.setPosicion({pos.x, oy + obs.getAlto()  / 2 + r + 1}); break;
    case LadoObst::ESTE:  p.setPosicion({ox + obs.getAncho() / 2 + r + 1, pos.y}); break;
    case LadoObst::OESTE: p.setPosicion({ox - obs.getAncho() / 2 - r - 1, pos.y}); break;
    }

    emit colisionDetectada("OBSTACULO", p.getId(), obs.getId(), 0);
    return true;
}

void DetectorColisiones::chequearParticulas(std::vector<Particula>& ps) {
    for (size_t i = 0; i < ps.size(); ++i) {
        if (!ps[i].estaActiva()) continue;
        for (size_t j = i + 1; j < ps.size(); ++j) {
            if (!ps[j].estaActiva()) continue;

            Vector2D delta = ps[i].getPosicion() - ps[j].getPosicion();
            double distMin = ps[i].getRadio() + ps[j].getRadio();

            if (delta.magnitudCuad() <= distMin * distMin) {
                if (ps[i].getMasa() >= ps[j].getMasa())
                    ps[i].fusionar(ps[j]);
                else
                    ps[j].fusionar(ps[i]);

                emit colisionDetectada("FUSION",
                                       ps[i].getId(), ps[j].getId(), 0);

                if (!ps[i].estaActiva()) break; // ps[i] fue absorbida, salir del loop interno
            }
        }
    }
}
