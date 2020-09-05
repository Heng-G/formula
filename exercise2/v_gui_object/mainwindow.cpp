#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimerEvent>

#include <QValueAxis>

#include <QProcess>
#include <QDir>

#include <QDebug>
#include <QDialog>
#include <QString>

#include <QDateTime>
#include <QFileDialog>
#include <QIODevice>

extern QString e_name;
QString result;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    p.frame_init(0,2.5,-500,500,"show","time(s)","h(t)");

    hz = 20; //set sampling rate

    timerId = startTimer(1000/hz);  // set timer
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::timerEvent(QTimerEvent *event) {

if (event->timerId() == timerId) {
    //time is up
    if (stop_flag == 0){

        //calculate the lambda(t) and h(lambda)
        lambda = 5 *sin(2*M_PI * t);
        h = 3 * M_PI * exp(-lambda);

       //produce CSV data
        QDateTime current_date_time =QDateTime::currentDateTime();
        QString current_date =current_date_time.toString("MM-dd-yyyy");
        QString current_time =current_date_time.toString("hh:mm:ss");
        result.append(QString::number(h) +"," +QString::number(lambda) + "," + QString::number(t) + ","+ current_date + "," + current_time + "," + e_name + ",\n");

        // record the maximum and minimum of h
        if (h > h_max) h_max = h;
        if (h< h_min) h_min = h;

        // store every h value into list (in order to plot them)
        h_list << h;
        lambda_list << lambda;


        // maxSize = the amount of plotting point that is allowed to show in the chart
        // if the size of h_list is larger than maxSize, the first data in h_list will be removed
        // the result of that is it looks like the curve move forward as the time go
        while (h_list.size() > maxSize) h_list.removeFirst();

        // clear the point and curve ploted previously
        p.plot_clear();


         // in this case, the size is 51, so it will run 51 times to plot 51 points and curve between them
         // to make it looks like the curve is moving

         for (int i = 0; i < h_list.size(); i++) {
             p.plot_curve(i * 1/hz + (t-(1/hz)*(maxSize-1)) * (t>(1/hz)*(maxSize-1)),h_list.at(i));
             p.plot_point(i * 1/hz + (t-(1/hz)*(maxSize-1)) * (t>(1/hz)*(maxSize-1)),h_list.at(i));
       }


         if (t > (1/hz)*(maxSize-1)) p.setXrange(t-(1/hz)*(maxSize-1),t);

         // automaically adjust the Y axis range, according to the maximum and minimun of h
         if (adjust_flag == 1) p.setYrange(h_min-100, h_max+100);


         c = c+1;   //circle_count
         t = c * 1/hz; // curent time (s)

    }
}

}



void MainWindow::on_stop_clicked()
{
    stop_flag = 1;
}

void MainWindow::on_start_clicked()
{
    ui->label->setText(e_name);
    stop_flag = 0;
}

void MainWindow::on_gird_clicked(bool checked)
{
 if (checked) p.show_grid(true);
 else p.show_grid(false);
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
  //  I temperately have no idea how to zoom X aixs
}

void MainWindow::on_verticalSlider_valueChanged(int value)
{
   p.zoom_y(value-50);
}


void MainWindow::on_adjust_clicked(bool checked)
{
    if (checked) adjust_flag = 1;
    else adjust_flag = 0;
}

void MainWindow::on_export_2_clicked()
{
    //export the csv file to anywhere

       // get the path to save file
       QString fileName = QFileDialog::getSaveFileName(this, tr("Save as"), qApp->applicationDirPath (), tr("Files (*.csv)"));
       if (fileName.isEmpty())return;

       //open csv file to create one
       QFile file(fileName);
       if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;

       // output the data to the file created
       QTextStream out(&file);
       out << "h(t),lambda(t),t,date,time,edit field content\n";
       out << result;

       file.close();
}

void MainWindow::on_restart_clicked()
{
    // this is used to reboot the programme
    QString program = QApplication::applicationFilePath();
    QStringList arguments = QApplication::arguments();
    QString workingDirectory = QDir::currentPath();
    QProcess::startDetached(program, arguments, workingDirectory);
    QApplication::exit();
}


