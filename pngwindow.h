#ifndef PNGWINDOW_H
#define PNGWINDOW_H

#include <QMainWindow>

namespace Ui {
class PNGReader;
}

class PNGWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PNGWindow(QWidget *parent = nullptr);
    ~PNGWindow();

private:
    Ui::PNGReader *ui;
};

#endif // PNGWINDOW_H
