#ifndef WAVWINDOW_H
#define WAVWINDOW_H

#include <QMainWindow>

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
};

#endif // WAVWINDOW_H
