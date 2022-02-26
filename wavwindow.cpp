#include "wavwindow.h"
#include "ui_wavwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QDataStream>
#include <iostream>

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
    setWindowTitle(file_name);

    // Read the file's data into memory.
    QDataStream in(&file);

    // temp code
    qint32 x = 0;
    in >> x;
    std::cout << x << std::endl;
}
