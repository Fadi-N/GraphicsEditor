#include "ekran.h"
#include <QPainter>
#include <QMouseEvent>

Ekran::Ekran(QWidget *parent) : QWidget(parent)
{
    im= QImage("C:/Users/Fadi/Desktop/Grafika_Komputerowa/zadania/TeksturowanieTrojkatow/kaczka.jpg");
    im = im.scaled(400,400);
    if(im.isNull()){
        qDebug("LOADING ERROR");
    }
    im3 = im.copy();

    im2 = QImage(400,400, QImage::Format_RGB32);
    for(int y=0; y<im2.height(); y++){
        uchar *tab = im2.scanLine(y);
        for(int x=0; x<im2.width(); ++x){
            tab[x*4] = 0;
            tab[x*4+1] = 0;
            tab[x*4+2] = 0;
        }
    }
    im4 = im2.copy();
}

void Ekran::wstawPiksel(int x, int y, int r, int g, int b)
{
    if(x<0 || y<0 || x>=800 || y>=800){
        return;
    }
    if(x<400){
        uchar *tab = im.scanLine(y);
        tab[x*4] = b;
        tab[x*4+1] = g;
        tab[x*4+2] = r;
        tab[x*4+3] = 255;
    }else{
        tab2 = im2.scanLine(y);
        tab2[x*4] = b;
        tab2[x*4+1] = g;
        tab2[x*4+2] = r;
        tab2[x*4+3] = 255;
    }
}

