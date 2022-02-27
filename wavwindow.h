#ifndef WAVWINDOW_H
#define WAVWINDOW_H

#include <QMainWindow>
#include "wav.h"

namespace Ui {
class WavWindow;
}

class WavWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit WavWindow(QWidget *parent = nullptr);
    ~WavWindow();

private:
    Ui::WavWindow *ui;

private slots:
    void on_selectFileButton_clicked();

private:
    template<class T>
    void plot_waveform(const T* samples, quint32 len, const WAV& wav);
};

#endif // WAVWINDOW_H
