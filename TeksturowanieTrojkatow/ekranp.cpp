#include "ekranp.h"
#include <QPainter>
#include <QMouseEvent>

EkranP::EkranP(QWidget *parent) : QWidget(parent)
{
    im = QImage(400,400, QImage::Format_RGB32);
    for(int y=0; y<im.height(); y++){
        uchar *tab = im.scanLine(y);
        for(int x=0; x<im.width(); ++x){
            tab[x*4] = 0;
            tab[x*4+1] = 0;
            tab[x*4+2] = 0;
        }
    }


}

void EkranP::wstawPiksel(int x, int y, int r, int g, int b)
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

void EkranP::addPoint(const std::vector< std::pair <int, int> > vect, int x, int y, int r, int g, int b)
{
    if(x<0 || y<0 || x>=im.width() || y>=im.height()){
        return;
    }
    int y2 = y;
    for(int i=0; i<4; i++){
        uchar *tab = im.scanLine(y);
        uchar *tab2 = im.scanLine(y2);
        tab[(x+i)*4] = b;
        tab[(x+i)*4+1] = g;
        tab[(x+i)*4+2] = r;
        tab[(x+i)*4+3] = 255;
        tab[(x-i)*4] = b;
        tab[(x-i)*4+1] = g;
        tab[(x-i)*4+2] = r;
        tab[(x-i)*4+3] = 255;
        tab[(x+i)*4] = b;
        tab2[(x+i)*4+1] = g;
        tab2[(x+i)*4+2] = r;
        tab2[(x+i)*4+3] = 255;
        tab2[(x-i)*4] = b;
        tab2[(x-i)*4+1] = g;
        tab2[(x-i)*4+2] = r;
        tab2[(x-i)*4+3] = 255;
        y++;
        y2--;
    }

    if(a==2){
        BresenhamLine(vect[a-2].first, vect[a-2].second, vect[a-1].first, vect[a-1].second);
        BresenhamLine(vect[a-1].first, vect[a-1].second, vect[a].first, vect[a].second);
        BresenhamLine(vect[a].first, vect[a].second, vect[a-2].first, vect[a-2].second);
    }

}

void EkranP::BresenhamLine(int x1, int y1, int x2, int y2)
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
     wstawPiksel(x, y, 91, 51, 224);
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
             wstawPiksel(x, y, 91, 51, 224);
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
             wstawPiksel(x, y, 91, 51, 224);
         }
     }
 }

void EkranP::wspolrzedneBarycentryczne(const std::vector< std::pair <int, int> > vect){
    Px = vect[0].first + v*(vect[1].first - vect[0].first) + w*(vect[2].first - vect[0].first);
    Py = vect[0].second + v*(vect[1].second - vect[0].second) + w*(vect[2].second - vect[0].second);
    W = (vect[1].second - vect[0].second)*(vect[2].second - vect[0].second) - (vect[1].second - vect[0].second)*(vect[2].second - vect[0].second);
    Wv = (Px * vect[0].second)*(vect[2].second - vect[0].second) - (Py*vect[0].second)*(vect[2].second - vect[0].second);
    Ww = (vect[1].second - vect[0].second)*(Py*vect[0].second) - (vect[1].second - vect[0].second)*(Px * vect[0].second);
    v = Wv/W;
    w = Ww/W;
    u = 1-v-w;
}

void EkranP::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.fillRect(0, 0, width(), height(), Qt::blue);
    p.drawImage(0, 0, im);
}

void EkranP::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        int x = e->x();
        int y = e->y();
        im2 = im.copy();
        if(a>=0){
            vect.push_back( std::make_pair(x,y));
            qDebug("PAIR[%d]: %d %d", a, vect[a].first, vect[a].second);
            addPoint(vect, x, y, 255, 51, 91);
            a++;
            update();
        }
    }
}

void EkranP::mouseReleaseEvent(QMouseEvent *e)
{

}

void EkranP::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() & Qt::BackButton){
        vect[z].first = e->x();
        vect[z].second = e->y();
        update();
    }
}


