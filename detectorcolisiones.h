#ifndef DETECTORCOLISIONES_H
#define DETECTORCOLISIONES_H

#include <QObject>
#include <vector>
#include "particula.h"
#include "obstaculo.h"

class DetectorColisiones : public QObject {
    Q_OBJECT
public:
    DetectorColisiones(double anchoCaja, double altoCaja,
                       QObject* parent = nullptr);

    void chequearParedes(Particula& p);
    bool chequearObstaculo(Particula& p, const Obstaculo& obs);
    void chequearParticulas(std::vector<Particula>& particulas);

signals:
    void colisionDetectada(QString tipo, int id1, int id2, double tiempo);

private:
    double anchoCaja;
    double altoCaja;
};

#endif // DETECTORCOLISIONES_H
