#include "ekran.h"
#include <QPainter>
#include <QMouseEvent>
#include <vector>
#include <utility>

int p=3, a=0, m, n, z, c;

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

void Ekran::removeAddPoint(int x, int y, int r, int g, int b)
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
}
void Ekran::addPoint(const std::vector< std::pair <int, int> > vect, int x, int y, int r, int g, int b)
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

    if(a==p){
        p++;
        bezier(vect, 500, r-164, g, b+133);
    }
}

void Ekran::BresenhamLine(int x1, int y1, int x2, int y2, int r, int g, int b)
 {
     //qDebug("x1=%d  y1=%d  x2=%d  y2=%d ", x1, y1 , x2, y2);
     int z, zx, zy, ai, bi, xi, yi;
     int x = x1, y = y1;
     //kierunek rysowania
     if (x1 < x2){
         xi = 1;
         zx = x2 - x1;
     }
     else{
         xi = -1;
         zx = x1 - x2;
     }
     //kierunek rysowania
     if (y1 < y2){
         yi = 1;
         zy = y2 - y1;
     }
     else{
         yi = -1;
         zy = y1 - y2;
     }
     // pierwszy piksel
     wstawPiksel(x, y, r, g, b);
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
             wstawPiksel(x, y, r, g, b);
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
             wstawPiksel(x, y, r, g, b);
         }
     }
 }

void Ekran::bezier(std::vector< std::pair <int, int> > vect, int N, int r, int g, int b){
    double t, m, wzor_x, wzor_y , first_point_x, first_point_y, sec_point_x, sec_point_y;

    for (int i=0; i<N; i++){
        t=(double)i/(double)N;
        wzor_x=(1.0/6.0*(-(pow(t,3))+3*pow(t,2)-3*t+1)*vect[a-3].first) + (1.0/6.0*(3*pow(t,3)-6*pow(t,2)+4)*vect[a-2].first) + (1.0/6.0*(-3*pow(t,3)+3*pow(t,2)+3*t+1)*vect[a-1].first) + 1.0/6.0*pow(t,3)*vect[a].first;
        wzor_y=(1.0/6.0*(-(pow(t,3))+3*pow(t,2)-3*t+1)*vect[a-3].second) + (1.0/6.0*(3*pow(t,3)-6*pow(t,2)+4)*vect[a-2].second) + (1.0/6.0*(-3*pow(t,3)+3*pow(t,2)+3*t+1)*vect[a-1].second) + 1.0/6.0*pow(t,3)*vect[a].second;
        m=t+((double)1.0/(double)N);
        first_point_x = wzor_x;
        first_point_y = wzor_y;
        sec_point_x = (1.0/6.0*(-(pow(m,3))+3*pow(m,2)-3*m+1)*vect[a-3].first) + (1.0/6.0*(3*pow(m,3)-6*pow(m,2)+4)*vect[a-2].first) + (1.0/6.0*(-3*pow(m,3)+3*pow(m,2)+3*m+1)*vect[a-1].first) + 1.0/6.0*pow(m,3)*vect[a].first;
        sec_point_y = (1.0/6.0*(-(pow(m,3))+3*pow(m,2)-3*m+1)*vect[a-3].second) + (1.0/6.0*(3*pow(m,3)-6*pow(m,2)+4)*vect[a-2].second) + (1.0/6.0*(-3*pow(m,3)+3*pow(m,2)+3*m+1)*vect[a-1].second) + 1.0/6.0*pow(m,3)*vect[a].second;
        /*qDebug("T: %f /n", t);
        qDebug("WZOR_X: %f /n", wzor_x);
        qDebug("WZOR_Y: %f /n", wzor_y);
        qDebug("SEC_X: %f /n", sec_point_x);
        qDebug("SEC_Y: %f /n", sec_point_y);
        */
        BresenhamLine(first_point_x, first_point_y, sec_point_x, sec_point_y, r,  g, b);
    }
}

void Ekran::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.fillRect(0, 0, width(), height(), Qt::blue);
    p.drawImage(0, 0, im);
}


