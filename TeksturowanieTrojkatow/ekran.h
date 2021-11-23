#ifndef EKRAN_H
#define EKRAN_H

#include <QWidget>

class Ekran : public QWidget
{
    Q_OBJECT
public:
    QImage im, im2, im3, im4;
    explicit Ekran(QWidget *parent = nullptr);
    uchar *tab2;
    int p=0,q;
    int a=0, m, n, z, c, Px, Py, Ptx, Pty;
    double W, Wv, Ww, u, v, w;
    void wstawPiksel(int x, int y, int r, int g, int b);
    void addPoint(const std::vector< std::pair <int, int> > vect, int x, int y, int r, int g, int b);
    void addPoint2(const std::vector< std::pair <double, double> > vect2, int x, int y, int r, int g, int b);
    void BresenhamLine(int x1, int y1, int x2, int y2);
    void nearestPoint(int x, int y);
    void nearestPoint2(int x, int y);
    void wspolrzedneBarycentryczne();
    std::vector< std::pair <int, int> > vect;
    std::vector< std::pair <double, double> > vect2;
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
signals:

};

#endif // EKRAN_H
