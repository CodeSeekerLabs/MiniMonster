/************
Autor:      Tony Lenter

Projekt:    MiniMonster
            Ein Spiel in dem 2 Spieler verschiedene Monster gegeneinander antreten lassen können

Klasse:     Tropizard
            Implementiert die Eigenschaften und das Verhalten des Monsters Tropizard

Datum:      15.07.2024
*************/

#include "tropizard.h"

#include <string>
#include <tuple>
#include <iostream>

using namespace std;



Tropizard::Tropizard(const string& n)
{
    name=n;
    typ="Pflanze";
    level=3;
    hp=level*50;
    hp_max=level*50;
    ep=0;
    ep_max=1000;
    angriff=50;
    verteidigung=25;
    initiative=35;
    kampfbereit=true;

    attacke[0]=new Attacke("Sturmlauf","Normal",40,35);
    attacke[1]=new Attacke("Lianenhieb","Pflanze",40,25);


}


Tropizard::Tropizard(const string& n, const int& l, const int& h, const int& hm, const int& e, const int& em, const bool& k, const int& angr, const int& vert, const int& init, const int& ap1, const int& ap2 )
{
    name=n;
    typ="Pflanze";
    level=l;
    hp=h;
    hp_max=hm;
    ep=e;
    ep_max=em;
    angriff=angr;
    verteidigung=vert;
    initiative=init;
    kampfbereit=k;

    attacke[0]=new Attacke("Sturmlauf","Normal",40,ap1);//Attacken sind immer gleich AP sind variabel
    attacke[1]=new Attacke("Lianenhieb","Pflanze",40,ap2);


}

Tropizard::Tropizard(){
    name="default";
    //cout<<"Defautl Konst"<<endl;
}


Tropizard::~Tropizard()
{
    cout<<"~Tropizard "<<name<<endl;
    delete attacke[0];
    delete attacke[1];

    //dtor
}


/*
 * Werte von Tropizard als string zurückgeben
 * @return: Werte des Tropizard als string
*/
string Tropizard::statistik() const{
    string s="";

    s="Tropizard\n"+name+
        "\n"+to_string(level)+
        "\n"+to_string(hp)+
        "\n"+to_string(hp_max)+
        "\n"+to_string(ep)+
        "\n"+to_string(ep_max)+
        "\n"+to_string(kampfbereit)+
        "\n"+to_string(angriff)+
        "\n"+to_string(verteidigung)+
        "\n"+to_string(initiative)+
        "\n"+
        to_string(attacke[0]->get_ap())+"\n"+
        to_string(attacke[1]->get_ap())+"\n";
    return s;
}
/*
 * Angriff ausführen
 * @param i: ausgwählte Attacke 0 oder 1
 * @return: ein Angriff mit (Schadenspunkte, Attacken Typ)
*/
tuple<int,string> Tropizard::angreifen(const int& i) const{

    typedef tuple<int,string> ang;

    if(!kampfbereit){//wenn das Tropizard nicht kampfbereit ist, kann es nicht angreifen
        ang a(0,attacke[i]->get_typ());
        cout<<"Tropizard nicht Kampfbereit"<<endl;
        return a;
    }

    attacke[i]->ausfuehren();//ausgewählte attacke wird ausgeführt

    if(attacke[i]->get_typ()==typ){//Wenn attacke gleichen Typ wie Tropizard hat (Wasser), dann erhöhen sich die Schadenspunkte um einen Bonus
        ang a((angriff+attacke[i]->get_schaden())*1.5,attacke[i]->get_typ());
        return a;
    }else{//bei einem unterschiedlichen Typ gibt es kein Bonus
        ang a(angriff+attacke[i]->get_schaden(),attacke[i]->get_typ());
        return a;
    }

}

