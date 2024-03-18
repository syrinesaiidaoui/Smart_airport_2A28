#ifndef EMPLOYES_H
#define EMPLOYES_H
#include <QString>
#include <QSqlQueryModel>
#include<QtCharts>
#include<QChartView>
#include<QPieSeries>
#include<QPieSlice>
class Employes
{
public:
    //++++++++++ Les constructeurs ++++++++++
    Employes();
    Employes(int,QString,QString,QString,QString,QString,QString,QString,QString,QString);

    //++++++++++ Les GETTERs ++++++++++
    int getIDE();
    QString getNomE();
    QString getPrenomE();
    QString getAdresse();
    QString getTelephone();
    QString getE_mail();
    QString getDate_embauche();
    QString getSalaire();
    QString getPrime();
    QString getDesignation();

    //++++++++++ Les SETTERs ++++++++++
    void setIDE(int);
    void setNomE(QString);
    void setPenomE(QString);
    void setAdresse(QString);
    void setTelephone(QString);
    void setE_mail(QString);
    void setDate_embauche(QString);
    void setSalaire(QString);
    void setPrime(QString);
    void setDesignation(QString);

    //++++++++++ Les CRUDs ++++++++++
    bool ajouterEmployes();
    QSqlQueryModel* afficherEmployes();
    bool supprimerEmployes(int);
    bool modifierEmployes(int,QString,QString,QString,QString);

    //++++++++++ LES METIERS ++++++++++
    QSqlQueryModel* RechercheEmployes(QString);
    QSqlQueryModel *trier();
    QChartView *statistiqueEmployes();

private:
    int idE;
    QString nomE,prenomE,adresse,telephone,e_mail;
    QString date_embauche,salaire,prime,designation;
};

#endif // EMPLOYES_H
