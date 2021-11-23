#ifndef EKRAN_H
#define EKRAN_H

#include <QWidget>
#include <stack>

class Ekran : public QWidget
{
    Q_OBJECT
public:
    QImage im, im2;
    explicit Ekran(QWidget *parent = nullptr);
    void wstawPiksel(int x, int y, int r, int g, int b);
    void BresenhamLine(int x1, int y1, int x2, int y2);
    void FloodFill(std::stack<std::pair<int, int> > point, int x, int y, int r, int g, int b);
    std::stack<std::pair<int, int> > point;
    void circleBres(int x1, int y1, int x2, int y2);
    void drawCircle(int xc, int yc, int x, int y);

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
public slots:
    void MouseClicked(QMouseEvent *);
signals:

};

#endif // EKRAN_H
