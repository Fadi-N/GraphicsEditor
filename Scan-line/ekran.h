#ifndef EKRAN_H
#define EKRAN_H

#include <QWidget>

class Ekran : public QWidget
{
    Q_OBJECT
public:
    QImage im, im2, im3;
    explicit Ekran(QWidget *parent = nullptr);
    void wstawPiksel(int x, int y, int r, int g, int b);
    void addPoint(const std::vector< std::pair <double, double> > vect, int x, int y, int r, int g, int b);
    void removeAddPoint(int x, int y, int r, int g, int b);
    void BresenhamLine(int x1, int y1, int x2, int y2, int r, int g, int b);
    void linePoints(std::vector< std::pair <double, double> > vect, int N, int r, int g, int b);
    void draw(int N, int r, int g, int b);
    void drawPolygonScanline(std::vector< std::pair <double, double> > vect);
    void min_max(std::vector< std::pair <int, int> > vect);
    std::vector< std::pair <double, double> > vect;
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

signals:

};

#endif // EKRAN_H
