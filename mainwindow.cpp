/************
Autor:      Tony Lenter

Projekt:    MiniMonster
            Ein Spiel in dem 2 Spieler verschiedene Monster gegeneinander antreten lassen können

Klasse:     MainWindow
            Erstellt das Startfenster zur Verwaltung des Spiels

Datum:      15.07.2024
*************/

#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "QFile"
#include "QFileDialog"
#include "QStandardPaths"



#include "monsterwindow.h"
#include "kampfwindow.h"
#include "player.h"

#include "iostream"
using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lineName1->setPlaceholderText("Name Spieler 1");
    ui->lineName2->setPlaceholderText("Name Spieler 2");

    ui->labelFehler->hide();
    ui->labelFehler2->hide();

    p1=new Player();
    p2=new Player();
    anzeigenP1();
    anzeigenP2();
}

MainWindow::~MainWindow()
{
    delete p1;
    delete p2;
    delete ui;
}


/*btnSpieler1_clicked()
 * einen Player (Spieler1) anlegen mit ausgelesenem Namen
 *
*/
void MainWindow::btnSpieler1()
{
    ui->labelFehler2->hide();
    delete p1;// "leeren" Spieler zunächst löschen


    if(namenTest(ui->lineName1->text())){//Wenn eingegebner Name ungültig ist
        p1=new Player(); //"leerer" Spieler wird wieder erzeugt
        ui->labelFehler->show(); //Fehlermeldung anzeigen, wenn Name falsch ist
        anzeigenP1();//"leeren" Spieler anzeigen
        return; //ausführung beenden
    }

    //Wenn Name gültig
    ui->labelFehler->hide();

    p1= new Player(ui->lineName1->text().toStdString());//neuen Spieler mit dem Namen anlegen
    cout<<"neuer Spieler erzeugt"<<endl;


    MonsterWindow mw= MonsterWindow (this, p1);//Ein MonsterWindow erzeugen um Monster dem Spieler hinzuzufügen
    //mw.setModal(true);//exec() ignores the value of this property and always pops up the dialog as modal.
    mw.exec();

    anzeigenP1();//Spieler anzeigen
}


/*btnSpieler2_clicked()
 * einen Player (Spieler2) anlegen mit ausgelesenem Namen
 *
*/
void MainWindow::btnSpieler2()
{
    ui->labelFehler2->hide();
    delete p2; //"leeren" Spieler zunächst löschen

    if(namenTest(ui->lineName2->text())){//Wenn eingegebner Name ungültig ist
        p2=new Player();//"leerer" Spieler wird wieder erzeugt
        ui->labelFehler->show();//Fehlermeldung anzeigen
        anzeigenP2();//"leeren" Spieler anzeigen
        return;//ausführung beenden
    }

    //Wenn Name gültig
    ui->labelFehler->hide();

    p2= new Player(ui->lineName2->text().toStdString());//neuen Spieler mit dem Namen anlegen
    cout<<"neuer Spieler erzeugt"<<endl;

    MonsterWindow mw= MonsterWindow (this, p2);//Ein MonsterWindow erzeugen um Monster dem Spieler hinzuzufügen
    //mw.setModal(true);//exec() ignores the value of this property and always pops up the dialog as modal.
    mw.exec();

    anzeigenP2();//Spieler anzeigen
}

