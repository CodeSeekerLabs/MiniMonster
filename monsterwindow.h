/************
Autor:      Tony Lenter

Projekt:    MiniMonster
            Ein Spiel in dem 2 Spieler verschiedene Monster gegeneinander antreten lassen können

Klasse:     MonsterWindow (Header)
            Erstellt ein Fenster in welchem ein Spieler die Monster auswählen kann, die er in den Kampf schicken möchte

Datum:      15.07.2024
*************/

#ifndef MONSTERWINDOW_H
#define MONSTERWINDOW_H

#include <QDialog>

#include "player.h"

namespace Ui {
class MonsterWindow;
}

class MonsterWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MonsterWindow(QWidget *parent = nullptr, Player *p=nullptr);
    ~MonsterWindow();

private slots:

    void reject();


    void btnOkAbbr_accepted();

    void btnOkAbbr_rejected();

    void btnWavertle();
    void btnFloradon();
    void btnPyrozard();
    void btnMoorgeck();
    void btnTropizard();
    void btnFlammfeder();

    void btnDelMon1();

    void btnDelMon2();

    void btnDelMon3();

private:
    Ui::MonsterWindow *ui;
    Player *player;

    void hinzu(Monster *m);
};

#endif // MONSTERWINDOW_H
