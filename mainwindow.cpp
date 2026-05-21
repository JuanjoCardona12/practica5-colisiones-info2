#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPen>
#include <QBrush>
#include <QGraphicsView>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    escena(new EscenaJuego(600, 500, this)),
    scene(new QGraphicsScene(0, 0, 600, 500, this))
{
    ui->setupUi(this);
    escena->inicializar();

    // Crear el QGraphicsView manualmente — sin depender del .ui
    QGraphicsView* view = new QGraphicsView(scene, this);
    view->setGeometry(10, 10, 620, 520);
    view->setRenderHint(QPainter::Antialiasing);
    view->setBackgroundBrush(QBrush(Qt::white));

    connect(&timer, &QTimer::timeout, this, &MainWindow::tick);
    timer.start(16);
}
MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::tick() {
    if (pausado) return;
    escena->paso(0.016);
    dibujarEstado();
    actualizarEstadisticas();
}

void MainWindow::dibujarEstado() {
    scene->clear();

    // Fondo blanco
    scene->setBackgroundBrush(Qt::white);

    // Borde de la caja
    scene->addRect(0, 0, 600, 500,
                   QPen(Qt::black, 2),
                   QBrush(Qt::NoBrush));

    // Dibujar obstáculos en gris
    for (const auto& obs : escena->getObstaculos()) {
        scene->addRect(obs.getBounds(),
                       QPen(Qt::darkGray, 2),
                       QBrush(Qt::lightGray));
    }

    // Dibujar partículas activas
    for (const auto& p : escena->getParticulas()) {
        if (!p.estaActiva()) continue;
        double r = p.getRadio();
        scene->addEllipse(
            p.getPosicion().x - r,
            p.getPosicion().y - r,
            2 * r, 2 * r,
            QPen(Qt::black, 1),
            QBrush(p.getColor())
            );
    }
}

void MainWindow::actualizarEstadisticas() {
    auto stats = escena->getEstadisticas();
    Q_UNUSED(stats);
}
