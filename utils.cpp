#include "utils.h"
#include <QtCharts/QChart>
#include <QtCharts/QChartView>

using std::unique_ptr;
using std::shared_ptr;
using std::make_shared;

void show_chart(
        unique_ptr<QMainWindow>& window,
        shared_ptr<QChartView>& chartView,
        QLineSeries* series, QString title,
        int x, int y
) {
    QChart* chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle(title);

    chartView = shared_ptr<QChartView>(new QChartView(chart));
    chartView->setRenderHint(QPainter::Antialiasing);

    window = unique_ptr<QMainWindow>(new QMainWindow);
    window->setCentralWidget(chartView.get());
    window->setGeometry(x, y, 600, 600);
    window->show();
}
