#include "ekran.h"
#include <QPainter>
#include <QMouseEvent>
#include <vector>
#include <utility>

int p=1, a=0, m, n, z, c;
uchar *tab;

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
    tab = im.scanLine(y);
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
void Ekran::addPoint(const std::vector< std::pair <double, double> > vect, int x, int y, int r, int g, int b)
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
        linePoints(vect, 500, r-164, g, b+133);
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

void Ekran::linePoints(std::vector< std::pair <double, double> > vect, int N, int r, int g, int b){
    double first_point_x, first_point_y, sec_point_x, sec_point_y;

    for (int i=0; i<N; i++){

        first_point_x = vect[a-1].first;
        first_point_y = vect[a-1].second;
        sec_point_x = vect[a].first;
        sec_point_y = vect[a].second;
        BresenhamLine(first_point_x, first_point_y, sec_point_x, sec_point_y, r,  g, b);
    }
}

void Ekran::drawPolygonScanline(std::vector< std::pair <double, double> > vect){
    auto max = std::max_element(begin(vect), end(vect), [](const std::pair<int, int>& left, const std::pair<int, int>& right){
        return left.second <  right.second;
    });
    auto min = std::max_element(begin(vect), end(vect), [](const std::pair<int, int>& left, const std::pair<int, int>& right){
        return left.second >  right.second;
    });
    //qDebug("MIN MAX = %f %f",  min->second, max->second);

    for(int i=min->second; i<=max->second; i++){
        //qDebug("I WYNOSI = %d", i);
        std::vector < double > point_x;
        double wzor;
        for (size_t j=0; j<vect.size()-1; j++) {
            wzor = vect[j].first + ((i - vect[j].second) * ((vect[j+1.0].first - vect[j].first) / (vect[j+1.0].second - vect[j].second)));
            //qDebug("WZOR = %f", wzor);

            if(wzor <= vect[j].first && wzor > vect[j+1].first){
                point_x.push_back(wzor);
            }else if(wzor >= vect[j].first && wzor < vect[j+1].first ){
                point_x.push_back(wzor);
            }
        }

        sort(point_x.begin(), point_x.end());

        for (int v=0; v<point_x.size()-1; v++) {
            //qDebug( "SORTED[%d]: %f \n", v, point_x[v]);
            if(point_x.size() == 3){
                for(int i=0; i<vect.size(); i++){
                    if(vect[i].first == point_x[0]){
                        v++;
                        BresenhamLine(point_x[v], i, point_x[v+1], i, 51, 128, 255);
                        break;
                    }
                }
                BresenhamLine(point_x[v], i, point_x[v+1], i, 51, 128, 255);
            }
            else{
                BresenhamLine(point_x[2*v], i, point_x[2*v+1], i, 51, 128, 255);
            }
        }

        /*for (int v=0; v<point_x.size(); v++) {
            qDebug( "SORTED[%d]: %f \n", v, point_x[v]);
            if(v>=1){
                BresenhamLine(point_x[v-1], i, point_x[v], i, 51, 128, 255);
            }
        }*/

        point_x.clear();
    }

    update();

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

void Ekran::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        int x = e->x();
        int y = e->y();
        im2 = im.copy();
        if(a>=0){
        vect.push_back( std::make_pair(x,y));
        qDebug("PAIR[%d]: %f %f", a, vect[a].first, vect[a].second);
        addPoint(vect, x, y, 255, 51, 91);

        a++;
        update();
    }

    }else if (e->button() == Qt::RightButton)
    {
        //qDebug("P= %d", p);
        if(a==p && p>1){
            p--;
            a--;
            removeAddPoint(vect[a].first, vect[a].second, 0, 0, 0);
            linePoints(vect, 500, 0, 0, 0);
            //qDebug("P= %d", p);
        }else{
            a--;
            removeAddPoint(vect[a].first, vect[a].second, 0, 0, 0);
        }
        vect.erase(vect.end());
        //qDebug("A=%d", a);
        update();
    }else if(e->button() == Qt::BackButton){
        /*
        m = e->x();
        n = e->y();
        qDebug("M I N = %d %d", m, n);
        nearestPoint(m, n);
        */
        drawPolygonScanline(vect);
        update();
    }
}
