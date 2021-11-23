#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->comboBox->addItem("Normal");
    ui->comboBox->addItem("Multiply");
    ui->comboBox->addItem("Lighten");
    ui->comboBox->addItem("Darken");
    ui->comboBox->addItem("Screen");

    ui->horizontalSlider->setMinimum(0);
    ui->horizontalSlider->setMaximum(100);
    ui->horizontalSlider->setValue(100);

    ui->listWidget->addItem("Car");
    ui->listWidget->addItem("Chess");
    ui->listWidget->addItem("Tree");

    connect(ui->comboBox, &QComboBox::activated, ui->ekran, &Ekran::on_comboBox_activated);
    connect(ui->horizontalSlider, &QSlider::valueChanged, ui->ekran, &Ekran::on_horizontalSlider_sliderMoved);
    connect(ui->listWidget, &QListWidget::currentRowChanged, ui->ekran, &Ekran::on_listWidget_currentRowChanged);
    connect(ui->ekran, &Ekran::signalComboBox, ui->comboBox, &QComboBox::setCurrentIndex);
    connect(ui->ekran, &Ekran::signalSlider, ui->horizontalSlider, &QSlider::setValue);

}

MainWindow::~MainWindow()
{
    delete ui;
}
