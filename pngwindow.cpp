#include "pngwindow.h"
#include "ui_pngreader.h"

PNGWindow::PNGWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PNGReader)
{
    ui->setupUi(this);
}

PNGWindow::~PNGWindow()
{
    delete ui;
}
