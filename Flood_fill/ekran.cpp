#include "ekran.h"
#include <QPainter>
#include <QMouseEvent>
#include <QPalette>
#include <stack>

int p, q;
uchar *tab;
Ekran::Ekran(QWidget *parent) : QWidget(parent)
{
    im = QImage(800,600, QImage::Format_RGB32);
    for(int y=0; y<im.height(); y++){
        tab = im.scanLine(y);
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
    tab = im.scanLine(y);
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
void Ekran::FloodFill(std::stack<std::pair<int, int> > point, int x, int y, int r, int g, int b){
    while(!point.empty()){
        std::pair<int,int> P = point.top();
        point.pop();
        tab = im.scanLine(P.second);
        if(P.first>=0 && P.second>=0 && P.first<im.width() && P.second<im.height()){
            if(tab[P.first*4]==0 && tab[P.first*4+1]==0 && tab[P.first*4+2]==0){

                wstawPiksel(P.first, P.second, r, g, b);

                point.push(std::pair<int, int>(P.first-1, P.second));
                point.push(std::pair<int, int>(P.first+1, P.second));
                point.push(std::pair<int, int>(P.first, P.second-1));
                point.push(std::pair<int, int>(P.first, P.second+1));

            }
        }
    }
    update();
}
void Ekran::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.fillRect(0, 0, width(), height(), Qt::blue);
    p.drawImage(0, 0, im);
}

void Ekran::MouseClicked(QMouseEvent *e){
    qDebug("KLIKLIK");
    if (e->button() == Qt::LeftButton)
    {
        p = e->x();
        q = e->y();
        im2=im.copy();
        drawCircle(p, q, p, q);
    }
    update();
}

void Ekran::mousePressEvent(QMouseEvent *e)
{

    if (e->button() == Qt::LeftButton)
    {
        p = e->x();
        q = e->y();
        im2=im.copy();
        qDebug("mouse press: %d, %d", p, q);
        BresenhamLine(p, q, p, q);
        update();
    }else if (e->button() == Qt::RightButton)
    {
        p = e->x();
        q = e->y();
        im2=im.copy();
        qDebug("mouse press: %d, %d", p, q);
        circleBres(p, q, p, q);
        update();
    }else if(e->button() == Qt::BackButton)
    {
        int x = e->x();
        int y = e->y();
        point.push(std::pair<int, int>(x,y));
        wstawPiksel(x, y, 0, 0, 0);
        FloodFill(point, x, y, 255, 51, 91);
    }

}

void Ekran::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        int x = e->x();
        int y = e->y();
        im=im2.copy();
        qDebug("mouse release: %d, %d", x, y);
        BresenhamLine(p, q, x, y);
        update();
    }else if (e->button() == Qt::RightButton)
    {
        int x = e->x();
        int y = e->y();
        qDebug("mouse release: %d, %d", x, y);
        circleBres(p, q, x, y);
        update();
    }
}

void Ekran::mouseMoveEvent(QMouseEvent *e)
{
    if (e->buttons() & Qt::LeftButton)
    {
        int x = e->x();
        int y = e->y();
        im=im2.copy();
        qDebug("mouse move: %d, %d", x, y);
        BresenhamLine(p, q, x, y);
        update();
    }else if (e->buttons() & Qt::RightButton){
        int x = e->x();
        int y = e->y();
        im=im2.copy();
        qDebug("mouse move: %d, %d", x, y);
        circleBres(p, q, x, y);
        update();
    }
}
