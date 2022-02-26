#ifndef WAVWINDOW_H
#define WAVWINDOW_H

#include <QMainWindow>

namespace Ui {
class WavReader;
}

class WavWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit WavWindow(QWidget *parent = nullptr);
    ~WavWindow();

private:
    Ui::WavReader *ui;
};

#endif // WAVWINDOW_H
