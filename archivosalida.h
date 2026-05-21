#ifndef ARCHIVOSALIDA_H
#define ARCHIVOSALIDA_H

#include <QFile>
#include <QTextStream>
#include <QString>
#include <vector>
#include "particula.h"

class ArchivoSalida {
public:
    ArchivoSalida(const QString& ruta);
    ~ArchivoSalida();

    void escribirCabecera();
    void escribirEstado(double t, const std::vector<Particula>& ps);
    void registrarColision(const QString& tipo, int id1, int id2, double t);

private:
    QFile       archivo;
    QTextStream stream;
};

#endif // ARCHIVOSALIDA_H
