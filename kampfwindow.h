/************
Autor:      Tony Lenter

Projekt:    MiniMonster
            Ein Spiel in dem 2 Spieler verschiedene Monster gegeneinander antreten lassen können

Klasse:     KampfWindow (Header)
            Erstellt das Kampffenster in welchem die Spieler ihre Monster gegeneinander antreten lassen

Datum:      15.07.2024
*************/

#ifndef KAMPFWINDOW_H
#define KAMPFWINDOW_H

#include <QDialog>

#include "player.h"
#include "Monster.h"

namespace Ui {
class KampfWindow;
}

class KampfWindow : public QDialog
{
    Q_OBJECT

public:
    explicit KampfWindow(QWidget *parent = nullptr, Player *player1=nullptr, Player *player2=nullptr);
    ~KampfWindow();

private slots:

    void btnStart();

    void btn1Att1();

    void btn1Att2();

    void btn2Att1();

    void btn2Att2();

    void btn1Auswahl2();

    void btn1Auswahl3();

    void btn2Auswahl2();

    void btn2Auswahl3();

private:
    Ui::KampfWindow *ui;
    Player *p1;
    Player *p2;

    int anzahlMonsterP1;//TODO: kann wieder weg
    int anzahlMonsterP2;//TODO: kann wieder weg

    int anzahlKampfMonsterP1;//TODO: kann wieder weg
    int anzahlKampfMonsterP2;//TODO: kann wieder weg

    int monsterAuswahlP1;
    int monsterAuswahlP2;


    void anzeigenP1();
    void anzeigenP2();

    void hideKampfPlayer1();
    void hideKampfPlayer2();
    void hideAttPlayer1();
    void hideAttPlayer2();

    void showKampfPlayer1(Monster *m);
    void showKampfPlayer2(Monster *m);
    void showAttPlayer1(Monster *m);
    void showAttPlayer2(Monster *m);

    void kampfBeginn();
    void konfetti();

};

#endif // KAMPFWINDOW_H
