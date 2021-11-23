#ifndef EKRAN_H
#define EKRAN_H

#include <QWidget>

class Ekran : public QWidget
{
    Q_OBJECT
public:
    QImage im, im2;
    explicit Ekran(QWidget *parent = nullptr);
    void HSV_RGB(float h, float s, float v);
protected:
    void paintEvent(QPaintEvent *);
public slots:
    void RGB_R(int);
    void RGB_G(int);
    void RGB_B(int);
    void HSV_H(int);
    void HSV_S(int);
    void HSV_V(int);
signals:

};

#endif // EKRAN_H
