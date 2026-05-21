#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsScene>
#include <QPainter>
#include "escenajuego.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void tick();

private:
    Ui::MainWindow*  ui;
    EscenaJuego*     escena  = nullptr;
    QTimer           timer;
    QGraphicsScene*  scene   = nullptr;
    bool             pausado = false;

    void dibujarEstado();
    void actualizarEstadisticas();
};

#endif // MAINWINDOW_H
