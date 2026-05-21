
#include "particula.h"
#include <cmath>

Particula::Particula(int id, Vector2D pos, Vector2D vel,
                     double masa, double radio, QColor color)
    : Entidad(pos, masa, id), vel(vel), radio(radio), color(color) {}

void Particula::actualizar(double dt) {
    if (!activa) return;
    pos += vel * dt;
}

void Particula::rebotarPared(LadoPared lado) {
    switch (lado) {
    case LadoPared::IZQUIERDA:
    case LadoPared::DERECHA:
        vel.x = -vel.x;
        break;
    case LadoPared::ARRIBA:
    case LadoPared::ABAJO:
        vel.y = -vel.y;
        break;
    }
}

void Particula::rebotarObstaculo(double e, LadoObst lado) {
    switch (lado) {
    case LadoObst::NORTE:
    case LadoObst::SUR:
        vel.y = -e * vel.y;
        break;
    case LadoObst::ESTE:
    case LadoObst::OESTE:
        vel.x = -e * vel.x;
        break;
    }
}

void Particula::fusionar(Particula& otra) {
    double masaTotal = masa + otra.masa;
    Vector2D momento = vel * masa + otra.getVelocidad() * otra.getMasa();
    vel   = momento / masaTotal;
    pos   = (pos * masa + otra.getPosicion() * otra.getMasa()) / masaTotal;
    radio = std::sqrt(radio * radio + otra.getRadio() * otra.getRadio());
    masa  = masaTotal;
    otra.activa = false;
}

double Particula::energiaCinetica() const {
    return 0.5 * masa * vel.magnitudCuad();
}
