/************
Autor:      Tony Lenter

Projekt:    MiniMonster
            Ein Spiel in dem 2 Spieler verschiedene Monster gegeneinander antreten lassen können

Klasse:     KampfWindow
            Erstellt das Kampffenster in welchem die Spieler ihre Monster gegeneinander antreten lassen

Datum:      15.07.2024
*************/

#include "kampfwindow.h"
#include "ui_kampfwindow.h"

#include "player.h"
#include "Monster.h"
#include "QMovie"
//#include "iostream"

using namespace std;

KampfWindow::KampfWindow(QWidget *parent, Player *player1, Player *player2)
    : QDialog(parent)
    , ui(new Ui::KampfWindow)
{
    ui->setupUi(this);

    p1=player1;
    p2=player2;



    monsterAuswahlP1=0;
    monsterAuswahlP2=0;


    anzeigenP1();
    anzeigenP2();
    hideKampfPlayer1();
    hideAttPlayer1();
    hideKampfPlayer2();
    hideAttPlayer2();

    ui->btn1Auswahl2->hide();
    ui->btn1Auswahl3->hide();
    ui->btn2Auswahl2->hide();
    ui->btn2Auswahl3->hide();

    ui->labelKonfetti->hide();

    ui->text->setText("Startet euren Kampf!");
}

KampfWindow::~KampfWindow()
{
    delete ui;
}

/*
 * Kampf starten
 * erstes kampffähiges Monster für jeden Spieler finden
*/
void KampfWindow::btnStart()
{

    //es gibt auf jeden fall das erste Monster und es gibt mindestens ein Kampffähiges monster
    //das erste monster muss jedoch nicht kampffähig sein

    //monster für Player1 finden
    for(int i=0; i<3; i++){
        if(p1->get_monster(i)!=nullptr){//wenn es kein nullptr ist
            //cout<<"monName: "<<p1->get_monster(i)->get_name()<<";  HP: "<<p1->get_monster(i)->get_hp()<<";  Kampfbereit: "<<p1->get_monster(i)->ist_kampfbereit()<<endl;

            if(!p1->get_monster(i)->ist_kampfbereit()){//kann das monster überprüft werden ob es kampffähig ist
                monsterAuswahlP1++;// ist es nicht kampffähig wird die auswahl inkrementiert, um nächstes monster auszuwählen
                                // da es min. ein kampffähiges monster gibt wird dieses gefunden
            }else{
                break; //wenn monster kampffähig ist, muss die auswahl nicht weiter erhöht werden und schleife kann abgebrochen werden
            }
        }
    }

    //monster für Player2 finden
    for(int i=0; i<3; i++){
        if(p2->get_monster(i)!=nullptr){
            //cout<<"monName: "<<p2->get_monster(i)->get_name()<<";  HP: "<<p2->get_monster(i)->get_hp()<<";  Kampfbereit: "<<p2->get_monster(i)->ist_kampfbereit()<<endl;

            if(!p2->get_monster(i)->ist_kampfbereit()){
                monsterAuswahlP2++;
            }else{
                break;
            }
        }    
    }

    kampfBeginn();
    ui->btnStart->hide();
}

/*
 * Fensterinhalt für den Kampf/die Runde darstellen
 *
*/
void KampfWindow::kampfBeginn(){
    showKampfPlayer1(p1->get_monster(monsterAuswahlP1));//Bilder der Monster anzeigen
    showKampfPlayer2(p2->get_monster(monsterAuswahlP2));

    //Auswählen welches Monster den Kampf beginen darf, das mit der höheren initiative
    if(p1->get_monster(monsterAuswahlP1)->get_initiative()>=p2->get_monster(monsterAuswahlP2)->get_initiative()){
        ui->text->setText(QString::fromStdString("Spieler "+p1->get_name()+" wähle deine Attacke!"));
        hideAttPlayer2();//Attacken vom Spieler2 verbergen
        showAttPlayer1(p1->get_monster(monsterAuswahlP1));//Attacken vom Spieler1 anzeigen
    }else{
        ui->text->setText(QString::fromStdString("Spieler "+p2->get_name()+" wähle deine Attacke!"));
        hideAttPlayer1();//Attacken von Spieler1 verbergen
        showAttPlayer2(p2->get_monster(monsterAuswahlP2));//Attacken von Spieler2 anzeigen
    }
}


