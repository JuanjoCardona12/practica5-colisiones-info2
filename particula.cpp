
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
        vel.x =  std::abs(vel.x);   // forzar dirección derecha
        break;
    case LadoPared::DERECHA:
        vel.x = -std::abs(vel.x);   // forzar dirección izquierda
        break;
    case LadoPared::ARRIBA:
        vel.y =  std::abs(vel.y);   // forzar dirección abajo (y crece hacia abajo)
        break;
    case LadoPared::ABAJO:
        vel.y = -std::abs(vel.y);   // forzar dirección arriba
        break;
    }
}

void Particula::rebotarObstaculo(double e, LadoObst lado) {
    switch (lado) {
    case LadoObst::NORTE:
        vel.y = -e * std::abs(vel.y);   // rebota hacia arriba (v_y < 0)
        break;
    case LadoObst::SUR:
        vel.y =  e * std::abs(vel.y);   // rebota hacia abajo  (v_y > 0)
        break;
    case LadoObst::ESTE:
        vel.x =  e * std::abs(vel.x);   // rebota hacia la derecha (v_x > 0)
        break;
    case LadoObst::OESTE:
        vel.x = -e * std::abs(vel.x);   // rebota hacia la izquierda (v_x < 0)
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
