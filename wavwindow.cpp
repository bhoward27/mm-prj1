#include "wavwindow.h"
#include "ui_wavwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QDataStream>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

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

    // Extract the RIFF chunk descriptor.
    string riff = "";
    char ch;
    for (int i = 0; i < 4; i++) {
        // TODO: Error handling/checking.
        in >> ch;
        riff += ch;
    }
    cout << "riff == " << riff << endl;

    in.setByteOrder(QDataStream::LittleEndian);
    quint32 file_size;
    in >> file_size;
    cout << "file_size == " << file_size << endl;
    cout << "file_size in KiB == " << (file_size >> 10) << endl;

    in.setByteOrder(QDataStream::BigEndian);
    string wave = "";
    for (int i = 0; i < 4; i++) {
        in >> ch;
        wave += ch;
    }
    cout << "wave == " << wave << endl;

    // Extract the "fmt " subchunk.


    file.close();
}
