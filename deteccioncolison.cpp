#include "detectorcolisiones.h"

DetectorColisiones::DetectorColisiones(double w, double h, QObject* parent)
    : QObject(parent), anchoCaja(w), altoCaja(h) {}

// ── A) Colisiones elásticas con paredes ─────────────────────────────────────
void DetectorColisiones::chequearParedes(Particula& p) {
    Vector2D pos = p.getPosicion();
    double   r   = p.getRadio();

    if (pos.x - r < 0) {
        p.setPosicion({r, pos.y});          // Evitar que quede atrapada
        p.rebotarPared(LadoPared::IZQUIERDA);
        emit colisionDetectada("PARED_IZQ", p.getId(), -1, 0);
    }
    else if (pos.x + r > anchoCaja) {
        p.setPosicion({anchoCaja - r, pos.y});
        p.rebotarPared(LadoPared::DERECHA);
        emit colisionDetectada("PARED_DER", p.getId(), -1, 0);
    }

    pos = p.getPosicion(); // Recalcular tras posible ajuste horizontal
    if (pos.y - r < 0) {
        p.setPosicion({pos.x, r});
        p.rebotarPared(LadoPared::ARRIBA);
        emit colisionDetectada("PARED_ARR", p.getId(), -1, 0);
    }
    else if (pos.y + r > altoCaja) {
        p.setPosicion({pos.x, altoCaja - r});
        p.rebotarPared(LadoPared::ABAJO);
        emit colisionDetectada("PARED_ABA", p.getId(), -1, 0);
    }
}

// ── B) Colisiones inelásticas con obstáculos ────────────────────────────────
bool DetectorColisiones::chequearObstaculo(Particula& p, const Obstaculo& obs) {
    if (!obs.colisionaCon(p.getPosicion(), p.getRadio())) return false;

    LadoObst lado = obs.ladoImpacto(p.getPosicion());
    p.rebotarObstaculo(obs.getCoefRestitución(), lado);

    // Separar la partícula del obstáculo para evitar penetración continua
    Vector2D pos = p.getPosicion();
    double   r   = p.getRadio();
    switch (lado) {
    case LadoObst::NORTE: pos.y = obs.getPosicion().y - obs.getAlto()/2 - r - 1; break;
    case LadoObst::SUR:   pos.y = obs.getPosicion().y + obs.getAlto()/2 + r + 1; break;
    case LadoObst::ESTE:  pos.x = obs.getPosicion().x + obs.getAncho()/2 + r + 1; break;
    case LadoObst::OESTE: pos.x = obs.getPosicion().x - obs.getAncho()/2 - r - 1; break;
    }
    p.setPosicion(pos);

    emit colisionDetectada("OBSTACULO", p.getId(), obs.getId(), 0);
    return true;
}

// ── C) Colisiones completamente inelásticas entre partículas ─────────────────
void DetectorColisiones::chequearParticulas(std::vector<Particula>& ps) {
    for (size_t i = 0; i < ps.size(); ++i) {
        if (!ps[i].estaActiva()) continue;
        for (size_t j = i + 1; j < ps.size(); ++j) {
            if (!ps[j].estaActiva()) continue;

            // Distancia entre centros
            Vector2D delta = ps[i].getPosicion() - ps[j].getPosicion();
            double distMin = ps[i].getRadio() + ps[j].getRadio();

            if (delta.magnitudCuad() <= distMin * distMin) {
                // Fusión: la de mayor masa absorbe a la menor
                if (ps[i].getMasa() >= ps[j].getMasa())
                    ps[i].fusionar(ps[j]);
                else
                    ps[j].fusionar(ps[i]);

                emit colisionDetectada("FUSION", ps[i].getId(), ps[j].getId(), 0);
            }
        }
    }
}
