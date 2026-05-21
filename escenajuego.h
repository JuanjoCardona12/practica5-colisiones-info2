#ifndef ESCENAJUEGO_H
#define ESCENAJUEGO_H

#include <QObject>
#include <vector>
#include "particula.h"
#include "obstaculo.h"
#include "detectorcolisiones.h"
#include "archivoSalida.h"

struct Estadisticas {
    double energiaTotal;
    int    numParticulas;
    int    colisiones;
};

class EscenaJuego : public QObject {
    Q_OBJECT
public:
    explicit EscenaJuego(double ancho, double alto,
                         QObject* parent = nullptr);

    void inicializar();
    void paso(double dt);
    Estadisticas getEstadisticas() const;

    const std::vector<Particula>& getParticulas() const { return particulas; }
    const std::vector<Obstaculo>& getObstaculos() const { return obstaculos; }

private:
    double ancho, alto;
    double tiempoTotal   = 0.0;
    int    numColisiones = 0;

    std::vector<Particula>  particulas;
    std::vector<Obstaculo>  obstaculos;
    DetectorColisiones      detector;
    ArchivoSalida           salida;
};

#endif // ESCENAJUEGO_H
