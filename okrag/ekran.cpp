#include "ekran.h"
#include <QPainter>
#include <QMouseEvent>

int p,q;

Ekran::Ekran(QWidget *parent) : QWidget(parent)
{
    im = QImage(800,600, QImage::Format_RGB32);
    for(int y=0; y<im.height(); y++){
        uchar *tab = im.scanLine(y);
        for(int x=0; x<im.width(); ++x){
            tab[x*4] = 0;
            tab[x*4+1] = 0;
            tab[x*4+2] = 0;
        }
    }


}

void Ekran::wstawPiksel(int x, int y, int r, int g, int b)
{
    if(x<0 || y<0 || x>=im.width() || y>=im.height()){
        return;
    }
    uchar *tab = im.scanLine(y);
    tab[x*4] = b;
    tab[x*4+1] = g;
    tab[x*4+2] = r;
    tab[x*4+3] = 255;
}

void Ekran::drawCircle(int x1, int y1, int x2, int y2)
{
    wstawPiksel(x1+x2, y1+y2, 255, 255, 255);
    wstawPiksel(x1-x2, y1+y2, 255, 255, 255);
    wstawPiksel(x1+x2, y1-y2, 255, 255, 255);
    wstawPiksel(x1-x2, y1-y2, 255, 255, 255);
    wstawPiksel(x1+y2, y1+x2, 255, 255, 255);
    wstawPiksel(x1-y2, y1+x2, 255, 255, 255);
    wstawPiksel(x1+y2, y1-x2, 255, 255, 255);
    wstawPiksel(x1-y2, y1-x2, 255, 255, 255);
}

void Ekran::circleBres(int x1, int y1, int x2, int y2)
{
    int r = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
    int x = 0, y = r;
    int d = 3 - 2 * r;

    drawCircle(x1, y1, x, y);

    while (y >= x)
    {
        //syowanie 8 pikseli dla każdego piksela
        x++;
        //sprawdzenie parametru i aktualizacja d, x, y
        if (d > 0)
        {
            y--;
            d = d + 4 * (x - y) + 10;
        }
        else
        {
            d = d + 4 * x + 6;
        }
        drawCircle(x1, y1, x, y);
    }
}

void Ekran::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.fillRect(0, 0, width(), height(), Qt::blue);
    p.drawImage(0, 0, im);
}

void Ekran::mousePressEvent(QMouseEvent *e)
{
    p = e->x();
    q = e->y();
    im2=im.copy();
    qDebug("mouse press: %d, %d", p, q);
    circleBres(p, q, p, q);
    update();
}

void Ekran::mouseReleaseEvent(QMouseEvent *e)
{

    int x = e->x();
    int y = e->y();
    qDebug("mouse release: %d, %d", x, y);
    circleBres(p, q, x, y);
    update();
}

void Ekran::mouseMoveEvent(QMouseEvent *e)
{
    int x = e->x();
    int y = e->y();
    im=im2.copy();
    qDebug("mouse move: %d, %d", x, y);
    circleBres(p, q, x, y);
    update();
}


