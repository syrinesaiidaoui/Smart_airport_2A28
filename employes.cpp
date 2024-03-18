#include "employes.h"
#include <QSqlQuery>
#include<QDebug>
#include<QObject>

//++++++++++ Les Constructeurs ++++++++++
Employes::Employes()
{
 idE=0;prenomE="";nomE="",adresse="",telephone="",e_mail="";
 date_embauche="",salaire="",prime="",designation="";
}

Employes::Employes(int idE,QString nomE,QString prenomE,QString adresse,QString telephone,QString e_mail,QString date_embauche,QString salaire,QString prime,QString designation)
{
    this->idE=idE;
    this->nomE=nomE;
    this->prenomE=prenomE;
    this->adresse=adresse;
    this->telephone=telephone;
    this->e_mail=e_mail;
    this->date_embauche=date_embauche;
    this->salaire=salaire;
    this->prime=prime;
    this->designation=designation;
}

//+++++++++++++++++++++ Les GETTERs ++++++++++++++++++++++++++++++++

int Employes::getIDE(){return idE; }
QString Employes::getNomE(){return nomE;}
QString Employes::getPrenomE(){return prenomE;}
QString Employes::getAdresse(){return adresse;}
QString Employes::getTelephone(){return telephone;}
QString Employes::getE_mail(){return e_mail;}
QString Employes::getDate_embauche(){return date_embauche;}
QString Employes::getSalaire(){return salaire;}
QString Employes::getPrime(){return prime;}
QString Employes::getDesignation(){return designation;}

//+++++++++++++++++++++++ Les SETTERs ++++++++++++++++++++++++++++++

void Employes::setIDE(int idE){this->idE=idE;}
void Employes::setNomE(QString nomE){this->nomE=nomE;}
void Employes::setPenomE(QString prenomE){this->prenomE=prenomE;}
void Employes::setAdresse(QString adresse){this->adresse=adresse;}
void Employes::setTelephone(QString telephone){this->telephone=telephone;}
void Employes::setE_mail(QString e_mail){this->e_mail=e_mail;}
void Employes::setDate_embauche(QString date_embauche){this->date_embauche=date_embauche;}
void Employes::setSalaire(QString salaire){this->salaire=salaire;}
void Employes::setPrime(QString prime){this->prime=prime;}
void Employes::setDesignation(QString designation){this->designation=designation;}

//+++++++++++++++++++++++ Les CRUDs ++++++++++++++++++++++++++++++++

bool Employes::ajouterEmployes()
{
    QSqlQuery query;
     QString idE_string=QString::number(idE);
         query.prepare("INSERT INTO EMPLOYES (idE, nomE, prenomE,adresse,telephone,e_mail,date_embauche,salaire,prime,designation) "
                       "VALUES (:idE, :nomE, :prenomE, :adresse, :telephone, :e_mail, :date_embauche, :salaire, :prime, :designation)");
         query.bindValue(":idE", idE_string);
         query.bindValue(":nomE", nomE);
         query.bindValue(":prenomE", prenomE);
         query.bindValue(":adresse", adresse);
         query.bindValue(":telephone", telephone);
         query.bindValue(":e_mail", e_mail);
         query.bindValue(":date_embauche", date_embauche);
         query.bindValue(":salaire", salaire);
         query.bindValue(":prime", prime);
         query.bindValue(":designation", designation);
         return query.exec();
}

bool Employes::supprimerEmployes(int idE)
{
    QSqlQuery query;
    query.prepare("Delete from EMPLOYES where idE=:idE ");
    query.bindValue(0,idE);

    return query.exec();
}

QSqlQueryModel * Employes::afficherEmployes()
{
   QSqlQueryModel* model=new QSqlQueryModel();
   model->setQuery("SELECT *  FROM employes");
   model->setHeaderData(0, Qt::Horizontal,QObject:: tr("Identifiant"));
   model->setHeaderData(1, Qt::Horizontal,QObject:: tr("Nom"));
   model->setHeaderData(2, Qt::Horizontal,QObject:: tr("Prenom"));
   model->setHeaderData(3, Qt::Horizontal,QObject:: tr("Adresse"));
   model->setHeaderData(4, Qt::Horizontal,QObject:: tr("Telephone"));
   model->setHeaderData(5, Qt::Horizontal,QObject:: tr("E_mail"));
   model->setHeaderData(6, Qt::Horizontal,QObject:: tr("Date_embauche"));
   model->setHeaderData(7, Qt::Horizontal,QObject:: tr("Salaire"));
   model->setHeaderData(8, Qt::Horizontal,QObject:: tr("Prime"));
   model->setHeaderData(9, Qt::Horizontal,QObject:: tr("Designation"));
return model;
}