/*
 * anzeigen von Spieler1
 *
*/
void MainWindow::anzeigenP1(){

    ui->labelKampfName1->setText(QString::fromStdString(p1->get_name()));//Name anzeigen
    ui->label1MonAnzahl->setText(QString::number(p1->get_Anzahl()));//Anzahl Monster anzeigen

    //erstes Monster anzeigen
    if(p1->get_monster(0)!=nullptr){
        ui->label1Mon1->setText(QString::fromStdString(p1->get_monster(0)->get_name()));//Name
        ui->label1HP1->show();//HP-Anzeige darstellen
        ui->label1HPanz1->setText(QString::number(p1->get_monster(0)->get_hp()));//HP anzegien
    }else{
        //Anzeige leer falls kein Monster vorhanden
        ui->label1Mon1->setText("leer");
        ui->label1HP1->hide();
        ui->label1HPanz1->setText("");
    }

    //zweites Monster anzeigen
    if(p1->get_monster(1)!=nullptr){
        ui->label1Mon2->setText(QString::fromStdString(p1->get_monster(1)->get_name()));//Name
        ui->label1HP2->show();//HP-Anzeige darstellen
        ui->label1HPanz2->setText(QString::number(p1->get_monster(1)->get_hp()));//HP anzeigen
    }else{
        //Anzeige leer falls kein Monster vorhanden
        ui->label1Mon2->setText("leer");
        ui->label1HP2->hide();
        ui->label1HPanz2->setText("");
    }

    //drittes Monster anzeigen
    if(p1->get_monster(2)!=nullptr){
        ui->label1Mon3->setText(QString::fromStdString(p1->get_monster(2)->get_name()));//Name
        ui->label1HP3->show();//HP-Anzeige darstellen
        ui->label1HPanz3->setText(QString::number(p1->get_monster(2)->get_hp()));//HP anzeigen
    }else{
        //Anzeige leer falls kein Monster vorhanden
        ui->label1Mon3->setText("leer");
        ui->label1HP3->hide();
        ui->label1HPanz3->setText("");
    }
}



/*
 * anzeigen von Spieler 2
 *
*/
void MainWindow::anzeigenP2(){

    ui->labelKampfName2->setText(QString::fromStdString(p2->get_name()));//Name anzeigen
    ui->label2MonAnzahl->setText(QString::number(p2->get_Anzahl()));//Anzahl Monster anzeigen

    //erstes Monster anzeigen
    if(p2->get_monster(0)!=nullptr){
        ui->label2Mon1->setText(QString::fromStdString(p2->get_monster(0)->get_name()));//Name
        ui->label2HP1->show();//HP-Anzeige darstellen
        ui->label2HPanz1->setText(QString::number(p2->get_monster(0)->get_hp()));//HP anzeigen
    }else{
        //Anzeige leer falls kein Monster vorhanden
        ui->label2Mon1->setText("leer");
        ui->label2HP1->hide();
        ui->label2HPanz1->setText("");
    }

    //zweites Monster anzeigen
    if(p2->get_monster(1)!=nullptr){
        ui->label2Mon2->setText(QString::fromStdString(p2->get_monster(1)->get_name()));//Name
        ui->label2HP2->show();//HP-Anzeige darstellen
        ui->label2HPanz2->setText(QString::number(p2->get_monster(1)->get_hp()));//HP anzeigen
    }else{
        //Anzeige leer falls kein Monster vorhanden
        ui->label2Mon2->setText("leer");
        ui->label2HP2->hide();
        ui->label2HPanz2->setText("");//sonst bleiben alte HP drin stehen falls ein neuer spieler ohne Monster an dieser stelle erzeugt wird
    }

    //drittes Monster anzeigen
    if(p2->get_monster(2)!=nullptr){
        ui->label2Mon3->setText(QString::fromStdString(p2->get_monster(2)->get_name()));//Name
        ui->label2HP3->show();//HP-Anzeige darstellen
        ui->label2HPanz3->setText(QString::number(p2->get_monster(2)->get_hp()));//HP anzeigen
    }else{
        //Anzeige leer falls kein Monster vorhanden
        ui->label2Mon3->setText("leer");
        ui->label2HP3->hide();
        ui->label2HPanz3->setText("");
    }
}

/*
 * Monster von Spieler1 heilen
 *
*/
void MainWindow::btnHeilen1()
{
    //Wenn Monster vorhanden
    if(p1->get_monster(0)!=nullptr){
        p1->get_monster(0)->heilen();//monster heilen
    }

    if(p1->get_monster(1)!=nullptr){
        p1->get_monster(1)->heilen();
    }

    if(p1->get_monster(2)!=nullptr){
        p1->get_monster(2)->heilen();
    }

    ui->labelFehler2->hide();
    anzeigenP1();
}

/*
 *Monster von Spieler2 heilen
 *
*/
void MainWindow::btnHeilen2()
{
    //Wenn monster vorhanden
    if(p2->get_monster(0)!=nullptr){
        p2->get_monster(0)->heilen();//Monster heilen
    }

    if(p2->get_monster(1)!=nullptr){
        p2->get_monster(1)->heilen();
    }

    if(p2->get_monster(2)!=nullptr){
        p2->get_monster(2)->heilen();
    }

    ui->labelFehler2->hide();
    anzeigenP2();
}

