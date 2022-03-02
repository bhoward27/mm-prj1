#ifndef UTILS_H
#define UTILS_H

#include <QMainWindow>
#include <QtCharts/QLineSeries>

void show_chart(QMainWindow* window, QLineSeries* series, QString title, int x, int y);

template<class T>
void cond_free(T* ptr);

#endif // UTILS_H
