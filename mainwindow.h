#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCoreApplication>
#include <QMatrix>
#include <QPixmap>
#include <QBitmap>
#include <QImage>
#include <QColor>
#include <QFile>
#include <QCoreApplication>
#include <QTextStream>
#include <QString>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_btn_selectfile_clicked();

    void on_btn_convert_clicked();

    void on_rbtn_sinf_clicked();

    void on_rbtn_none_clicked();

    void on_rbtn_semicol_clicked();

private:
    Ui::MainWindow *ui;
    QString filename;
};

#endif // MAINWINDOW_H
