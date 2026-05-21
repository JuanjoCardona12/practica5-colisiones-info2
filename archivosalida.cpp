#include "archivoSalida.h"

ArchivoSalida::ArchivoSalida(const QString& ruta) : archivo(ruta) {
    archivo.open(QIODevice::WriteOnly | QIODevice::Text);
    stream.setDevice(&archivo);
}

ArchivoSalida::~ArchivoSalida() {
    if (archivo.isOpen()) archivo.close();
}

void ArchivoSalida::escribirCabecera() {
    stream << "# SIMULACION DE COLISIONES - Informatica II\n";
    stream << "# tiempo id px py vx vy masa radio Ek\n";
    stream << "# Colisiones marcadas con [COL]\n\n";
    stream.flush();
}

void ArchivoSalida::escribirEstado(double t,
                                   const std::vector<Particula>& ps) {
    for (const auto& p : ps) {
        if (!p.estaActiva()) continue;
        stream << QString::number(t, 'f', 4)            << " "
               << p.getId()                              << " "
               << QString::number(p.getPosicion().x,'f',2) << " "
               << QString::number(p.getPosicion().y,'f',2) << " "
               << QString::number(p.getVelocidad().x,'f',2) << " "
               << QString::number(p.getVelocidad().y,'f',2) << " "
               << p.getMasa()                            << " "
               << p.getRadio()                           << " "
               << QString::number(p.energiaCinetica(),'f',3) << "\n";
    }
    stream.flush();
}

void ArchivoSalida::registrarColision(const QString& tipo,
                                      int id1, int id2, double t) {
    stream << "[COL] t=" << QString::number(t, 'f', 4)
    << " tipo="   << tipo
    << " id1="    << id1
    << " id2="    << id2 << "\n";
    stream.flush();
}
