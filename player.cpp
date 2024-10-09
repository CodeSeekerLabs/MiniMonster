/************
Autor:      Tony Lenter

Projekt:    MiniMonster
            Ein Spiel in dem 2 Spieler verschiedene Monster gegeneinander antreten lassen können

Klasse:     Player
            Implementiert das Verhalten und die Eigenschaften eines Spielers

Datum:      15.07.2024
*************/

#include "player.h"

#include "Monster.h"

#include "wavertle.h"
#include "floradon.h"
#include "pyrozard.h"
#include "moorgeck.h"
#include "tropizard.h"
#include "flammfeder.h"

#include "fstream"
#include "iostream"
using namespace std;


Player::Player(const string& n) {
    name=n;

    //Ein Playerobjekt hat zunächst keine Monster
    m[0]=nullptr;
    m[1]=nullptr;
    m[2]=nullptr;
    anzahlMonster=0;
}


Player::~Player(){
    cout<<"~Player"<<endl;
    //den für die Moster allokierten speicher freigeben
    delete m[0];
    delete m[1];
    delete m[2];
}

Player::Player(){
    name="Spieler_Name";

    m[0]=nullptr;
    m[1]=nullptr;
    m[2]=nullptr;
    anzahlMonster=0;
}


/*
 * Monster m[0] setzen
 * @param *mon: Ein Pointer auf ein Monster
*/
void Player::set_monster1(Monster *mon){

    if(mon != nullptr){ //wenn mon kein nullptr ist
        if(m[0]==nullptr){//wenn m[i] zuvor nullptr ist
            anzahlMonster++;//wird die anzahl der monster inkrementiert
        }
        m[0]=mon;//der Pointer vom player zeigt auf das jeweilige Monster

    }else{//wenn mon nullptr ist
        if(m[0]!=nullptr){//wenn m[i] zuvor kein nullptr war
            anzahlMonster--;//anzahl der monster wird dekrementiert   
        }
        m[0]=mon;//Pointer vom player zeigt auf nullptr

    }
}

/*
 * Monster m[1] setzen
 * @param *mon: Ein Pointer auf ein Monster
*/
void Player::set_monster2(Monster *mon){

    if(mon != nullptr){ //wenn mon kein nullptr ist
        if(m[1]==nullptr){//wenn m[i] zuvor nullptr ist
            anzahlMonster++;//wird die anzahl der monster inkrementiert
        }
        m[1]=mon;//der Pointer vom player zeigt auf das jeweilige Monster

    }else{//wenn mon nullptr ist
        if(m[1]!=nullptr){//wenn m[i] zuvor kein nullptr war
            anzahlMonster--;//anzahl der monster wird dekrementiert
        }
        m[1]=mon;//Pointer vom player zeigt auf nullptr

    }
}

/*
 * Monster m[2] setzen
 * @param *mon: Ein Pointer auf ein Monster
*/
void Player::set_monster3(Monster *mon){

    if(mon != nullptr){ //wenn mon kein nullptr ist
        if(m[2]==nullptr){//wenn m[i] zuvor nullptr ist
            anzahlMonster++;//wird die anzahl der monster inkrementiert
        }
        m[2]=mon;//der Pointer vom player zeigt auf das jeweilige Monster

    }else{//wenn mon nullptr ist
        if(m[2]!=nullptr){//wenn m[i] zuvor kein nullptr war
            anzahlMonster--;//anzahl der monster wird dekrementiert
        }
        m[2]=mon;//Pointer vom player zeigt auf nullptr

    }
}

/*
 * Pointer auf ausgewähltes Monster zurückgeben
 * @param i: auswahl für das monster 0 bis 2
 * @return: pointer auf ein Monster
*/
Monster* Player::get_monster(const int& i) const{
    return m[i];
}

/*
 * Name des Spielers zurückgeben
 * @return: Name des Spielers
*/
string Player::get_name()const{
    return name;
}

/*
 * Monster m[0] löschen
 *
*/
void Player::del_monster1(){
    if(m[0]!=nullptr){//Wenn m[0] kein nullptr
        delete m[0];// löschen
        m[0]=nullptr;// auf nullptr setzen
        anzahlMonster--;//anzahl der Monster dekrementieren
    }
}

/*
 * Monster m[1] löschen
 *
*/
void Player::del_monster2(){
    if(m[1]!=nullptr){//Wenn m[1] kein nullptr
        delete m[1];// löschen
        m[1]=nullptr;// auf nullptr setzen
        anzahlMonster--;//anzahl der Monster dekrementieren
    }
}

