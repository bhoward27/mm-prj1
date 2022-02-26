#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "wavwindow.h"
#include "pngwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_openWavButton_clicked();
    void on_openPngButton_clicked();

private:
    Ui::MainWindow *ui;
    WavWindow* wav_window;
    PNGWindow* png_window;
};
#endif // MAINWINDOW_H
