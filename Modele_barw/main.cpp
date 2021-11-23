#include <QApplication>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QSlider>
#include <QLabel>

#include "ekran.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget mainWindow;
    QHBoxLayout mainLayout;
    mainWindow.setLayout(&mainLayout);
    mainWindow.setStyleSheet("background: #FF335B;");

    Ekran ekran;
    QWidget panel;
    mainLayout.addWidget(&ekran);
    mainLayout.addWidget(&panel);
    mainLayout.setStretch(0,4);
    mainLayout.setStretch(1,2);

    QVBoxLayout panelLayer;
    panel.setLayout(&panelLayer);
    QSpinBox spinBox;
    panelLayer.addStretch();

    QSlider R(Qt::Horizontal);
    QSlider G(Qt::Horizontal);
    QSlider B(Qt::Horizontal);
    QSlider H(Qt::Horizontal);
    QSlider S(Qt::Horizontal);
    QSlider V(Qt::Horizontal);
    QPushButton button("EXIT");

    QLabel *r = new QLabel("R");
    QLabel *g = new QLabel("G");
    QLabel *b = new QLabel("B");
    QLabel *h = new QLabel("H");
    QLabel *s = new QLabel("S");
    QLabel *v = new QLabel("V");

    panelLayer.addWidget(r);
    panelLayer.addWidget(&R);
    panelLayer.addWidget(g);
    panelLayer.addWidget(&G);
    panelLayer.addWidget(b);
    panelLayer.addWidget(&B);

    panelLayer.addStretch();

    panelLayer.addWidget(h);
    panelLayer.addWidget(&H);
    panelLayer.addWidget(s);
    panelLayer.addWidget(&S);
    panelLayer.addWidget(v);
    panelLayer.addWidget(&V);

    panelLayer.addStretch();

    panelLayer.addWidget(&button);

    R.setMinimum(0);
    R.setMaximum(255);
    G.setMinimum(0);
    G.setMaximum(255);
    B.setMinimum(0);
    B.setMaximum(255);
    H.setMinimum(0);
    H.setMaximum(360);
    S.setMinimum(0);
    S.setMaximum(100);
    V.setMinimum(0);
    V.setMaximum(100);

    QObject::connect(&R, &QSlider::valueChanged, &ekran, &Ekran::RGB_R);
    QObject::connect(&G, &QSlider::valueChanged, &ekran, &Ekran::RGB_G);
    QObject::connect(&B, &QSlider::valueChanged, &ekran, &Ekran::RGB_B);
    QObject::connect(&H, &QSlider::valueChanged, &ekran, &Ekran::HSV_H);
    QObject::connect(&S, &QSlider::valueChanged, &ekran, &Ekran::HSV_S);
    QObject::connect(&V, &QSlider::valueChanged, &ekran, &Ekran::HSV_V);

    QObject::connect(&button, SIGNAL(clicked()), &mainWindow, SLOT(close()));
    mainWindow.resize(400,300);
    mainWindow.show();
    return a.exec();
}
