#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    processor= new Processor;
}

MainWindow::~MainWindow()
{
    delete processor;
    delete ui;
}

bool MainWindow::check_number(QString str){ //helper function
    for (int i = 0; i < str.length(); i++)
    if (str[i].isDigit() == false)
       return false;
    return true;
}

void MainWindow::on_calcButton_clicked()
{
    QString read_n=ui->numberEdit->text();
    if(check_number(read_n) && read_n.toInt()!=0){
        ui->saveButton->setEnabled(false);
        processor->process(read_n.toInt());
        make_plot();
        ui->saveButton->setEnabled(true);
    }else{
        QMessageBox::information(this,tr("Unable to calculate the result"),tr("The input was incorrect"));
        return;
    }
}


void MainWindow::on_saveButton_clicked()
{
    QString file_name=QFileDialog::getSaveFileName(this,
        tr("Save results to file"),"",
        tr("Text file (*.txt);;All files (*)"));

    if(file_name.isEmpty()) return;
    else{
        QFile file(file_name);
        if(!file.open(QIODevice::WriteOnly)){
            QMessageBox::information(this,tr("Unable to save file"),file.errorString());
            return;
        }

        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_5_9);

        double step=2.0/1000;
        for(int i=0;i<1000;i++){
            double y=processor->calculate_result(step*i);
            out<<QString::number(step*i,'f',5)<<","<<QString::number(y,'f',5)<<"\n";
        }
    }
}

void MainWindow::make_plot(){
    double step=2.0/1000;
    QVector<double> x(1000),y(1000);
    for(int i=0;i<1000;i++){
        x[i]=step*i;
        y[i]=processor->calculate_result(step*i);
    }
    ui->plot->addGraph();
    ui->plot->graph(0)->setData(x,y);

    ui->plot->xAxis->setLabel("X");
    ui->plot->yAxis->setLabel("Y");

    ui->plot->xAxis->setRange(0,2);
    ui->plot->yAxis->setRange(-30,30);

    ui->plot->replot();
}

