/************
Autor:      Tony Lenter

Projekt:    MiniMonster
            Ein Spiel in dem 2 Spieler verschiedene Monster gegeneinander antreten lassen können

Klasse:     (Abstrakt) Monster
            Legt die Eigenschaften und Verhaltensweisen für die einzelnen Monster fest

Datum:      15.07.2024
*************/

#include "Monster.h"

#include <iostream>

using namespace std;



Monster::Monster()
{
    //ctor
}

Monster::~Monster()
{
    cout<<"~Monster "<<name<<endl;
    //dtor
}