/*
 * Monster von Spieler1 anzeigen
 *
*/
void KampfWindow::anzeigenP1(){

    ui->labelKampfName1->setText(QString::fromStdString(p1->get_name()));//Name Spieler1

    //Wenn erstes Monster vorhanden (wurde eigentlich schon zuvor überprüft)
    if(p1->get_monster(0)!=nullptr){

        ui->text1Mon1->setText(QString::fromStdString(p1->get_monster(0)->get_name()));//Monster Namen anzeigen

        //Wenn Monster Kampfbereit
        if(p1->get_monster(0)->ist_kampfbereit()){
            ui->text1Mon1->setStyleSheet("background-color: rgb(23,145,52)");//grün anzeigen
        }else{
            ui->text1Mon1->setStyleSheet("background-color: rgb(165,29,45)");// sonst rot anezigen
        }

    }else{//Wenn Monster nicht vorhanden
        ui->text1Mon1->setText("leer");//leer anzeigen
        ui->text1Mon1->setStyleSheet("");//und keine Farbe
    }


    //Vorgehen wiederholt sich für die anderen Monster

    if(p1->get_monster(1)!=nullptr){
        ui->text1Mon2->setText(QString::fromStdString(p1->get_monster(1)->get_name()));

        if(p1->get_monster(1)->ist_kampfbereit()){
            ui->text1Mon2->setStyleSheet("background-color: rgb(23,145,52)");
        }else{
            ui->text1Mon2->setStyleSheet("background-color: rgb(165,29,45)");
        }

    }else{
        ui->text1Mon2->setText("leer");
        ui->text1Mon2->setStyleSheet("");
    }

    if(p1->get_monster(2)!=nullptr){
        ui->text1Mon3->setText(QString::fromStdString(p1->get_monster(2)->get_name()));

        if(p1->get_monster(2)->ist_kampfbereit()){
            ui->text1Mon3->setStyleSheet("background-color: rgb(23,145,52)");
        }else{
            ui->text1Mon3->setStyleSheet("background-color: rgb(165,29,45)");
        }

    }else{
        ui->text1Mon3->setText("leer");
        ui->text1Mon3->setStyleSheet("");
    }
}

/*
 * Monster von Spieler2 anzeigen
 *
*/
void KampfWindow::anzeigenP2(){

    //Vorgehen ist das gleiche wie bei Spieler1 [KampfWindow::anzeigenP1()]

    ui->labelKampfName2->setText(QString::fromStdString(p2->get_name()));

    if(p2->get_monster(0)!=nullptr){
        ui->text2Mon1->setText(QString::fromStdString(p2->get_monster(0)->get_name()));

        if(p2->get_monster(0)->ist_kampfbereit()){
            ui->text2Mon1->setStyleSheet("background-color: rgb(23,145,52)");
        }else{
            ui->text2Mon1->setStyleSheet("background-color: rgb(165,29,45)");
        }

    }else{
        ui->text2Mon1->setText("leer");
        ui->text2Mon1->setStyleSheet("");
    }

    if(p2->get_monster(1)!=nullptr){
        ui->text2Mon2->setText(QString::fromStdString(p2->get_monster(1)->get_name()));

        if(p2->get_monster(1)->ist_kampfbereit()){
            ui->text2Mon2->setStyleSheet("background-color: rgb(23,145,52)");
        }else{
            ui->text2Mon2->setStyleSheet("background-color: rgb(165,29,45)");
        }

    }else{
        ui->text2Mon2->setText("leer");
        ui->text2Mon2->setStyleSheet("");
    }

    if(p2->get_monster(2)!=nullptr){
        ui->text2Mon3->setText(QString::fromStdString(p2->get_monster(2)->get_name()));

        if(p2->get_monster(2)->ist_kampfbereit()){
            ui->text2Mon3->setStyleSheet("background-color: rgb(23,145,52)");
        }else{
            ui->text2Mon3->setStyleSheet("background-color: rgb(165,29,45)");
        }

    }else{
        ui->text2Mon3->setText("leer");
        ui->text2Mon3->setStyleSheet("");
    }
}

