#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employes.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QRegExpValidator>
#include <QSqlQueryModel>
#include <QPrinter>
#include"QFont"
#include"QPen"
#include"QPdfWriter"
#include"QTextDocumentWriter"
#include"QDesktopServices"
#include"QtPrintSupport/QPrinter"
#include<QPainter>
#include<QImage>
#include<QSqlQuery>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab_employes->setModel(Em.afficherEmployes());
    //valider que 7 chiffres
    ui->le_idE->setValidator(new QIntValidator(0,9999999, this));
    //valider que les adresses mail
    QRegExp rx("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    QRegExpValidator *valiEmail =new QRegExpValidator(rx,this);
    ui->le_e_mail->setValidator(valiEmail);
    //AFFichage de la statistique
    Employes E;
    ui->VL_statistique->addWidget(E.statistiqueEmployes());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{  //récupération des informations saisies à travers l'interface graphique
    int idE=ui->le_idE->text().toInt();
    QString nomE=ui->le_nomE->text();
    QString prenomE=ui->le_prenomE->text();
    QString adresse=ui->le_adresse->text();
    QString telephone=ui->le_telephone->text();
    QString e_mail=ui->le_e_mail->text();
    QString date_embauche=ui->le_date_embauche->text();
    QString salaire=ui->le_salaire->text();
    QString prime=ui->le_prime->text();
    QString designation=ui->le_designation->text();

    Employes E(idE,nomE,prenomE,adresse,telephone,e_mail,date_embauche,salaire,prime,designation);
    bool test=E.ajouterEmployes();
    //refresh table view
    ui->tab_employes->setModel(Em.afficherEmployes());

    if(test)
{        QMessageBox::information(nullptr, QObject::tr("Ok"),
                    QObject::tr("Ajout bien effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
                    QObject::tr("Ajout non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_pb_supprimer_clicked()
{
    Employes E;
    E.setIDE(ui->le_id_sup->text().toInt());
    bool test=E.supprimerEmployes(E.getIDE());
    if(test)
{
        QMessageBox::information(nullptr, QObject::tr("Ok"),
                    QObject::tr("Suppression bien effectuée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        //refresh table view
        ui->tab_employes->setModel(E.afficherEmployes());

}
    else
        QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
                    QObject::tr("Suppression non effectuée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pb_modifier_clicked()
{
   Employes Emod;
   Emod.setIDE(ui->le_id_modif->text().toInt());
//récupération des valeurs à changer
   QString adresse=ui->le_nouv_adresse->text();
   QString telephone=ui->le_nouv_tele->text();
   QString salaire=ui->le_nouv_salaire->text();
   QString prime=ui->le_nouv_prime->text();
  bool test=Emod.modifierEmployes(Emod.getIDE(),adresse,telephone,salaire,prime);
  if(test)
  {
          QMessageBox::information(nullptr, QObject::tr("Ok"),
                      QObject::tr("modification bien effectuée.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
          //refresh table view
          ui->tab_employes->setModel(Emod.afficherEmployes());

  }
      else
          QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
                      QObject::tr("modification non effectuée.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pb_load_name_clicked()
{ Employes E1;
   ui->tri_table->setModel(E1.afficherEmployes());
}

void MainWindow::on_pb_search_clicked()
{
    Employes E2;
    QString nomS=ui->le_nom_search->text();
    ui->tri_table->setModel(E2.RechercheEmployes(nomS));

}

void MainWindow::on_pb_sort_clicked()
{
    Employes Et;
    ui->tri_table->setModel(Et.trier());
}

void MainWindow::on_pb_pdf_clicked()
{
    QPdfWriter pdf("C:/Users/Syrin/Desktop/QT/FicheDesEmployés.pdf");
    QPainter painter(&pdf);
    int i = 4000;

    QImage img("C:/Users/Syrin/Desktop/QT/Smart Airport.png");
               Q_ASSERT(!img.isNull());
               painter.drawImage(QRect(200, 200, 2000, 2000), img);

                    painter.setPen(Qt::darkBlue);
                    painter.setFont(QFont("euphemia", 40));
                    painter.drawText(2200,1500,"Fiche Des Employés");
                    painter.setPen(Qt::black);
                    painter.setFont(QFont("calibri", 20));
                   // painter.drawRect(100,100,7300,2600);
                    painter.drawRect(0,3000,9600,500);
                    painter.setFont(QFont("consolas", 9));
                    painter.drawText(200,3300,"ID:");
                    painter.drawText(1300,3300,"NOM:");
                    painter.drawText(2400,3300,"PRENOM:");
                    painter.drawText(3500,3300,"ADRESSE:");
                    painter.drawText(4600,3300,"TELEPHONE:");
                    painter.drawText(5700,3300,"E_MAIL:");
                    painter.drawText(7200,3300,"DATE_EMBAUCHE:");
                    QSqlQuery query;
                    query.prepare("select * from employes");
                    query.exec();
                    while (query.next())
                    {
                        painter.drawText(200,i,query.value(0).toString());
                        painter.drawText(1300,i,query.value(1).toString());
                        painter.drawText(2400,i,query.value(2).toString());
                        painter.drawText(3500,i,query.value(3).toString());
                        painter.drawText(4600,i,query.value(4).toString());
                        painter.drawText(5700,i,query.value(5).toString());
                        painter.drawText(7200,i,query.value(6).toString());
                       i = i + 600;
                    }
                    if(painter.end())
                    {
                        QMessageBox::information(nullptr, QObject::tr("FICHE EMPLOYEE"),
                                                 QObject::tr("Fichier employee Genere.\n"
                                                             "Click Ok to exit."), QMessageBox::Ok);
                    }
           }




/*
{
    c= new camera();
       c->show();
}
*/

void MainWindow::on_actionOpen_triggered()
{       //pour videoplayer
    player=new QMediaPlayer(this);
    player->setVideoOutput(vw);
    this->setCentralWidget(vw);

    QString filename=QFileDialog::getOpenFileName(this,"Open a file","","(*.mpg *.mp4)");
    on_actionStop_triggered();
    player->setMedia(QUrl::fromLocalFile(filename));
    on_actionPlay_triggered();
}

void MainWindow::on_actionPlay_triggered()
{
    player->play();
    ui->statusBar->showMessage("Playing");
}

void MainWindow::on_actionStop_triggered()
{
    player->stop();
    ui->statusBar->showMessage("Stopped");
}
