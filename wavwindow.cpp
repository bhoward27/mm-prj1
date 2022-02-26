#include "wavwindow.h"
#include "ui_wavreader.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

WavWindow::WavWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WavReader)
{
    ui->setupUi(this);
}

WavWindow::~WavWindow()
{
    delete ui;
}
