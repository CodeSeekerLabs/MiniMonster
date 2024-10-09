/************
Autor:      Tony Lenter

Projekt:    MiniMonster
            Ein Spiel in dem 2 Spieler verschiedene Monster gegeneinander antreten lassen können

Klasse:     (Abstrakt) Monster (Header)
            Legt die Eigenschaften und Verhaltensweisen für die einzelnen Monster fest

Datum:      15.07.2024
*************/

#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include "Attacke.h"
#include <tuple>

using namespace std;


class Monster
{
public:

    Monster();
    virtual ~Monster();

    virtual string statistik() const =0;
    virtual tuple<int,string> angreifen(const int&) const =0;
    virtual int wird_angegriffen(const tuple<int,string>&) =0;
    virtual void leveln(const int&)=0;
    virtual void heilen()=0;

    virtual string get_name() const =0;
    virtual int get_level() const =0;
    virtual int get_hp() const =0;
    virtual int get_hpMax() const =0;
    virtual int get_ep() const =0;
    virtual int get_epMax() const =0;
    virtual bool ist_kampfbereit() const =0;

    virtual Attacke* get_Attacke1() const =0;
    virtual Attacke* get_Attacke2() const =0;

    virtual int get_angriff() const =0;
    virtual int get_verteidigung() const =0;
    virtual int get_initiative() const =0;

protected:
    string name; //Name des MOnsters
    string typ; //Typ des Monsters

    int level; //Level des Monsters
    int hp; //Wie viel Healthpoints das monster noch hat
    int hp_max; //Wie viel Healthpoints das Monster maximal haben kann
    int ep; //Erfahrungspunkte des Monsters
    int ep_max;//Wie viel ep benötigt werden für ein Levelaufstieg
    int angriff;//Angriffspunkte
    int verteidigung;//verteidigungspunkte
    int initiative;//Initiative des Monster

    bool kampfbereit;//Ob das Monster Kampfbereit ist

    Attacke *attacke[2];// Attacken des Monsters

private:
};

#endif // MONSTER_H
