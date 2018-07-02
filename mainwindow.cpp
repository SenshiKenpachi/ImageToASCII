#include "mainwindow.h"
#include "ui_mainwindow.h"

//========== KONSTRUKTOR ============================================================================================================================================================
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//========== SELECT FILE ============================================================================================================================================================
void MainWindow::on_btn_selectfile_clicked()
{
    filename = QFileDialog::getOpenFileName(this,tr("Select Image"),"","");

    ui->lbl_file_out->setText(filename);

    QString str = ui->lbl_file_out->text();

    if(ui->rbtn_sinf->isChecked())
    {
        str.replace(QString(".bmp"), QString(".SINF"));
        str.replace(QString(".jpg"), QString(".SINF"));
        str.replace(QString(".png"), QString(".SINF"));
    } else
    {
        str.replace(QString(".bmp"), QString(".txt"));
        str.replace(QString(".jpg"), QString(".txt"));
        str.replace(QString(".png"), QString(".txt"));
    }

    ui->lbl_file_output->setText(str);

}

//========== CONVERT ============================================================================================================================================================
void MainWindow::on_btn_convert_clicked()
{
    if(filename.isEmpty())
        return;

    QImage myimage = QImage(ui->lbl_file_out->text());

    int width = myimage.width();
    int height = myimage.height();

    QFile file(ui->lbl_file_output->text());

    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);


    if(ui->rbtn_sinf->isChecked())
    {
        out << "DEVICE:177870140A1";
        out << '\n';
        out << "LOT:E17340.17";
        out << '\n';
        out << "WAFER:E17340W05PA2";
        out << '\n';
        out << "FNLOC:180";
        out << '\n';
        out << "ROWCT:999";
        out << '\n';
        out << "COLCT:999";
        out << '\n';
        out << "BCEQU:00";
        out << '\n';
        out << "REFPX:0";
        out << '\n';
        out << "REFPY:0";
        out << '\n';
        out << "DUTMS:mm";
        out << '\n';
        out << "XDIES:0";
        out << '\n';
        out << "YDIES:0";
        out << '\n';
    }




    for(int j = 0; j < height; j++)
    {
        if(ui->rbtn_sinf->isChecked())
            out << "RowData:";

      for(int i = 0; i < width; i++)
      {
        int pixel = qGray(myimage.pixel(i,j));


        if (pixel <= 128)
            pixel = 1;
        else if (pixel >= 128)
            pixel = 0;


        QString text = QString::number(pixel);


        if(ui->rbtn_none->isChecked())
            out << text;

        if(ui->rbtn_semicol->isChecked())
            out << text << ";";

        if(ui->rbtn_sinf->isChecked())
            out << "0" << text << " ";

      }

      out << '\n';

    }

    QMessageBox msgBox;
    msgBox.setText("   Done.      ");
    msgBox.exec();

}

//========== RADIO BUTTONS ============================================================================================================================================================
void MainWindow::on_rbtn_sinf_clicked()
{
    QString str = ui->lbl_file_output->text();

    str.replace(QString(".txt"), QString(".SINF"));

    ui->lbl_file_output->setText(str);
}

void MainWindow::on_rbtn_none_clicked()
{
    QString str = ui->lbl_file_output->text();

    str.replace(QString(".SINF"), QString(".txt"));

    ui->lbl_file_output->setText(str);
}

void MainWindow::on_rbtn_semicol_clicked()
{
    QString  str = ui->lbl_file_output->text();

    str.replace(QString(".SINF"), QString(".txt"));

    ui->lbl_file_output->setText(str);
}
