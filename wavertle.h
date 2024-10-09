/************
Autor:      Tony Lenter

Projekt:    MiniMonster
            Ein Spiel in dem 2 Spieler verschiedene Monster gegeneinander antreten lassen können

Klasse:     Wavertle (Header)
            Legt die Eigenschaften und das Verhalten des Monsters Wavertle fest

Datum:      15.07.2024
*************/

#ifndef WAVERTLE_H
#define WAVERTLE_H

#include "Monster.h"
#include <string>
#include <tuple>

using namespace std;

class Wavertle:public Monster
{
public:
    Wavertle(const string&);
    Wavertle(const string&, const int&, const int&, const int&, const int&, const int&, const bool&, const int&, const int&, const int&, const int&, const int&);
    Wavertle();
    ~Wavertle();

    string statistik() const;

    tuple<int,string> angreifen(const int&) const;
    int wird_angegriffen(const tuple<int,string>&);
    void leveln(const int&);
    void heilen();


    string get_name() const;
    int get_level() const;
    int get_hp() const;
    int get_hpMax() const;
    int get_ep() const;
    int get_epMax() const;
    bool ist_kampfbereit() const;

    Attacke* get_Attacke1() const;
    Attacke* get_Attacke2() const;

    int get_angriff() const;
    int get_verteidigung() const;
    int get_initiative() const;

protected:

private:
};


#endif // WAVERTLE_H
