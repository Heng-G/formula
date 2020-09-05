#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QSplineSeries>
#include <QScatterSeries>
#include <QChart>
#include <QChartView>
#include <QTimerEvent>

#include <QValueAxis>

#include <QDialog>

#include <plot.h>
using namespace QtCharts;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Ui::MainWindow *ui;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    plot p;

    double hz;
    bool stop_flag = 1 ;
    bool adjust_flag = 0;
    double lambda;
    double h;
    double h_min = 0, h_max = 0;
    double t = 0;
    int c = 0;
    int timerId;
    int maxSize = 51;

    QList<double> h_list;
    QList<double> lambda_list;

    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;

private slots:
    void on_stop_clicked();

    void on_start_clicked();

    void on_restart_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_verticalSlider_valueChanged(int value);

    void on_adjust_clicked(bool checked);

    void on_export_2_clicked();

    void on_gird_clicked(bool checked);

private:

};
#endif // MAINWINDOW_H