/*
 * Spieler1 in Textdatei speichern
 *
*/
void MainWindow::btnSpieler1speichern()
{
    QString path= QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);//Pfad für Dokumentenordner


    //Einen FileDialog öffnen, um Datei erstellen oder überschreiben zu können
    //Dateiname wird als QString gespeichert
    QString fileName= QFileDialog::getSaveFileName(this, "Save Player", path+"/Player1.txt", "Text Files (*.txt)");

    //testen, ob eine Datei ausgewählt wurde
    if(!fileName.isEmpty()){
        p1->serialize(fileName.toStdString());//Spieler in Datei schreiben
    }

    ui->labelFehler2->hide();
}

/*
 * Spieler1 aus Textdatei laden
 *
*/
void MainWindow::btnSpieler1laden()
{
    QString path= QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);//Pfad für Dokumentenordner

    //Einen FileDialog öffnen, um Datei auswählen zu können
    //Dateiname wird als QString gespeichert
    QString fileName= QFileDialog::getOpenFileName(this, "Save Player", path, "Text Files (*.txt)");

    //testen, ob Datei ausgewählt wurde
    if(!fileName.isEmpty()){
        p1->deserialize(fileName.toStdString());//Spieler aus Datei lesen
    }

    ui->labelFehler2->hide();
    anzeigenP1();//Spieler anzeigen
}

/*
 * Spieler2 in Textdatei speichern
 *
*/
void MainWindow::btnSpieler2speichern()
{
    QString path= QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);//Pfad für Dokumentenordner

    //Einen FileDialog öffnen, um Datei erstellen oder überschreiben zu können
    //Dateiname wird als QString gespeichert
    QString fileName= QFileDialog::getSaveFileName(this, "Save Player", path+"/Player2.txt", "Text Files (*.txt)");

    //testen, ob Datei ausgewählt wurde
    if(!fileName.isEmpty()){
        p2->serialize(fileName.toStdString());//Spieler in Datei schreiben
    }

    ui->labelFehler2->hide();
}

/*
 * Spieler2 aus Textdatei laden
 *
*/
void MainWindow::btnSpieler2laden()
{
    QString path= QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);//Pfad für Dokumentenordner

    //Einen FileDialog öffnen, um Datei auswählen zu können
    //Dateiname wird als QString gespeichert
    QString fileName= QFileDialog::getOpenFileName(this, "Open Saved Player", path, "Text Files (*.txt)");

    //testen, ob Datei ausgewählt wurde
    if(!fileName.isEmpty()){
        p2->deserialize(fileName.toStdString());//Spieler aus Datei lesen
    }

    ui->labelFehler2->hide();
    anzeigenP2();//Spieler anzeigen
}


/*
 * testen, ob Name ein Leerezeichen enthält (sonst funktioniert das laden nicht)
 * oder leer ist
 * @param s: Ein QString der den Namen enthält
*/
bool MainWindow::namenTest(QString s){

    if(s==""){
        cout<<"Name leer"<<endl;
        return true;
    }

    if(s.contains(" ")){
        cout<<"Leerzeichen"<<endl;
        return true;
    }

    return false;
}

/*
 * Kampf Fenster öffnen
 *
*/
void MainWindow::btnKampf()
{

    ui->labelFehler2->hide();
    //testen, dass es mindestens ein Kampffähiges monster gibt pro Spieler
    //reicht aus, um auch zu wissen dass Monster vohanden sind
    //Wenn keine Monster vorhanden sind gibt es auch keine Kampffähigen

    if((p1->get_AnzahlAktiverMonster()>0)&&(p2->get_AnzahlAktiverMonster()>0)){
        KampfWindow kw = KampfWindow(this, p1, p2);//Kampfwindow erstellen und anzeigen
        kw.exec();
        anzeigenP1();//Spieler nach dem Kampf anzeigen
        anzeigenP2();
    }else{
        cout<<"keine Monster"<<endl;
        ui->labelFehler2->show();//Fehlermeldung wenn keine Kampffähigen Monster vorhanden sind
    }

}

