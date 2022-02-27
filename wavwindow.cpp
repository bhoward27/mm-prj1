#include "wavwindow.h"
#include "ui_wavwindow.h"
#include "wav.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QDataStream>
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
    setWindowTitle(file_name);

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
    if (wav.bits_per_sample == 16) {
        quint32 n = wav.data_size / (wav.num_channels * 2);
        qint16* samples = (qint16*) wav.bytes;
    }
}

//void WavWindow::read_test() {
//    // Read the file's data into memory.
//    QDataStream in(&file);

//    // Extract the RIFF chunk descriptor.
//    string riff = "";
//    char ch;
//    for (int i = 0; i < 4; i++) {
//        // TODO: Error handling/checking.
//        in >> ch;
//        riff += ch;
//    }
//    cout << "riff == " << riff << endl;

//    in.setByteOrder(QDataStream::LittleEndian);
//    quint32 file_size;
//    in >> file_size;
//    cout << "file_size == " << file_size << endl;
//    cout << "file_size in KiB == " << (file_size >> 10) << endl;

//    in.setByteOrder(QDataStream::BigEndian);
//    string wave = "";
//    for (int i = 0; i < 4; i++) {
//        in >> ch;
//        wave += ch;
//    }
//    cout << "wave == " << wave << endl;

//    // Extract the "fmt " subchunk.
//    string fmt = "";
//    for (int i = 0; i < 4; i++) {
//        in >> ch;
//        fmt += ch;
//    }
//    cout << "fmt == " << fmt << endl;

//    in.setByteOrder(QDataStream::LittleEndian);
//    quint32 fmt_chunk_size;
//    in >> fmt_chunk_size;
//    // Note that fmt_chunk_size is not always 16 bytes, though commonly this is the case.
//    // For example, stereo.wav has an fmt_chunk_size == 18 bytes.
//    // I will assume that if we have more than 16 bytes we can ignore the later ones.
//    // So we'll just skip ahead past the last extra bytes in the fmt sub chunk.
//    cout << "fmt_chunk_size == " << fmt_chunk_size << endl;

//    quint16 audio_format;
//    in >> audio_format;
//    // Expect 0x(00 01) for PCM.
//    // stereo.wav gives 0x(00 06).
//    // Apparently values other than 1 indicate some form of compression,
//    // which I thought we are not supposed to have to deal with for this
//    // project. Therefore, I will issue an error/reject files not conforming to this
//    // (such as stereo.wav!).
//    cout << "audio_format == " << audio_format << endl;

//    quint16 num_channels;
//    in >> num_channels; // Expect 1 or 2. > 2 should throw an error.
//    cout << "num_channels == " << num_channels << endl;

//    quint32 sample_rate;
//    in >> sample_rate;
//    cout << "sample_rate == " << sample_rate << endl;

//    quint32 byte_rate; // sample_rate * num_channels * bits_per_sample/8.
//    in >> byte_rate;
//    cout << "byte_rate == " << byte_rate << endl;

//    quint16 block_align; // number of bytes per sample including all channels.
//    in >> block_align;
//    cout << "block_align == " << block_align << endl;

//    quint16 bits_per_sample;
//    in >> bits_per_sample; // Expect 8 or 16.
//    cout << "bits_per_sample == " << bits_per_sample << endl;

//    // If not PCM, there will be some extra fmt info after this, but we
//    // do not need to concern ourselves with this for this project.

//    // Extract "data" subchunk header.
//    in.setByteOrder(QDataStream::BigEndian); // Technically not necessary since we're reading one byte at a time here.
//    string data = "";
//    for (int i = 0; i < 4; i++) {
//        in >> ch;
//        data += ch;
//    }
//    cout << "data == " << data << endl; // Expect data.

//    in.setByteOrder(QDataStream::LittleEndian);
//    quint32 data_size;
//    in >> data_size; // num_samples * num_channels * bytes_per_sample
//    cout << "data_size == " << data_size << endl;

//    // Copy the remaining bytes into an array of the appropriate size and data type.
//    char* bytes = new char[data_size];
//    in.readBytes(bytes, data_size);
//}
