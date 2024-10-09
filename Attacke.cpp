/************
Autor:      Tony Lenter

Projekt:    MiniMonster
            Ein Spiel in dem 2 Spieler verschiedene Monster gegeneinander antreten lassen können

Klasse:     Attacke
            Implementiert eine mögliche Art für einen Angriff

Datum:      15.07.2024
*************/

#include "Attacke.h"

#include <string>
#include "iostream"

using namespace std;

Attacke::Attacke(const string& a, const string& t, const int& s, const int& p)
    :name(a), typ(t), schaden(s), ap(p), ap_max(p)
{

    //ctor
}

Attacke::~Attacke()
{
    cout<<"~Attacke "<<name<<endl;
    //dtor
}

/*
 * AP verringern
 *
*/
void Attacke::ausfuehren(){
    ap--;
}

/*
 * AP auf max. Wert setzen
 *
*/
void Attacke::set_ap(){
    ap=ap_max;
}


/*
 * Name der Attacke zurückgeben
 * @return: Name der Attacke
*/
string Attacke::get_name() const{
    return name;
}

/*
 * Typ der Attacke zurückgeben
 * @return: Typ der Attacke
*/
string Attacke::get_typ() const{
    return typ;
}

/*
 * Schaden der Attacke zurückgeben
 * @return: Schaden der Attacke
*/
int Attacke::get_schaden() const{
    return schaden;
}

/*
 * AP der Attacke zurückgeben
 * @return: AP der Attacke
*/
int Attacke::get_ap() const{
    return ap;
}













