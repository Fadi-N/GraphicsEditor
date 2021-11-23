#ifndef EKRAN_H
#define EKRAN_H

#include <QWidget>

class Ekran : public QWidget
{
    Q_OBJECT
public:
    QImage im, im2, im3, im4, im5, im6, im7;
    explicit Ekran(QWidget *parent = nullptr);
    uchar *tab2;
    int p=0,q, qq=0;
    int a=0, aa=0, va=0 , m, n, z, c, Px, Py, Ptx, Pty;
    double W, Wv, Ww, u, v, w;
    void wstawPiksel(int x, int y, int r, int g, int b);
    void addPoint(const std::vector< std::pair <double, double> > vect, int x, int y, int r, int g, int b);
    void addPoint3(const std::vector< std::pair <double, double> > vect3, int x, int y, int r, int g, int b);
    void BresenhamLine(int x1, int y1, int x2, int y2);
    void move(const std::vector< std::pair <double, double> > vect2, double val, double alpha);
    void nearestPoint(int x, int y);
    void nearestPoint2(int x, int y);
    void wspolrzedneBarycentryczne();
    void wspolrzedneBarycentryczne2();
    void morphing(double val);
    void clear();
    std::vector< std::pair <double, double> > vect;
    std::vector< std::pair <double, double> > vect2;
    std::vector< std::pair <double, double> > vect3;
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
public slots:
    void on_horizontalSlider_valueChanged(int value);
    void on_horizontalSlider_2_valueChanged(int value);

};

#endif // EKRAN_H
