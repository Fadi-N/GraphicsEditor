#include "ekran.h"

#include <QApplication>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QSlider>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget mainWindow;
    QHBoxLayout mainLayout;
    mainWindow.setLayout(&mainLayout);

    Ekran ekran;
    QWidget panel;

    mainLayout.addWidget(&ekran);
    mainLayout.addWidget(&panel);
    mainLayout.setStretch(0, 4);
    mainLayout.setStretch(1, 1);

    QVBoxLayout panelLayer;
    panel.setLayout(&panelLayer);
    QPushButton button("Przycisk");
    QSpinBox *spinBox = new QSpinBox(&ekran);
    QSlider *slider = new QSlider(Qt::Horizontal, &ekran);

    panelLayer.addWidget(&button);
    panelLayer.addWidget(spinBox);
    panelLayer.addWidget(slider);
    panelLayer.addStretch();



    QObject::connect(spinBox, &QSpinBox::valueChanged, slider, &QSlider::setValue);
    QObject::connect(slider, &QSlider::valueChanged, spinBox, &QSpinBox::setValue);
    QObject::connect(slider, &QSlider::valueChanged, &ekran, &Ekran::w_slider);

    spinBox->setMinimum(3);
    spinBox->setMaximum(25);
    slider->setMinimum(3);
    slider->setMaximum(25);

    mainWindow.resize(800, 600);
    mainWindow.show();

    return a.exec();
}
