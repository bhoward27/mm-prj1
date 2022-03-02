#include "utils.h"
#include <QtCharts/QChart>
#include <QtCharts/QChartView>

void show_chart(QMainWindow*& window, QChartView*& chartView, QLineSeries* series, QString title, int x, int y) {
    QChart* chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle(title);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    window = new QMainWindow();
    window->setCentralWidget(chartView);
    window->setGeometry(x, y, 600, 600);
    window->show();
}
