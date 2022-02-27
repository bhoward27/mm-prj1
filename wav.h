#ifndef WAV_H
#define WAV_H

#include <QtGlobal>
#include <QFile>

const quint16 LPCM = 1;

enum class WAVReadResult {
    not_riff,
    not_wav,
    not_fmt,
    not_lpcm,
    not_mono_or_stereo,
    not_data,
    ok
};

class WAV {
    public:
        quint16 num_channels;
        quint32 sample_rate;
        quint32 byte_rate;
        quint16 block_align;
        quint16 bits_per_sample;
        quint32 data_size;
        char* bytes;

        WAV();
        ~WAV();
        WAVReadResult read(QFile& open_file);
};

#endif // WAV_H