void Ekran::addPoint(const std::vector< std::pair <int, int> > vect, int x, int y, int r, int g, int b)
{
    if(x<0 || y<0 || x>=800 || y>=800){
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

    if(a==2 || a==3){
        BresenhamLine(vect[a-2].first, vect[a-2].second, vect[a-1].first, vect[a-1].second);
        BresenhamLine(vect[a-1].first, vect[a-1].second, vect[a].first, vect[a].second);
        BresenhamLine(vect[a].first, vect[a].second, vect[a-2].first, vect[a-2].second);
    }
}

void Ekran::addPoint2(const std::vector< std::pair <double, double> > vect2, int x, int y, int r, int g, int b)
{
    if(x<0 || y<0 || x>=800 || y>=900){
        return;
    }
    int y2 = y;
    for(int i=0; i<4; i++){
        uchar *tab = im2.scanLine(y);
        uchar *tab2 = im2.scanLine(y2);
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

    //qDebug("p = %d", p);
    if(p==2 || p==3){
        BresenhamLine(vect2[p-2].first, vect2[p-2].second, vect2[p-1].first, vect2[p-1].second);
        BresenhamLine(vect2[p-1].first, vect2[p-1].second, vect2[p].first, vect2[p].second);
        BresenhamLine(vect2[p].first, vect2[p].second, vect2[p-2].first, vect2[p-2].second);
    }
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

void Ekran::wspolrzedneBarycentryczne(){

    auto max = std::max_element(begin(vect2), end(vect2), [](const std::pair<int, int>& left, const std::pair<int, int>& right){
        return left.second <  right.second;
    });
    auto min = std::max_element(begin(vect2), end(vect2), [](const std::pair<int, int>& left, const std::pair<int, int>& right){
        return left.second >  right.second;
    });
    //qDebug("MIN MAX = %f %f",  min->second, max->second);

    for(int i=min->second; i<max->second; i++){
        //qDebug("I WYNOSI = %d", i);
        std::vector < double > point_x;
        double wzor;
        for (size_t j=0; j<vect2.size()-1; j++) {
            wzor = vect2[j].first + ((i - vect2[j].second) * ((vect2[j+1.0].first - vect2[j].first) / (vect2[j+1.0].second - vect2[j].second)));
            //qDebug("WZOR = %f", wzor);
            if(wzor <= vect2[j].first && wzor > vect2[j+1].first){
                point_x.push_back(wzor);
            }else if(wzor >= vect2[j].first && wzor < vect2[j+1].first ){
                point_x.push_back(wzor);
            }
        }

        sort(point_x.begin(), point_x.end());

        for (int g=point_x[0]; g<point_x[1]; g++) {
            //qDebug( "SIZE %d", point_x.size());
            //qDebug( "LICZBY: %f %d %f %d \n", point_x[2*g], i, point_x[2*g+1], i);
            Px = g;
            Py = i;
            W = ((vect2[1].first - vect2[0].first)*(vect2[2].second - vect2[0].second)) - ((vect2[1].second - vect2[0].second)*(vect2[2].first - vect2[0].first));
            Wv = ((Px - vect2[0].first)*(vect2[2].second - vect2[0].second)) - ((Py - vect2[0].second)*(vect2[2].first - vect2[0].first));
            Ww = ((vect2[1].first - vect2[0].first)*(Py - vect2[0].second)) - ((vect2[1].second - vect2[0].second)*(Px - vect2[0].first));
            v = Wv/W;
            w = Ww/W;
            u = 1-v-w;

            /*
            qDebug("px = %d, py = %d", Px, Py);
            qDebug("W = %f, Wv = %f, Ww = %f", W, Wv, Ww);
            qDebug("v = %f, w = %f, u = %f", v, w, u);
            qDebug("ptx = %d, pty = %d", Ptx, Pty);
            */

            if ((u>0 && v>0 && w>0) && (u<1 && v<1 && w<1)){
                    Ptx = u*vect[0].first + v*vect[1].first + w*vect[2].first;
                    Pty = u*vect[0].second + v*vect[1].second + w*vect[2].second;

                    tab2 = im2.scanLine(i);
                    uchar *t = im3.scanLine(Pty);
                    tab2[g*4] = t[Ptx*4];
                    tab2[g*4+1] = t[Ptx*4+1];
                    tab2[g*4+2] = t[Ptx*4+2];
                    tab2[g*4+3] = 255;
            }

        }

        point_x.clear();
    }

    update();
}

void Ekran::nearestPoint(int x, int y){
    int wzor = sqrt(((x-vect2[0].first)*(x-vect2[0].first)) + ((y-vect2[0].second)*(y-vect2[0].second)));
    int min = wzor;
    for (auto i=0; i<vect2.size()-1; i++) {
        wzor = sqrt(((x-vect2[i].first)*(x-vect2[i].first)) + ((y-vect2[i].second)*(y-vect2[i].second)));
        //qDebug("WZOR[%d] = %d", i, wzor);
        if(wzor <= min){
            min = wzor;
            z = i;
            qDebug("Z = %d", z);
        }
        //qDebug("MIN = %d", min);
    }
    wspolrzedneBarycentryczne();
    addPoint2(vect2, vect2[z].first, vect2[z].second, 0, 0, 0);
    im2=im4.copy();
}

void Ekran::nearestPoint2(int x, int y){
    int wzor = sqrt(((x-vect[0].first)*(x-vect[0].first)) + ((y-vect[0].second)*(y-vect[0].second)));
    int min = wzor;
    for (auto i=0; i<vect.size()-1; i++) {
        wzor = sqrt(((x-vect[i].first)*(x-vect[i].first)) + ((y-vect[i].second)*(y-vect[i].second)));
        //qDebug("WZOR[%d] = %d", i, wzor);
        if(wzor <= min){
            min = wzor;
            z = i;
            qDebug("Z = %d", z);
        }
        //qDebug("MIN = %d", min);
    }
    wspolrzedneBarycentryczne();
    addPoint(vect, vect[z].first, vect[z].second, 0, 0, 0);
    im=im3.copy();
}


void Ekran::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.drawImage(0, 0, im);
    p.drawImage(400, 0, im2);
}

void Ekran::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        int x = e->x();
        int y = e->y();
        if(a>=0 && a<=2){
            vect.push_back( std::make_pair(x,y));
            qDebug("PAIR[%d]: %d %d", a, vect[a].first, vect[a].second);
            addPoint(vect, x, y, 255, 51, 91);
            a++;
            if(a==3){
                vect.push_back(std::make_pair(vect[0].first, vect[0].second));
                //qDebug("PAIR[%d]: %d %d", a, vect[a].first, vect[a].second);

            }

        }else if(a>=3 && p<=2){
            vect2.push_back( std::make_pair(x,y));
            //qDebug("PAIR[%d]: %f %f", p, vect2[p].first, vect2[p].second);
            addPoint2(vect2, x, y, 255, 51, 91);
            p++;
            if(p==3){
                vect2.push_back(std::make_pair(vect2[0].first, vect2[0].second));
                //qDebug("PAIR[%d]: %f %f", p, vect2[p].first, vect2[p].second);
            }
        }
        update();
    }else if(e->button() == Qt::BackButton){
        int x = e->x();
        int y = e->y();
        //qDebug("M I N = %d %d", x, y);
        nearestPoint(x, y);
        update();
    }else if(e->button() == Qt::ForwardButton){
        int x = e->x();
        int y = e->y();
        //qDebug("M I N = %d %d", x, y);
        nearestPoint2(x, y);
        update();
    }
}

void Ekran::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        if(p==3){
            wspolrzedneBarycentryczne();
        }
        update();
    }else if(e->button() == Qt::BackButton){
        vect2[z].first = e->x();
        vect2[z].second = e->y();
        if(z==0){
            vect2[3].first = e->x();
            vect2[3].second = e->y();
            addPoint2(vect2, vect2[3].first, vect2[3].second, 255, 51, 91);

        }
        addPoint2(vect2, vect2[z].first, vect2[z].second, 255, 51, 91);
        wspolrzedneBarycentryczne();
        update();
    }else if(e->button() == Qt::ForwardButton){
        vect[z].first = e->x();
        vect[z].second = e->y();
        if(z==0){
            vect[3].first = e->x();
            vect[3].second = e->y();
            addPoint(vect, vect[3].first, vect[3].second, 255, 51, 91);

        }
        addPoint(vect, vect[z].first, vect[z].second, 255, 51, 91);
        wspolrzedneBarycentryczne();
        update();
    }
}

void Ekran::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() & Qt::BackButton){
        vect2[z].first = e->x();
        vect2[z].second = e->y();
        update();
    }else if(e->buttons() & Qt::ForwardButton){
        vect[z].first = e->x();
        vect[z].second = e->y();
        update();
    }
}

