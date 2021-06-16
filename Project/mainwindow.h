#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <processor.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_calcButton_clicked();
    void on_saveButton_clicked();

    void make_plot();
private:
    Ui::MainWindow *ui;
    Processor * processor;
    bool check_number(QString str);
};
#endif // MAINWINDOW_H
