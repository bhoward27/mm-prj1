#ifndef UTILS_H
#define UTILS_H

#include <QMainWindow>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>

void show_chart(QMainWindow*& window, QChartView*& chartView, QLineSeries* series, QString title, int x, int y);

template<class T>
void cond_free(T* ptr) {
    if (ptr) delete ptr;
}

#endif // UTILS_H