/*
 * Das Kampfinterface von Spieler1 verbergen
*/
void KampfWindow::hideKampfPlayer1(){
    ui->lifeBar1->hide(); //Lebensanzeige des Monsters verbergen
    ui->lvlBar1->hide(); //ep Anzeige verbergen
    ui->labelLevel1->hide();//level verbergen
    ui->label1HP->hide(); //"HP" verbergen
    ui->label1HPmon->hide();// Label für HP des Monsters verbergen
    ui->labelBild1->hide();//Bild des Monsters verbergen
}

/*
 * Das Kampfinterface von Spieler2 verbergen
*/
void KampfWindow::hideKampfPlayer2(){
    ui->lifeBar2->hide();//Lebensanzeige des Monsters verbergen
    ui->lvlBar2->hide();//ep Anzeige verbergen
    ui->labelLevel2->hide();//level verbergen
    ui->label2HP->hide();//"HP" verbergen
    ui->label2HPmon->hide();// Label für HP des Monsters verbergen
    ui->labelBild2->hide();//Bild des Monsters verbergen
}

/*
 * Attacken des Monsters von Spieler1 verbergen
*/
void KampfWindow::hideAttPlayer1(){
    ui->btn1Att1->hide();
    ui->btn1Att2->hide();
}

/*
 * Attacken des Monsters von Spieler2 verbergen
*/
void KampfWindow::hideAttPlayer2(){
    ui->btn2Att1->hide();
    ui->btn2Att2->hide();
}

/*
 * Kampfinterface von Spieler1 anzeigen
 * @param m: Pointer auf ein Monster
*/
void KampfWindow::showKampfPlayer1(Monster *m){
    ui->lifeBar1->show();//Lebensanzeige des Monsters
    ui->lifeBar1->setValue(100*m->get_hp()/m->get_hpMax());//Wert für Lebensanzeige in % umrechenen

    ui->lvlBar1->show();
    ui->lvlBar1->setValue(100*m->get_ep()/m->get_epMax());//Wert für Levelanzeige in % umrechnen

    ui->labelLevel1->show();
    ui->labelLevel1->setText("Lv: "+QString::number(m->get_level()));

    ui->label1HP->show();//"HP" anzeigen
    ui->label1HPmon->show();//Label für HP des Monsters anzeigen
    ui->label1HPmon->setText(QString::number(m->get_hp()));//HP des Monsters setzen

    ui->labelBild1->show();// Label für das Bild des Monsters anzeigen
    QPixmap monster(QString::fromStdString("./pictures/"+m->get_name()+".png"));//neues Pixmap-Objekt erstellen mit Bild des Monsters
    ui->labelBild1->setPixmap(monster.scaled(150,150,Qt::KeepAspectRatio));//Pimap-Objekt anzeigen im Label

}

