#include "wav.h"
#include <QDataStream>
#include <string>
#include <stdexcept>

using std::string;

WAV::WAV() {
    num_channels = sample_rate = byte_rate = block_align = bits_per_sample = data_size = 0;
    bytes = nullptr;
}

WAV::~WAV() {
    if (bytes) {
        delete[] bytes;
    }
}

WAVReadResult WAV::read(QFile& open_file) {
    // Read the file's data into memory.
    // open_file is expected to already have been opened for reading.
    QDataStream in(&open_file);

    // Extract the RIFF chunk descriptor.
    string chunk_id = "";
    char ch;
    for (int i = 0; i < 4; i++) {
        // TODO: Error handling/checking.
        in >> ch;
        chunk_id += ch;
    }
    if (chunk_id != "RIFF") {
        return WAVReadResult::not_riff;
    }

    // in.setByteOrder(QDataStream::LittleEndian);
    quint32 chunk_size; // This won't be used. Just eat the bytes to get to next spot.
    in >> chunk_size;

    // in.setByteOrder(QDataStream::BigEndian);
    string format = "";
    for (int i = 0; i < 4; i++) {
        in >> ch;
        format += ch;
    }
    if (format != "WAVE") {
        return WAVReadResult::not_wav;
    }

    // Extract the "fmt " subchunk.
    string subchunk1_id = "";
    for (int i = 0; i < 4; i++) {
        in >> ch;
        subchunk1_id += ch;
    }
    if (subchunk1_id != "fmt ") {
        return WAVReadResult::not_fmt;
    }

    in.setByteOrder(QDataStream::LittleEndian);
    quint32 subchunk1_size;
    in >> subchunk1_size; // Expect 16.

    quint16 audio_format;
    in >> audio_format;
    if (audio_format != LPCM) {
        return WAVReadResult::not_lpcm;
    }

    in >> num_channels;
    if (num_channels > 2 || num_channels < 1) {
        return WAVReadResult::not_mono_or_stereo;
    }

    in >> sample_rate >> byte_rate >> block_align >> bits_per_sample;
    if (subchunk1_size > 16) {
        // Skip past these bytes by "eating" them.
        quint32 diff = 16 - subchunk1_size;
        for (quint32 i = 0; i < diff; i++) {
            in >> ch;
        }
    }

    // Extract "data" subchunk header.
    string subchunk2_id = "";
    for (int i = 0; i < 4; i++) {
        in >> ch;
        subchunk2_id += ch;
    }
    if (subchunk2_id != "data") {
        return WAVReadResult::not_data;
    }

    in >> data_size;

    bytes = new char[data_size];
    int res = in.readRawData(bytes, data_size);
    if (bytes == nullptr || res == -1) throw std::runtime_error("bytes == nullptr or res == -1");

    return WAVReadResult::ok;
}
