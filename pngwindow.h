#ifndef PNGWINDOW_H
#define PNGWINDOW_H

#include <QMainWindow>
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

    void plot_histogram(QColor line_colour, QMainWindow* window, const std::array<quint64, FREQ_LEN>& colour_freqs, QString title, int x, int y);

private slots:
    void on_selectFileButton_clicked();
};

#endif // PNGWINDOW_H
