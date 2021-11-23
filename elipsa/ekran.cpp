#include "ekran.h"
#include <QPainter>
#include <QMouseEvent>

int p,q, a;

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

void Ekran::BresenhamLine(int x1, int y1, int x2, int y2)
 {
     int z, zx, zy, ai, bi, xi, yi;
     int x = x1, y = y1;
     //kierunek rysowania
     if (x1 < x2)
     {
         xi = 1;
         zx = x2 - x1;
     }
     else
     {
         xi = -1;
         zx = x1 - x2;
     }
     //kierunek rysowania
     if (y1 < y2)
     {
         yi = 1;
         zy = y2 - y1;
     }
     else
     {
         yi = -1;
         zy = y1 - y2;
     }
     // pierwszy piksel
     wstawPiksel(x, y, 255, 255, 255);
     // oś wiodąca OX
     if (zx > zy)
     {
         ai = (zy - zx) * 2;
         bi = zy * 2;
         z = bi - zx;
         // pętla po kolejnych x
         while (x != x2)
         {
             // test współczynnika
             if (z >= 0)
             {
                 x += xi;
                 y += yi;
                 z += ai;
             }
             else
             {
                 z += bi;
                 x += xi;
             }
             wstawPiksel(x, y, 255, 255, 255);
         }
     }
     // oś wiodąca OY
     else
     {
         ai = ( zx - zy ) * 2;
         bi = zx * 2;
         z = bi - zy;
         // pętla po kolejnych y
         while (y != y2)
         {
             // test współczynnika
             if (z >= 0)
             {
                 x += xi;
                 y += yi;
                 z += ai;
             }
             else
             {
                 z += bi;
                 y += yi;
             }
             wstawPiksel(x, y, 255, 255, 255);
         }
     }
 }

void Ekran::elipsa(int x1, int y1, int x2, int y2)
{
        for(int j=0, k=a-1; j<a; k=j++){
            int r = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
            float alpha = j*2*M_PI/a;
            float alpha_k = k*2*M_PI/a;
            BresenhamLine(x1+r*cos(alpha), y1+r*sin(alpha), x1+r*cos(alpha_k), y1+r*sin(alpha_k));
        }

    update();
}

int Ekran::w_slider(int liczba)
{
    a = liczba;
    update();
    return a;
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
    elipsa(p, q, p, q);
    update();
}

void Ekran::mouseReleaseEvent(QMouseEvent *e)
{

    int x = e->x();
    int y = e->y();
    qDebug("mouse release: %d, %d", x, y);
    elipsa(p, q, x, y);
    update();
}

void Ekran::mouseMoveEvent(QMouseEvent *e)
{
    int x = e->x();
    int y = e->y();
    im=im2.copy();
    qDebug("mouse move: %d, %d", x, y);
    elipsa(p, q, x, y);
    update();
}
