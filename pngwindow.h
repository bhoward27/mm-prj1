#ifndef PNGWINDOW_H
#define PNGWINDOW_H

#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <array>
#include <memory>

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
    std::unique_ptr<QMainWindow> red_hist_window, green_hist_window, blue_hist_window;
    std::unique_ptr<QChartView> red_hist_chartView, blue_hist_chartView, green_hist_chartView;
    std::unique_ptr<QChart> red_chart, blue_chart, green_chart;
    std::unique_ptr<QLineSeries> red_freq_series, green_freq_series, blue_freq_series;

    void plot_freq_not_histogram(
            QColor line_colour,
            std::unique_ptr<QMainWindow>& window,
            std::unique_ptr<QChartView>& chartView,
            std::unique_ptr<QChart>& chart,
            std::unique_ptr<QLineSeries>& freq_series,
            const std::array<quint64, FREQ_LEN>& colour_freqs,
            QString title, int x, int y
    );
    int dither(int a, int b);

private slots:
    void on_selectFileButton_clicked();
};

#endif // PNGWINDOW_H
