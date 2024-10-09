/************
Autor:      Tony Lenter

Projekt:    MiniMonster
            Ein Spiel in dem 2 Spieler verschiedene Monster gegeneinander antreten lassen können

Klasse:     MonsterWindow
            Erstellt ein Fenster in welchem ein Spieler die Monster auswählen kann, die er in den Kampf schicken möchte

Datum:      15.07.2024
*************/

#include "monsterwindow.h"
#include "ui_monsterwindow.h"

#include "wavertle.h"
#include "floradon.h"
#include "pyrozard.h"
#include "moorgeck.h"
#include "tropizard.h"
#include "flammfeder.h"
#include "player.h"

//#include "QPixmap"

#include "iostream"
using namespace std;

MonsterWindow::MonsterWindow(QWidget *parent, Player *p)
    : QDialog(parent)
    , ui(new Ui::MonsterWindow)
{
    ui->setupUi(this);

    player=p;

    ui->labelName->setText(QString::fromStdString(p->get_name()));
    ui->labelName_2->setText(QString::fromStdString(p->get_name()));

    ui->lineMonster1->setPlaceholderText("Erstes Monster");
    ui->lineMonster2->setPlaceholderText("Zweites Monster");
    ui->lineMonster3->setPlaceholderText("Drittes Monster");

    QPixmap wavertle("./pictures/Wavertle.png");
    ui->labelBildWavertle->setPixmap(wavertle.scaled(150,150,Qt::KeepAspectRatio));

    QPixmap floradon("./pictures/Floradon.png");
    ui->labelBildFloradon->setPixmap(floradon.scaled(150,150,Qt::KeepAspectRatio));

    QPixmap pyrozard("./pictures/Pyrozard.png");
    ui->labelBildPyrozard->setPixmap(pyrozard.scaled(150,150,Qt::KeepAspectRatio));

    QPixmap moorgeck("./pictures/Moorgeck.png");
    ui->labelBildMoorgeck->setPixmap(moorgeck.scaled(150,150,Qt::KeepAspectRatio));

    QPixmap tropizard("./pictures/Tropizard.png");
    ui->labelBildTropizard->setPixmap(tropizard.scaled(150,150,Qt::KeepAspectRatio));

    QPixmap flammfeder("./pictures/Flammfeder.png");
    ui->labelBildFlammfeder->setPixmap(flammfeder.scaled(150,150,Qt::KeepAspectRatio));
}

MonsterWindow::~MonsterWindow()
{
    delete ui;
}

/*
 * Bestätigung
 * Fenster schließen
*/
void MonsterWindow::btnOkAbbr_accepted()
{
    accept();
}

/*
 *Abbruch
 *erzeugte Monster aus Player löschen/entfernen
 *Fenster Schließen
*/
void MonsterWindow::btnOkAbbr_rejected()
{
    reject();
}

/*
 * reject override
 * damit Monster gelöscht werden wenn x gedrückt wird zum fenster schließen
*/
void MonsterWindow::reject(){
    player->del_monster1();//Monster löschen
    player->del_monster2();
    player->del_monster3();

    QDialog::reject();//expliziter aufruf von reject der Klasse QDialog
}

/*
 * ein Wavertle dem Player hinzufügen
*/
void MonsterWindow::btnWavertle()
{
    hinzu(new Wavertle("Wavertle"));
    //wird gelöscht wenn player zerstört wird oder wenn Button Delete ausgeführt wird
}

/*
 * ein Floradon dem Player hinzufügen
*/
void MonsterWindow::btnFloradon()
{
    hinzu(new Floradon("Floradon"));
    //wird gelöscht wenn player zerstört wird oder wenn Button Delete ausgeführt wird
}

/*
 * ein Pyrozard dem Player hinzufügen
*/
void MonsterWindow::btnPyrozard()
{
    hinzu(new Pyrozard("Pyrozard"));
    //wird gelöscht wenn player zerstört wird oder wenn Button Delete ausgeführt wird
}

/*
 * ein Hydropi dem Player hinzufügen
*/
void MonsterWindow::btnMoorgeck()
{
    hinzu(new Moorgeck("Moorgeck"));
    //wird gelöscht wenn player zerstört wird oder wenn Button Delete ausgeführt wird
}

