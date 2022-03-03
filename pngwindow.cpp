#include "pngwindow.h"
#include "ui_pngwindow.h"
#include "utils.h"
#include <QFileDialog>
#include <QImage>
#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::vector;
using std::map;
using std::sort;
using std::array;
using std::unique_ptr;

const int N = 4;
// N x N dither matrix.
// TODO: Try with different dither matrix (e.g., Floyd-Steinberg)
const int D[N][N] = {
    {0, 8, 2, 10},
    {12, 4, 14, 6},
    {3, 11, 1, 9},
    {15, 7, 13, 5}
};

PNGWindow::PNGWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PNGWindow)
{
    ui->setupUi(this);
}

PNGWindow::~PNGWindow()
{
    delete ui;
}

void PNGWindow::on_selectFileButton_clicked() {
    QString file_name = QFileDialog::getOpenFileName(this, "Open the file");
    unique_ptr<QImage> og_img(new QImage(file_name));
    if (og_img->isNull()) {
        // TODO: Use messagebox
        cout << "img is null." << endl;
        return;
    }
    // TODO: Check the format using img->format().

    array<quint64, FREQ_LEN> red_freqs = {0};
    array<quint64, FREQ_LEN> green_freqs = {0};
    array<quint64, FREQ_LEN> blue_freqs = {0};
    auto height = og_img->height();
    auto width = og_img->width();

    // TODO: Use 2D arrays to be more efficient.
    // vector<vector<int>> reds(height), greens(height), blues(height);
    unique_ptr<QImage> dither_img(new QImage(og_img->size(), QImage::Format_RGB32));
    for (int y = 0; y < height; ++y) {
        QRgb *line = reinterpret_cast<QRgb*>(og_img->scanLine(y));
        for (int x = 0; x < width; ++x) {
            QRgb &rgb = line[x];
            auto red = qRed(rgb);
            auto green = qGreen(rgb);
            auto blue = qBlue(rgb);

            // For histograms.
            red_freqs[red]++;
            green_freqs[green]++;
            blue_freqs[blue]++;

            // Dither for each channel.
            int d = D[y % N][x % N];
            auto point = QPoint(x, y);
            auto colour = QColor(dither(red, d), dither(green, d), dither(blue, d));
            // NOTE: setPixelColor is NOT an efficient function. Documentation reccommends other ways.
            dither_img->setPixelColor(point, colour);
//            reds[y].push_back(dither(red, d));
//            greens[y].push_back(dither(green, d));
//            blues[y].push_back(dither(blue, d));
        }
    }

    // Display original image.
    *og_img = og_img->scaled(ui->labelOriginalImage->width(), ui->labelOriginalImage->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    unique_ptr<QPixmap> og_pm(new QPixmap());
    *og_pm = og_pm->fromImage(*og_img);
    ui->labelOriginalImage->setPixmap(*og_pm);

    // Display dither image.
    *dither_img = dither_img->scaled(ui->labelDitherImage->width(), ui->labelDitherImage->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    unique_ptr<QPixmap> dither_pm(new QPixmap());
    *dither_pm = dither_pm->fromImage(*dither_img);
    ui->labelDitherImage->setPixmap(*dither_pm);

    plot_freq_not_histogram(QColor("red"), red_hist_window, red_hist_chartView, red_chart, red_freq_series, red_freqs, "Red Histogram", 0, 0);
    plot_freq_not_histogram(QColor("green"), green_hist_window, green_hist_chartView, green_chart, green_freq_series, green_freqs, "Green Histogram", 600, 0);
    plot_freq_not_histogram(QColor("blue"), blue_hist_window, blue_hist_chartView, blue_chart, blue_freq_series, blue_freqs, "Blue Histogram", 300, 600);

    // Display dithered image.

}

// TODO: As currently implemented this is technically NOT a histogram, but merely a frequency plot.
// Therefore, you should modify this function (and then name it plot_histogram).
// Histogram is defined as follows:
// "a diagram consisting of rectangles whose area is proportional to the frequency of a variable and
// whose width is equal to the class interval."
void PNGWindow::plot_freq_not_histogram(
        QColor line_colour,
        unique_ptr<QMainWindow>& window,
        unique_ptr<QChartView>& chartView,
        unique_ptr<QChart>& chart,
        unique_ptr<QLineSeries>& freq_series,
        const array<quint64, FREQ_LEN>& colour_freqs,
        QString title, int x, int y
) {
    freq_series = unique_ptr<QLineSeries>(new QLineSeries());
    freq_series->setColor(line_colour);
    for (int i = 0; i < FREQ_LEN; i++) {
        freq_series->append(i, colour_freqs[i]);
    }
    show_chart(window, chartView, chart, freq_series.get(), title, x, y);
}

// TODO: This could be a macro.
int PNGWindow::dither(int a, int b) {
    return (a > N * N * b) ? 255 : 0;
}