/*
 * Kampfinterface von Spieler2 anzeigen
 * @param m: Pointer auf ein Monster
*/
void KampfWindow::showKampfPlayer2(Monster *m){
    ui->lifeBar2->show();//Lebensanzeige des Monsters
    ui->lifeBar2->setValue(100*m->get_hp()/m->get_hpMax());//Wert für Lebensanzeige in % umrechenen

    ui->lvlBar2->show();
    ui->lvlBar2->setValue(100*m->get_ep()/m->get_epMax());

    ui->labelLevel2->show();
    ui->labelLevel2->setText("Lv: "+QString::number(m->get_level()));

    ui->label2HP->show();//"HP" anzeigen
    ui->label2HPmon->show();//Label für HP des Monsters anzeigen
    ui->label2HPmon->setText(QString::number(m->get_hp()));//HP des Monsters setzen

    ui->labelBild2->show();// Label für das Bild des Monsters anzeigen
    QPixmap monster(QString::fromStdString("./pictures/"+m->get_name()+".png"));//neues Pixmap-Objekt erstellen mit Bild des Monsters
    ui->labelBild2->setPixmap(monster.scaled(150,150,Qt::KeepAspectRatio));//Pimap-Objekt anzeigen im Label
}

/*
 * Attacken des Monsters von Spieler1 anzeigen
 * @param m: Pointer auf ein Monster
*/
void KampfWindow::showAttPlayer1(Monster *m){
    ui->btn1Att1->show();//Button anzeigen
    ui->btn1Att1->setText(QString::fromStdString(m->get_Attacke1()->get_name()));//Text im Button setzen
    ui->btn1Att2->show();
    ui->btn1Att2->setText(QString::fromStdString(m->get_Attacke2()->get_name()));
}

/*
 * Attacken des Monsters von Spieler2 anzeigen
 * @param m: Pointer auf ein Monster
*/
void KampfWindow::showAttPlayer2(Monster *m){
    ui->btn2Att1->show();//Button anzeigen
    ui->btn2Att1->setText(QString::fromStdString(m->get_Attacke1()->get_name()));//Text im Button setzen
    ui->btn2Att2->show();
    ui->btn2Att2->setText(QString::fromStdString(m->get_Attacke2()->get_name()));
}


/*
 * Erste Attacke des Monsters von Spieler1 ausführen
*/
void KampfWindow::btn1Att1()
{
    //Attacke ausführen
    p1->get_monster(monsterAuswahlP1)->leveln(p2->get_monster(monsterAuswahlP2)->wird_angegriffen(p1->get_monster(monsterAuswahlP1)->angreifen(0)));
    showKampfPlayer2(p2->get_monster(monsterAuswahlP2));//Kampfinterface für Spieler2 neu erstellen
    hideAttPlayer1();//eigene Attacken verbergen, da jetzt der jeweils andere Spieler am Zug ist
    showAttPlayer2(p2->get_monster(monsterAuswahlP2));//Attacken des Monsters vom anderen Spielers anzeigen
    ui->text->setText(QString::fromStdString("Spieler "+p2->get_name()+" wähle deine Attacke!"));//Text setzen

    //Wenn angegriffenes Monster nicht mehr Kampfbereit ist
    if(!p2->get_monster(monsterAuswahlP2)->ist_kampfbereit()){
        hideAttPlayer2(); //Attacken des Monster verbergen
        hideKampfPlayer2();//Kampfinterface verbergen
        anzeigenP2();//Monster neu anzeigen, damit sie rot hinterlegt sind

        //Wenn die Anzahl der aktiven Monster == 0 ist, hat der angegriffene Spieler verloren
        if(p2->get_AnzahlAktiverMonster()==0){

            ui->text->setText(QString::fromStdString("Spieler "+p2->get_name()+" du hast kein Kampffähiges Monster mehr. "+
                                                     "Spieler "+p1->get_name()+" hat gewonnen!"));

            konfetti();//Konfetti für Gewinner starten

        }else{//Wenn es noch aktive Monster gibt, kann der Spieler ein neues auswählen
            ui->text->setText(QString::fromStdString("Spieler "+p2->get_name()+" dein "+p2->get_monster(0)->get_name()+
                                                     " ist nicht mehr Kampffähig! Wähle dein nächstes Monster aus."));

            //Wenn Monster vorhanden
            if(p2->get_monster(1)!=nullptr){
                //Wenn Monster kampfbereit
                if(p2->get_monster(1)->ist_kampfbereit()){
                    ui->btn2Auswahl2->show();//Button zum auswählen anzeigen
                }
            }

            //Wenn Monster vorhanden
            if(p2->get_monster(2)!=nullptr){
                //Wenn Monster kampfbereit
                if(p2->get_monster(2)->ist_kampfbereit()){
                    ui->btn2Auswahl3->show();//Button zum auswählen anzeigen
                }
            }


        }


    }


}

