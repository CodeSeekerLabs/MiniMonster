/************
Autor:      Tony Lenter

Projekt:    MiniMonster
            Ein Spiel in dem 2 Spieler verschiedene Monster gegeneinander antreten lassen können

Klasse:     Player (Header)
            Legt das Verhalten und die Eigenschaften eines Spielers fest

Datum:      15.07.2024
*************/

#ifndef PLAYER_H
#define PLAYER_H

#include "Monster.h"



class Player
{
public:
    Player(const string& n);
    Player();
    ~Player();

    void set_monster1(Monster *mon);
    void set_monster2(Monster *mon);
    void set_monster3(Monster *mon);

    void serialize(const string& s) const;
    void deserialize(const string& s);

    void del_monster1();
    void del_monster2();
    void del_monster3();


    Monster* get_monster(const int& i) const;
    string get_name() const;
    int get_Anzahl() const;
    int get_AnzahlAktiverMonster() const;





private:
    string name; //Name des Spielers
    Monster *m[3];// Monster des Spielers
    int anzahlMonster;// Anzahl der Monster des Spielers
};

#endif // PLAYER_H
