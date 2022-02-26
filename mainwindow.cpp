#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "wavwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    wav_window = new WavWindow();
    png_window = new PNGWindow();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete wav_window;
    delete png_window;
}

void MainWindow::on_openWavButton_clicked()
{
    wav_window->show();
}

void MainWindow::on_openPngButton_clicked() {
    png_window->show();
}