/*
 * Zweite Attacke des Monsters von Spieler1 ausführen
*/
void KampfWindow::btn1Att2()
{
    //Vorgehen ist das gleiche wie bei [KampfWindow::btn1Att1()]

    p1->get_monster(monsterAuswahlP1)->leveln(p2->get_monster(monsterAuswahlP2)->wird_angegriffen(p1->get_monster(monsterAuswahlP1)->angreifen(1)));
    showKampfPlayer2(p2->get_monster(monsterAuswahlP2));
    hideAttPlayer1();
    showAttPlayer2(p2->get_monster(monsterAuswahlP2));
    ui->text->setText(QString::fromStdString("Spieler "+p2->get_name()+" wähle deine Attacke!"));

    if(!p2->get_monster(monsterAuswahlP2)->ist_kampfbereit()){
        hideAttPlayer2();
        hideKampfPlayer2();
        anzeigenP2();

        if(p2->get_AnzahlAktiverMonster()==0){

            ui->text->setText(QString::fromStdString("Spieler "+p2->get_name()+" du hast kein Kampffähiges Monster mehr. "+
                                                     "Spieler "+p1->get_name()+" hat gewonnen!"));
            konfetti();

        }else{
            ui->text->setText(QString::fromStdString("Spieler "+p2->get_name()+" dein "+p2->get_monster(0)->get_name()+
                                                     " ist nicht mehr Kampffähig! Wähle dein nächstes Monster aus."));

            if(p2->get_monster(1)!=nullptr){
                if(p2->get_monster(1)->ist_kampfbereit()){
                    ui->btn2Auswahl2->show();
                }
            }

            if(p2->get_monster(2)!=nullptr){
                if(p2->get_monster(2)->ist_kampfbereit()){
                    ui->btn2Auswahl3->show();
                }
            }


        }


    }
}

/*
 * Erste Attacke des Monsters von Spieler2 ausführen
*/
void KampfWindow::btn2Att1()
{
    //Vorgehen ist das gleiche wie bei [KampfWindow::btn1Att1()]

    p2->get_monster(monsterAuswahlP2)->leveln(p1->get_monster(monsterAuswahlP1)->wird_angegriffen(p2->get_monster(monsterAuswahlP2)->angreifen(0)));
    showKampfPlayer1(p1->get_monster(monsterAuswahlP1));
    hideAttPlayer2();
    showAttPlayer1(p1->get_monster(monsterAuswahlP1));
    ui->text->setText(QString::fromStdString("Spieler "+p1->get_name()+" wähle deine Attacke!"));

    if(!p1->get_monster(monsterAuswahlP1)->ist_kampfbereit()){
        hideAttPlayer1();
        hideKampfPlayer1();
        anzeigenP1();

        if(p1->get_AnzahlAktiverMonster()==0){

            ui->text->setText(QString::fromStdString("Spieler "+p1->get_name()+" du hast kein Kampffähiges Monster mehr. "+
                                                     "Spieler "+p2->get_name()+" hat gewonnen!")); 
            konfetti();

        }else{
            ui->text->setText(QString::fromStdString("Spieler "+p1->get_name()+" dein "+p1->get_monster(0)->get_name()+
                                                     " ist nicht mehr Kampffähig! Wähle dein nächstes Monster aus."));

            if(p1->get_monster(1)!=nullptr){
                if(p1->get_monster(1)->ist_kampfbereit()){
                    ui->btn1Auswahl2->show();
                }
            }

            if(p1->get_monster(2)!=nullptr){
                if(p1->get_monster(2)->ist_kampfbereit()){
                    ui->btn1Auswahl3->show();
                }
            }




        }


    }
}

