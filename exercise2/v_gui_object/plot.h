#ifndef PLOT_H
#define PLOT_H
#include <QChart>
#include <QChartView>
#include <QSplineSeries>
#include <QScatterSeries>
#include <QTimerEvent>
#include <QTimer>

using namespace QtCharts;
class plot
{
public:
    plot();


    void frame_init(double minX, double maxX, double minY, double maxY, QString title, QString x_title, QString y_title);

    void plot_point(double x, double y);
    void plot_curve(double x, double y);

    void setXrange(double x, double y);

    void setYrange(double x, double y);
    void zoom_y(float value);


    void show_grid(bool visible);
    void plot_clear();



private:
    float current_minY, current_maxY;

    QSplineSeries *splineSeries;
    QScatterSeries *scatterSeries;
    QChart *chart;
    QChartView *chartView;

};

#endif // PLOT_H
