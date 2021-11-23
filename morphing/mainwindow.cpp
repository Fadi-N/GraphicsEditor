#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->horizontalSlider, &QSlider::valueChanged, ui->widget, &Ekran::on_horizontalSlider_valueChanged);
    connect(ui->horizontalSlider_2, &QSlider::valueChanged, ui->widget, &Ekran::on_horizontalSlider_2_valueChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