bool Employes::modifierEmployes(int idE,QString adresse,QString telephone,QString salaire,QString prime)
{
    QSqlQuery query;
    query.prepare("update employes set adresse=:adresse,telephone=:telephone,salaire=:salaire,prime=:prime where idE=:idE");
    query.bindValue(":idE",idE);
    query.bindValue(":adresse",adresse);
    query.bindValue(":telephone",telephone);
    query.bindValue(":salaire",salaire);
    query.bindValue(":prime",prime);
    return query.exec();
}

//+++++++++++++++++++++ Les Métiers ++++++++++++++++++++++++++++++

QSqlQueryModel *Employes::RechercheEmployes(QString a)
{
    QSqlQueryModel * model= new QSqlQueryModel();
       model->setQuery("select * from employes where nomE like'%"+a+"%' ");
       model->setHeaderData(0, Qt::Horizontal,QObject:: tr("Identifiant"));
       model->setHeaderData(1, Qt::Horizontal,QObject:: tr("Nom"));
       model->setHeaderData(2, Qt::Horizontal,QObject:: tr("Prenom"));
       model->setHeaderData(3, Qt::Horizontal,QObject:: tr("Adresse"));
       model->setHeaderData(4, Qt::Horizontal,QObject:: tr("Telephone"));
       model->setHeaderData(5, Qt::Horizontal,QObject:: tr("E_mail"));
       model->setHeaderData(6, Qt::Horizontal,QObject:: tr("Date_embauche"));
       model->setHeaderData(7, Qt::Horizontal,QObject:: tr("Salaire"));
       model->setHeaderData(8, Qt::Horizontal,QObject:: tr("Prime"));
       model->setHeaderData(9, Qt::Horizontal,QObject:: tr("Designation"));
           return model;
}

QSqlQueryModel *Employes::trier()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from employes order by nomE asc");
    model->setHeaderData(0, Qt::Horizontal,QObject:: tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal,QObject:: tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal,QObject:: tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal,QObject:: tr("Adresse"));
    model->setHeaderData(4, Qt::Horizontal,QObject:: tr("Telephone"));
    model->setHeaderData(5, Qt::Horizontal,QObject:: tr("E_mail"));
    model->setHeaderData(6, Qt::Horizontal,QObject:: tr("Date_embauche"));
    model->setHeaderData(7, Qt::Horizontal,QObject:: tr("Salaire"));
    model->setHeaderData(8, Qt::Horizontal,QObject:: tr("Prime"));
    model->setHeaderData(9, Qt::Horizontal,QObject:: tr("Designation"));
        return model;

}

QChartView* Employes::statistiqueEmployes()
{
        int row_count = 0;
        int row_count1 = 0;

                QSqlQuery query,query1;

                query.prepare("SELECT * FROM employes where SALAIRE>=2000");
                query.exec();
                while(query.next())
                    row_count++;

                query1.prepare("SELECT * FROM employes where SALAIRE<2000");
                query1.exec();
                while(query1.next())
                    row_count1++;

               // qDebug()<<"row1="<<row_count<<row_count1;

        QPieSeries *series = new QPieSeries();
        series->append("Des Employes ayant un salaire>=2000 dt", row_count);
        series->append("Des Employes ayant un salaire<2000 dt", row_count1);

        //pour slider les employes ayant un salaire>=2000dt
        QPieSlice *slice= series->slices().at(0);
        slice->setExploded(true);
        slice->setLabelVisible(true);
        slice->setPen((QPen(Qt::white)));

        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("STATISTIQUE DES SALAIRES");
        chart->legend()->setAlignment(Qt::AlignRight);
        chart->legend()->setBackgroundVisible(true);
        chart->legend()->setBrush(QBrush(QColor(128, 128, 128, 128)));
        chart->legend()->setPen(QPen(QColor(192, 192, 192, 192)));
        series->setLabelsVisible();

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        return chartView;
}
