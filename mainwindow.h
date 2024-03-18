#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "employes.h"
#include <QMediaPlayer>
#include <QVideoWidget>
#include "camera.h"
#include<QFileDialog>
#include <QProgressBar>
#include<QSlider>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_modifier_clicked();

    void on_pb_load_name_clicked();

    void on_pb_search_clicked();

    void on_pb_sort_clicked();

    void on_pb_pdf_clicked();
    void on_camera_clicked();






    void on_actionOpen_triggered();

    void on_actionPlay_triggered();

    void on_actionStop_triggered();

private:
    Ui::MainWindow *ui;
    Employes Em;
    QMediaPlayer* player;
    QVideoWidget* vw;
    QProgressBar* bar;
    QSlider* slider;
     camera *c;
};

#endif // MAINWINDOW_H
