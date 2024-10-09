/************
Autor:      Tony Lenter

Projekt:    MiniMonster
            Ein Spiel in dem 2 Spieler verschiedene Monster gegeneinander antreten lassen können

Klasse:     MainWindow (Header)
            Erstellt das Startfenster zur Verwaltung des Spiels

Datum:      15.07.2024
*************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "player.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool namenTest(QString s);

private slots:

    void btnSpieler1();

    void btnSpieler2();

    void btnHeilen1();

    void btnHeilen2();

    void btnSpieler1speichern();

    void btnSpieler1laden();

    void btnSpieler2speichern();

    void btnSpieler2laden();

    void btnKampf();

private:
    Ui::MainWindow *ui;

    Player *p1;

    Player *p2;

    void anzeigenP1();
    void anzeigenP2();




};
#endif // MAINWINDOW_H