/*
 * Tropizard wird angegriffen
 * @param ang: ein tupel aus Schadenspunkte (int), Typ der Attacke (string)
 * @return: EP werden zurückgegeben
*/
int Tropizard::wird_angegriffen(const tuple<int,string>& ang){
    if(!kampfbereit){//Wenn Tropizard nicht kampfbereit ist, kann es nicht angegriffen werden
        cout<<name<<" ist nicht Kampfbereit und kann nicht angegriffen werden!"<<endl;
        return 0;
    }

    auto [w,t]=ang; //w=Schadenspunkte und t=Typ des angriffs werden ausgelesen

    if(t==typ){//Wenn der Typ der Attacke der gleiche wie von Tropizard (Pflanze) ist, dann reduzieren sich die Schadenspunkte
        w=w*0.7;
    }

    if(verteidigung>=w||w==0){//wenn verteidigung groeßer als der angriff oder der angriff == 0
        cout<<"Angriff nicht Effektiv!"<<endl;
        hp=hp-12;//eingeringer Teil der HP werden abgezogen
    }else{
        hp=hp-w+verteidigung; //ansonsten werden neue HP berechnet
    }

    if(hp<=0){//wenn HP unter 0 fallen
        hp=0;//werden HP auf 0 gesetzt
        kampfbereit=false;//Tropizard ist nicht mehr Kampfbereit
        return level*150;//gibt EP zurück
    }else{
        return 0;//sonst keine EP zurück
    }
}

/*
 * Erfahrungspunkte und evtl. Level erhöhen
 * @param punkte: erfahrungspunkte die Tropizard durch einen Angriff erhält
*/
void Tropizard::leveln(const int& punkte){

    ep=ep+punkte;//punkte werden zu vorhandene ep addiert

    //Ein Monster kann maximal ep_max erfahrungspunkte haben, dann steigt das level
    while(ep>ep_max){//solange die ep grösser als maximal ep sind
        level++;//steigt das level und sonstige werte
        angriff+=2;
        verteidigung+=2;
        initiative+=2;

        ep=ep-ep_max;// neue ep werden berechnet
        ep_max=ep_max+ep_max*0.15;//maimal ep steigen um nächstes level zu errechnen

        if(hp==hp_max){//wenn HP des Monsters voll sind
            hp_max+=10;//max Hp erhöhen
            hp=hp_max;//hp auf max hp setzen
        }else{
            hp_max+=10;//sonst nur max hp erhöhen
        }

    }

}

/*
 * Tropizard Kampfbereit setzen
*/
void Tropizard::heilen(){
    hp=hp_max; //werte werden auf max werte gesetzt
    attacke[0]->set_ap();
    attacke[1]->set_ap();

    kampfbereit=true;//Tropizard ist kampfbereit
}

/*
 * Name zurückgeben
 * @return: name
*/
string Tropizard::get_name() const{
    return name;
}

/*
 * level zurückgeben
 * @return: level
*/
int Tropizard::get_level() const{
    return level;
}

/*
 * HP zurückgeben
 * @return: HP
*/
int Tropizard::get_hp() const{
    return hp;
}

/*
 * max HP zurückgeben
 * @return: max HP
*/
int Tropizard::get_hpMax() const{
    return hp_max;
}

/*
 * erfahrungspunkte zurückgeben
 * @return: ep
*/
int Tropizard::get_ep() const{
    return ep;
}

/*
 * Maximale erfahrungspunkte zurückgeben
 * @return: ep_max
*/
int Tropizard::get_epMax() const{
    return ep_max;
}

/*
 * zurückgeben, ob Tropizard kampffähig ist
 * @return: status kampfbereit
*/
bool Tropizard::ist_kampfbereit() const{
    return kampfbereit;
}

/*
 * Erste Attacke zurückgeben
 * @return: Pointer auf die erste Attacke
*/
Attacke* Tropizard::get_Attacke1() const{
    return attacke[0];
}

/*
 * Zweite Attacke zurückgeben
 * @return: Pointer auf die zweite Attacke
*/
Attacke* Tropizard::get_Attacke2() const{
    return attacke[1];
}

/*
 * Angriffsstärke zurückgeben
 * @return: Angriffsstärke
*/
int Tropizard::get_angriff() const{
    return angriff;
}

/*
 * Verteidigungsstärke zurückgeben
 * @return: Verteidigungsstärke
*/
int Tropizard::get_verteidigung() const{
    return verteidigung;
}

/*
 * höhe der Initiative zurückgeben
 * @return: initiative
*/
int Tropizard::get_initiative() const{
    return initiative;
}