/*
 * ein Tropizard dem Player hinzufügen
*/
void MonsterWindow::btnTropizard()
{
    hinzu(new Tropizard("Tropizard"));
    //wird gelöscht wenn player zerstört wird oder wenn Button Delete ausgeführt wird
}

/*
 * ein Flammfeder dem Player hinzufügen
*/
void MonsterWindow::btnFlammfeder()
{
    hinzu(new Flammfeder("Flammfeder"));
    //wird gelöscht wenn player zerstört wird oder wenn Button Delete ausgeführt wird
}

/*
 * Monster dem Spieler hinzufügen
 * Reihenfolge von Platz 0 nach 2 auffüllen
 * @param m: Pointer auf ein Monster
*/
void MonsterWindow::hinzu(Monster *m){

    //Wenn Platz 0 noch nicht belegt ist mit einem Moster
    if(player->get_monster(0)==nullptr){
        player->set_monster1(m);//wird es an Platz 0 hinzugefügt
        ui->lineMonster1->setText(QString::fromStdString(player->get_monster(0)->get_name()));//monster namen anzeigen
    }else if(player->get_monster(1)==nullptr){
        player->set_monster2(m);//sonst an Platz 1 hinzufügen
        ui->lineMonster2->setText(QString::fromStdString(player->get_monster(1)->get_name()));
    }else if(player->get_monster(2)==nullptr){
        player->set_monster3(m);//sonst an platz 2 hinzufügen
        ui->lineMonster3->setText(QString::fromStdString(player->get_monster(2)->get_name()));
    }else{
        cout<<"Bereits drei Monster ausgewählt!"<<endl;//mehr als drei Monster gehen nicht
    }
}

/*
 * Monster an Platz 0 löschen
*/
void MonsterWindow::btnDelMon1()
{
    player->del_monster1();//Monster an PLatz 0 löschen
    ui->lineMonster1->setText("");//damit kein monster drin steht wenn nur eins zuvor ausgewählt wurde

    //Wenn Platz 1 mit Monster belegt ist
    if(player->get_monster(1)!=nullptr){
        player->set_monster1(player->get_monster(1));//Monster ein Platz vorschieben
        player->set_monster2(nullptr);//muss als nullptr gesetzt werden, damit reject --> del_monster richtig funktioniert
                                      //und um standard wieder herzustellen
        ui->lineMonster1->setText(QString::fromStdString(player->get_monster(0)->get_name()));//Name auf neuen Platz anzeigen
        ui->lineMonster2->setText("");//alten Platz für Namen leeren
    }

    //Wenn Platz 2 mit Monster belegt ist
    if(player->get_monster(2)!=nullptr){
        player->set_monster2(player->get_monster(2));
        //on_btnDelMon3_clicked();// darf nicht gelöscht werden sonst wird das gespeicherte monster auf das der zweite ptr zeigt gelöscht
        player->set_monster3(nullptr);//muss als nullptr gesetzt werden, damit reject --> del_monster richtig funktioniert
                                      //und um standard wieder herzustellen
        ui->lineMonster2->setText(QString::fromStdString(player->get_monster(1)->get_name()));//Name auf neuen Platz anzeigen
        ui->lineMonster3->setText("");//alten Platz für Namen leeren
    }
}

/*
 * Monster an Platz 1 löschen
*/
void MonsterWindow::btnDelMon2()
{
    player->del_monster2();//monster an Platz 1 löschen
    ui->lineMonster2->setText("");//damit kein monster drin steht wenn nur zwei zuvor ausgewählt wurden

    //Wenn Platz 2 mit Monster belegt ist
    if(player->get_monster(2)!=nullptr){
        player->set_monster2(player->get_monster(2));//Monster ein Platz vorschieben
        //on_btnDelMon3_clicked();// darf nicht ausgeführt werden, da sonst Monster gelöscht wird
        player->set_monster3(nullptr);//muss als nullptr gesetzt werden, damit reject --> del_monster richtig funktioniert
                                      //und um standard wieder herzustellen
        ui->lineMonster2->setText(QString::fromStdString(player->get_monster(1)->get_name()));//Name auf neuen Platz anzeigen
        ui->lineMonster3->setText("");//alten Platz für Namen leeren
    }
}

/*
 * Monster an Platz 2 löschen
*/
void MonsterWindow::btnDelMon3()
{
    player->del_monster3();//Monster löschen
    ui->lineMonster3->setText("");//damit kein Monstername mehr drin steht
}