void Ekran::draw(int N, int r, int g, int b){
    double t, m, wzor_x, wzor_y , first_point_x, first_point_y, sec_point_x, sec_point_y;
    for (auto i=0; i<vect.size(); i++) {
        c = i;
    }
    int j=0;
    for (int i=0; i<N; i++){
        for (auto j=3; j<vect.size(); j++) {
            t=(double)i/(double)N;
            wzor_x=(1.0/6.0*(-(pow(t,3))+3*pow(t,2)-3*t+1)*vect[j-3].first) + (1.0/6.0*(3*pow(t,3)-6*pow(t,2)+4)*vect[j-2].first) + (1.0/6.0*(-3*pow(t,3)+3*pow(t,2)+3*t+1)*vect[j-1].first) + 1.0/6.0*pow(t,3)*vect[j].first;
            wzor_y=(1.0/6.0*(-(pow(t,3))+3*pow(t,2)-3*t+1)*vect[j-3].second) + (1.0/6.0*(3*pow(t,3)-6*pow(t,2)+4)*vect[j-2].second) + (1.0/6.0*(-3*pow(t,3)+3*pow(t,2)+3*t+1)*vect[j-1].second) + 1.0/6.0*pow(t,3)*vect[j].second;
            m=t+((double)1.0/(double)N);
            first_point_x = wzor_x;
            first_point_y = wzor_y;
            sec_point_x = (1.0/6.0*(-(pow(m,3))+3*pow(m,2)-3*m+1)*vect[j-3].first) + (1.0/6.0*(3*pow(m,3)-6*pow(m,2)+4)*vect[j-2].first) + (1.0/6.0*(-3*pow(m,3)+3*pow(m,2)+3*m+1)*vect[j-1].first) + 1.0/6.0*pow(m,3)*vect[j].first;
            sec_point_y = (1.0/6.0*(-(pow(m,3))+3*pow(m,2)-3*m+1)*vect[j-3].second) + (1.0/6.0*(3*pow(m,3)-6*pow(m,2)+4)*vect[j-2].second) + (1.0/6.0*(-3*pow(m,3)+3*pow(m,2)+3*m+1)*vect[j-1].second) + 1.0/6.0*pow(m,3)*vect[j].second;

            BresenhamLine(first_point_x, first_point_y, sec_point_x, sec_point_y, r,  g, b);
        }
    }
}

void Ekran::nearestPoint(int x, int y){
    int wzor = sqrt(((x-vect[0].first)*(x-vect[0].first)) + ((y-vect[0].second)*(y-vect[0].second)));
    int min = wzor;
    for (auto i=0; i<vect.size(); i++) {
        wzor = sqrt(((x-vect[i].first)*(x-vect[i].first)) + ((y-vect[i].second)*(y-vect[i].second)));
        qDebug("WZOR[%d] = %d", i, wzor);
        if(wzor <= min){
            min = wzor;
            z = i;
        }
        qDebug("MIN = %d", min);
    }
    draw(500, 0, 0, 0);
    removeAddPoint(vect[z].first, vect[z].second, 0, 0, 0);
    im2=im.copy();

}

void Ekran::mousePressEvent(QMouseEvent *e)
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

    }else if (e->button() == Qt::RightButton)
    {
        //qDebug("P= %d", p);
        if(a==p && p>3){
            p--;
            a--;
            removeAddPoint(vect[a].first, vect[a].second, 0, 0, 0);
            bezier(vect, 500, 0, 0, 0);
            //qDebug("P= %d", p);
        }else{
            a--;
            removeAddPoint(vect[a].first, vect[a].second, 0, 0, 0);
        }
        vect.erase(vect.end());
        //qDebug("A=%d", a);
        update();
    }else if(e->button() == Qt::BackButton){
        m = e->x();
        n = e->y();
        qDebug("M I N = %d %d", m, n);
        nearestPoint(m, n);
        update();
    }
}

void Ekran::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::BackButton){
        vect[z].first = e->x();
        vect[z].second = e->y();
        im=im2.copy();
        removeAddPoint(vect[z].first, vect[z].second, 255, 51, 91);
        draw(500, 91, 51, 224);
        update();
    }
}

void Ekran::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() & Qt::BackButton){
        vect[z].first = e->x();
        vect[z].second = e->y();
        update();
    }
}

