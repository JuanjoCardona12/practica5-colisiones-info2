#pragma once
#include <QObject>
#include <vector>
#include "particula.h"
#include "obstaculo.h"

class DetectorColisiones : public QObject {
    Q_OBJECT
public:
    DetectorColisiones(double anchoCaja, double altoCaja, QObject* parent = nullptr);

    // Verifica y resuelve colisiones de tipo A: pared
    void chequearParedes(Particula& p);

    // Verifica y resuelve colisiones de tipo B: obstáculo inelástico
    bool chequearObstaculo(Particula& p, const Obstaculo& obs);

    // Verifica y resuelve colisiones de tipo C: fusión entre partículas
    void chequearParticulas(std::vector<Particula>& particulas);

signals:
    void colisionDetectada(QString tipo, int id1, int id2, double tiempo);

private:
    double anchoCaja, altoCaja;
};
