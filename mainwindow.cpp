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


void MainWindow::on_btn_selectfile_clicked()
{
    filename = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://Users//Master-2014//Desktop//",
                ""
                );

    ui->lbl_file_out->setText(filename);

    QString str;

    str = ui->lbl_file_out->text();

    str.replace(QString(".bmp"), QString(".txt"));
    str.replace(QString(".jpg"), QString(".txt"));
    str.replace(QString(".png"), QString(".txt"));

    ui->lbl_file_output->setText(str);

}

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

    ui->lbl_status_out->setText("--done--");


}
