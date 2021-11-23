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
    void addPoint(const std::vector< std::pair <int, int> > vect, int x, int y, int r, int g, int b);
    void removeAddPoint(int x, int y, int r, int g, int b);
    void BresenhamLine(int x1, int y1, int x2, int y2, int r, int g, int b);
    void bezier(std::vector< std::pair <int, int> > vect, int N, int r, int g, int b);
    void draw(int N, int r, int g, int b);
    void nearestPoint(int x, int y);
    std::vector< std::pair <int, int> > vect;
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

signals:

};

#endif // EKRAN_H