/*
 * Zweite Attacke des Monsters von Spieler2 ausführen
*/
void KampfWindow::btn2Att2()
{
    //Vorgehen ist das gleiche wie bei [KampfWindow::btn1Att1()]

    p2->get_monster(monsterAuswahlP2)->leveln(p1->get_monster(monsterAuswahlP1)->wird_angegriffen(p2->get_monster(monsterAuswahlP2)->angreifen(1)));
    showKampfPlayer1(p1->get_monster(monsterAuswahlP1));
    hideAttPlayer2();
    showAttPlayer1(p1->get_monster(monsterAuswahlP1));
    ui->text->setText(QString::fromStdString("Spieler "+p1->get_name()+" wähle deine Attacke!"));

    if(!p1->get_monster(monsterAuswahlP1)->ist_kampfbereit()){
        hideAttPlayer1();
        hideKampfPlayer1();
        anzeigenP1();

        if(p1->get_AnzahlAktiverMonster()==0){

            ui->text->setText(QString::fromStdString("Spieler "+p1->get_name()+" du hast kein Kampffähiges Monster mehr. "+
                                                     "Spieler "+p2->get_name()+" hat gewonnen!"));
            konfetti();

        }else{
            ui->text->setText(QString::fromStdString("Spieler "+p1->get_name()+" dein "+p1->get_monster(0)->get_name()+
                                                     " ist nicht mehr Kampffähig! Wähle dein nächstes Monster aus."));

            if(p1->get_monster(1)!=nullptr){
                if(p1->get_monster(1)->ist_kampfbereit()){
                    ui->btn1Auswahl2->show();
                }
            }

            if(p1->get_monster(2)!=nullptr){
                if(p1->get_monster(2)->ist_kampfbereit()){
                    ui->btn1Auswahl3->show();
                }
            }
        }


    }
}

/*
 * zweites Monster von Spieler1 auswählen
*/
void KampfWindow::btn1Auswahl2()
{
    monsterAuswahlP1=1;//monsterAuswahl setzen

    ui->btn1Auswahl2->hide();//Buttons zur Auswahl verbergen
    ui->btn1Auswahl3->hide();

    kampfBeginn();//neue Runde starten
}

/*
 * drittes Monster von Spieler1 auswählen
*/
void KampfWindow::btn1Auswahl3()
{
    monsterAuswahlP1=2;//monsterAuswahl setzen

    ui->btn1Auswahl2->hide();//Buttons zur Auswahl verbergen
    ui->btn1Auswahl3->hide();

    kampfBeginn();//neue Runde starten
}

/*
 * zweites Monster von Spieler2 auswählen
*/
void KampfWindow::btn2Auswahl2()
{
    monsterAuswahlP2=1;//monsterAuswahl setzen

    ui->btn2Auswahl2->hide();//Buttons zur Auswahl verbergen
    ui->btn2Auswahl3->hide();

    kampfBeginn();//neue Runde starten
}

/*
 * drittes Monster von Spieler2 auswählen
*/
void KampfWindow::btn2Auswahl3()
{
    monsterAuswahlP2=2;//monsterAuswahl setzen

    ui->btn2Auswahl2->hide();//Buttons zur Auswahl verbergen
    ui->btn2Auswahl3->hide();

    kampfBeginn();//neue Runde starten
}

/*
 * Konfetti für den Gewinner anzeigen
*/
void KampfWindow::konfetti(){

    //Ein Movie-Object erstellen mit Konfetti Gif
    QMovie *konfetti=new QMovie("./pictures/konfetti.gif");

    ui->labelKonfetti->show();//Label für Konfetti anzeigen
    ui->labelKonfetti->setMovie(konfetti);//Konfetti in label einfügen; benötigt pointer
    konfetti->start();//Gif starten
}
