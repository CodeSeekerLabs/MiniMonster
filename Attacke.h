/************
Autor:      Tony Lenter

Projekt:    MiniMonster
            Ein Spiel in dem 2 Spieler verschiedene Monster gegeneinander antreten lassen können

Klasse:     Attacke
            Legt eine mögliche Art für einen Angriff fest

Datum:      15.07.2024
*************/

#ifndef ATTACKE_H
#define ATTACKE_H

#include <string>

using namespace std;

class Attacke
{
public:
    Attacke(const string&, const string&, const int&, const int&);
    ~Attacke();

    void ausfuehren();
    void set_ap();

    string get_name() const;
    string get_typ() const;
    int get_schaden() const;
    int get_ap() const;

private:
    string name;//Name der Attacke
    string typ;//Typ der Attacke

    int schaden;//Wie viel Schaden die Attacke macht
    int ap;//Wie oft die Attacke noch ausgeführt werden kann
    int ap_max;//Wie oft die Attacke maximal ausgeführt werden kann

};

#endif // ATTACKE_H
