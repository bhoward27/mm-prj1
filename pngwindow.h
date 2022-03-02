#ifndef PNGWINDOW_H
#define PNGWINDOW_H

#include <QMainWindow>
#include <QtCharts/QChartView>
#include <array>

const int FREQ_LEN = 256;

namespace Ui {
class PNGWindow;
}

class PNGWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PNGWindow(QWidget *parent = nullptr);
    ~PNGWindow();

private:
    Ui::PNGWindow *ui;
    QMainWindow* red_hist_window;
    QMainWindow* green_hist_window;
    QMainWindow* blue_hist_window;
    QChartView* red_hist_chartView;
    QChartView* green_hist_chartView;
    QChartView* blue_hist_chartView;

    void plot_freq_not_histogram(QColor line_colour, QMainWindow*& window, QChartView*& chartView, const std::array<quint64, FREQ_LEN>& colour_freqs, QString title, int x, int y);
    int dither(int a, int b);

private slots:
    void on_selectFileButton_clicked();
};

#endif // PNGWINDOW_H
