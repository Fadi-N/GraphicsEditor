#ifndef EKRANP_H
#define EKRANP_H

#include <QWidget>

class EkranP : public QWidget
{
    Q_OBJECT
public:
    QImage im, im2;
    explicit EkranP(QWidget *parent = nullptr);
    int p,q;
    int a=0, m, n, z, c, Px, Py, u, v, w, W, Wv, Ww;
    void wstawPiksel(int x, int y, int r, int g, int b);
    void addPoint(const std::vector< std::pair <int, int> > vect, int x, int y, int r, int g, int b);
    void BresenhamLine(int x1, int y1, int x2, int y2);
    void wspolrzedneBarycentryczne(const std::vector< std::pair <int, int> > vect);
    std::vector< std::pair <int, int> > vect;
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
signals:

};

#endif // EKRANP_H