/*
 * Monster m[2] löschen
 *
*/
void Player::del_monster3(){
    if(m[2]!=nullptr){//Wenn m[2] kein nullptr
        delete m[2];// löschen
        m[2]=nullptr;// auf nullptr setzen
        anzahlMonster--;//anzahl der Monster dekrementieren
    }
}

/*
 * Anzahl der Monster zurückgeben
 * @return: Anzahl Monster
*/
int Player::get_Anzahl()const{
    return anzahlMonster;
}

/*
 * Anzahl der aktiven Monster zurückgeben
 * @return: Anzahl aktiver Monster
*/
int Player::get_AnzahlAktiverMonster() const{
    int anzahl=0;

    for(int i=0; i<3; i++){ //schleife um Monster durchzugehen
        if(m[i]!=nullptr){ //wenn kein nullptr
            //können methoden des monsters genutzt werden
            if(m[i]->ist_kampfbereit()){//wenn kampfbereit
                anzahl++;//anzahl erhöhen
            }
        }
    }

    return anzahl;
}

/*
 * Daten des Spielers in eine Textdatei schreiben
 * @param s: Name/Pfad der Datei
*/
void Player::serialize(const string& s) const{

    ofstream d(s);//Datei zum schreiben öffnen

    if(!d){//Fehlermeldung falls Datei nicht göffnet werden kann
        cout<<"Datei kann nicht geoeffnet werden"<<endl;
    }else{
        d<<name<<endl;//Name schreiben
        d<<anzahlMonster<<endl;//anzahlMonster schreiben

        if(m[0]!=nullptr){ //wenn Monster vorhanden
            d<<m[0]->statistik();//Daten des Monsters schreiben
        }

        if(m[1]!=nullptr){//wenn Monster vorhanden
            d<<m[1]->statistik();//Daten des Monsters schreiben
        }

        if(m[2]!=nullptr){//wenn Monster vorhanden
            d<<m[2]->statistik();//Daten des Monsters schreiben
        }
    }

    d.close();//Datei schließen
}

/*
 * Daten des Spielers aus einer Textdatei lesen
 * @param s: Name/Pfad der Datei
*/
void Player::deserialize(const string& s){
    ifstream d(s);
    string mon="", n="";
    int l=0,h=0,hm=0,e=0, em=0,ap1=0,ap2=0,i=0, ang=0, vert=0, init=0;
    bool k;

    if(!d){//Fehlermeldung falls datei nicht geöffnet werden kann
        cout<<"Datei kann nicht geoeffnet werden"<<endl;
    }else{
        //Daten des Spielers zurücksetzen
        name="";
        anzahlMonster=0;
        m[0]=nullptr;
        m[1]=nullptr;
        m[2]=nullptr;

        //Daten des Spielers lesen
        d>>name;
        cout<<name<<endl;
        d>>anzahlMonster;
        cout<<anzahlMonster<<endl;

        //Schleife um Daten der Monster zu lesen
        while(i<anzahlMonster){
            d>>mon;
            cout<<mon<<endl;
            d>>n;
            cout<<n<<endl;
            d>>l;
            cout<<l<<endl;
            d>>h;
            cout<<h<<endl;
            d>>hm;
            cout<<hm<<endl;
            d>>e;
            cout<<e<<endl;
            d>>em;
            cout<<em<<endl;
            d>>k;
            cout<<k<<endl;
            d>>ang;
            cout<<ang;
            d>>vert;
            cout<<vert;
            d>>init;
            cout<<init;
            d>>ap1;
            cout<<ap1<<endl;
            d>>ap2;
            cout<<ap2<<endl;


            //neue Monster erstellen
            if(mon=="Wavertle"){
                m[i]=new Wavertle(n,l,h,hm,e,em,k,ang,vert,init,ap1,ap2);
            }else if(mon=="Floradon"){
                m[i]=new Floradon(n,l,h,hm,e,em,k,ang,vert,init,ap1,ap2);
            }else if(mon=="Pyrozard"){
                m[i]=new Pyrozard(n,l,h,hm,e,em,k,ang,vert,init,ap1,ap2);
            }else if(mon=="Moorgeck"){
                m[i]=new Moorgeck(n,l,h,hm,e,em,k,ang,vert,init,ap1,ap2);
            }else if(mon=="Tropizard"){
                m[i]=new Tropizard(n,l,h,hm,e,em,k,ang,vert,init,ap1,ap2);
            }else if(mon=="Flammfeder"){
                m[i]=new Flammfeder(n,l,h,hm,e,em,k,ang,vert,init,ap1,ap2);
            }else{
                m[i]=nullptr;
            }

            i++;
        }
    }

    d.close();

}
