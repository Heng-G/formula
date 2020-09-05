#include "plot.h"

#include <QChart>
#include <QChartView>
#include <QSplineSeries>
#include <QScatterSeries>

#include <QDebug>

#include <QTimerEvent>
#include <QObject>

#include <QTimer>

#include <QVBoxLayout>
#include <QWidget>
using namespace QtCharts;

extern QString result;
extern int timerId;
 plot::plot()
{

}

void plot::frame_init(double minX, double maxX, double minY, double maxY, QString title, QString x_title, QString y_title)
{

    //create qchart object
    chart = new QChart();
    chart->setTitle(title);
    chart->legend()->hide();
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->show();
    chartView->setFixedSize(800,640); //fix the window size


    //create line and point object
    splineSeries = new QSplineSeries();
    scatterSeries = new QScatterSeries();
    chart->addSeries(splineSeries);
    chart->addSeries(scatterSeries);

    //create axis object
    chart->createDefaultAxes();
    chart->axisX()->setRange(minX,maxX);
    chart->axisX()->setTitleText(x_title);
    chart->axisY()->setRange(minY, maxY);
    chart->axisY()->setTitleText(y_title);
    current_minY = minY; current_maxY = maxY;
    chart->axisX()->gridVisibleChanged(false);
    chart->axisY()->gridVisibleChanged(false);

}

void plot::plot_clear(){
splineSeries->clear();
scatterSeries->clear();
}

void plot::plot_point(double x, double y){
scatterSeries->append(x,y);
}

void plot::plot_curve(double x, double y){
splineSeries->append(x,y);
}

void plot::setXrange(double x, double y){
chart->axisX()->setRange(x,y);
}

void plot::setYrange(double x, double y){
chart->axisY()->setRange(x,y);
current_minY = x; current_maxY = y;
}

void plot::zoom_y(float value){
chart->axisY()->setRange(current_minY-value*10,current_maxY+value*10);
}

void plot::show_grid(bool visible){
    chart->axisX()->gridVisibleChanged(visible);
chart->axisY()->gridVisibleChanged(visible);
}




