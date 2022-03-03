#include "wavwindow.h"
#include "ui_wavwindow.h"
#include "utils.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QDataStream>
#include <QtCharts/QChartView>
#include <QPoint>
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

WavWindow::WavWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WavWindow)
{
    ui->setupUi(this);
}

WavWindow::~WavWindow()
{
    delete ui;
}

void WavWindow::on_selectFileButton_clicked() {
    // Get the file name.
    QString file_name = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(file_name);

    // Open the .wav file.
    // TODO: Only allow the user to select .wav files.
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Warning", "Could not open file: " + file.errorString());
    }

    WAV wav = WAV();
    WAVReadResult res = wav.read(file);
    file.close();
    switch (res) {
        case WAVReadResult::ok:
            // Do nothing.
            break;
        default:
            // TODO: Display error message.
            cout << "Error." << endl;
            break;
    }
    switch (wav.bits_per_sample) {
        // TODO: The casting of wav.bytes probably wouldn't "work" on a Big-Endian machine.
        case 8:
            plot_waveform((quint8*) wav.bytes, wav.data_size, wav);
            break;
        case 16:
            plot_waveform((qint16*) wav.bytes, wav.data_size/2, wav);
            break;
        default:
            // Throw error?
            cout << "bits per sample == " << wav.bits_per_sample << endl;
            break;
    }
}

template<class T>
void WavWindow::plot_waveform(const T* samples, quint32 len, const WAV& wav) {
    // TODO: Show total number of samples and sampling rate.
    // TODO: Simply plot the samples as lines instead of doing interpolation between points.
    // TODO: Use "by value" QLineSeries instead of pointer (it will allocate its own data like vector).
    QLineSeries* chan1 = nullptr;
    QLineSeries* chan2 = nullptr;
    QString title = "";
    title += QString("TOTAL Number of Samples = ") + QString::number(len);
    title += QString(" - Sampling Rate = ") + QString::number(wav.sample_rate) + QString(" Hz");
    switch (wav.num_channels) {
        case 1:
            chan1 = new QLineSeries();
            for (quint32 i = 0; i < len; i++) {
                chan1->append(i, samples[i]);
            }
            title = QString("Audio - ") + title;
            show_chart(chan1_window, chan1_chartView, chan1, title, 300, 0);
            break;
        case 2:
            chan1 = new QLineSeries();
            chan2 = new QLineSeries();
            for (quint32 i = 0; i < len - 1; i += 2) {
                chan1->append(i/2, samples[i]);
                chan2->append(i/2, samples[i + 1]);
            }
            show_chart(chan1_window, chan1_chartView, chan1, QString("Left Channel - ") + title, 0, 0);
            show_chart(chan2_window, chan2_chartView, chan2, QString("Right Channel - ") + title, 600, 0);
            break;
        default:
            // Do nothing.
            break;
    }
}
