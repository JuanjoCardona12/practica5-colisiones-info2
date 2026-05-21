#include "escenajuego.h"

EscenaJuego::EscenaJuego(double ancho, double alto, QObject* parent)
    : QObject(parent),
    ancho(ancho), alto(alto),
    detector(ancho, alto, this),
    salida("simulacion.txt")
{
    connect(&detector, &DetectorColisiones::colisionDetectada,
            this, [this](QString tipo, int id1, int id2, double t) {
                Q_UNUSED(tipo); Q_UNUSED(id1); Q_UNUSED(id2); Q_UNUSED(t);
                numColisiones++;
                salida.registrarColision(tipo, id1, id2, tiempoTotal);
            });
}

void EscenaJuego::inicializar() {
    particulas.clear();
    obstaculos.clear();

    // 4 partículas con distintas masas, velocidades y colores
    particulas.emplace_back(1, Vector2D(80,  80),  Vector2D(150,  80),  2.0, 12, Qt::red);
    particulas.emplace_back(2, Vector2D(300, 200), Vector2D(-80,  120), 3.0, 15, Qt::blue);
    particulas.emplace_back(3, Vector2D(200, 350), Vector2D(100, -90),  1.5, 10, Qt::green);
    particulas.emplace_back(4, Vector2D(450, 150), Vector2D(-60, -70),  2.5, 13, Qt::yellow);

    // 2 obstáculos estáticos
    obstaculos.emplace_back(10, Vector2D(250, 250), 60, 60, 0.6);
    obstaculos.emplace_back(11, Vector2D(420, 360), 50, 80, 0.5);

    tiempoTotal   = 0.0;
    numColisiones = 0;
    salida.escribirCabecera();
}

void EscenaJuego::paso(double dt) {
    tiempoTotal += dt;

    // 1. Mover partículas
    for (auto& p : particulas)
        p.actualizar(dt);

    // 2. Colisiones con paredes (elástica)
    for (auto& p : particulas)
        if (p.estaActiva()) detector.chequearParedes(p);

    // 3. Colisiones con obstáculos (inelástica)
    for (auto& p : particulas)
        if (p.estaActiva())
            for (const auto& obs : obstaculos)
                detector.chequearObstaculo(p, obs);

    // 4. Colisiones entre partículas (completamente inelástica)
    detector.chequearParticulas(particulas);


    salida.escribirEstado(tiempoTotal, particulas);
}

Estadisticas EscenaJuego::getEstadisticas() const {
    double Etotal = 0.0;
    int    nAct   = 0;
    for (const auto& p : particulas) {
        if (p.estaActiva()) {
            Etotal += p.energiaCinetica();
            nAct++;
        }
    }
    return { Etotal, nAct, numColisiones };
}
