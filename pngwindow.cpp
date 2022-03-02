#include "pngwindow.h"
#include "ui_pngwindow.h"
#include "utils.h"
#include <QFileDialog>
#include <QImage>
#include <iostream>

using std::cout;
using std::endl;
using std::vector;
using std::map;
using std::sort;
using std::array;

PNGWindow::PNGWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PNGWindow)
{
    ui->setupUi(this);
    red_hist_window = blue_hist_window = green_hist_window = nullptr;
}

PNGWindow::~PNGWindow()
{
    delete ui;
}

void PNGWindow::on_selectFileButton_clicked() {
    QString file_name = QFileDialog::getOpenFileName(this, "Open the file");
    QImage* img = new QImage(file_name);
    if (img->isNull()) {
        // TODO: Use messagebox
        cout << "img is null." << endl;
        return;
    }
    // TODO: Check the format using img->format().

    array<quint64, FREQ_LEN> red_freqs = {0};
    array<quint64, FREQ_LEN> green_freqs = {0};
    array<quint64, FREQ_LEN> blue_freqs = {0};
    auto height = img->height();
    auto width = img->width();
    for (int y = 0; y < height; ++y) {
        QRgb *line = reinterpret_cast<QRgb*>(img->scanLine(y));
        for (int x = 0; x < width; ++x) {
            QRgb &rgb = line[x];
            red_freqs[qRed(rgb)]++;
            green_freqs[qGreen(rgb)]++;
            blue_freqs[qBlue(rgb)]++;

            // TODO: While you're here, do some dithering stuff.
        }
    }

    plot_histogram(QColor("red"), red_hist_window, red_freqs, "Red Histogram", 0, 0);
    plot_histogram(QColor("green"), green_hist_window, green_freqs, "Green Histogram", 600, 0);
    plot_histogram(QColor("blue"), blue_hist_window, blue_freqs, "Blue Histogram", 300, 600);
}

void PNGWindow::plot_histogram(QColor line_colour, QMainWindow* window, const array<quint64, FREQ_LEN>& colour_freqs, QString title, int x, int y) {
    QLineSeries* freq_series = new QLineSeries();
    freq_series->setColor(line_colour);
    for (int i = 0; i < FREQ_LEN; i++) {
        freq_series->append(i, colour_freqs[i]);
    }
    show_chart(window, freq_series, title, x, y);
}
