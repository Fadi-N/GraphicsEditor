#include "ekran.h"
#include <QPainter>
#include <QMouseEvent>

Ekran::Ekran(QWidget *parent) : QWidget(parent)
{
    im = QImage("C:/Users/Fadi/Desktop/Grafika_Komputerowa/zadania/morphing/kaczka.jpg");
    im = im.scaled(400,400);
    if(im.isNull()){
        qDebug("LOADING ERROR");
    }
    im3 = im.copy();

    im5= QImage("C:/Users/Fadi/Desktop/Grafika_Komputerowa/zadania/morphing/a.jpg");
    im5 = im5.scaled(400,400);
    if(im5.isNull()){
        qDebug("LOADING ERROR");
    }

    im2 = QImage(400,400, QImage::Format_RGB32);
    for(int y=0; y<im2.height(); y++){
        uchar *tab = im2.scanLine(y);
        for(int x=0; x<im2.width(); ++x){
            tab[x*4] = 0;
            tab[x*4+1] = 0;
            tab[x*4+2] = 0;
        }
    }
    im7= im2.copy();
    im6 = im2.copy();
    im4 = im2.copy();

}

void Ekran::wstawPiksel(int x, int y, int r, int g, int b)
{
    if(x<0 || y<0 || x>=1300 || y>=1300){
        return;
    }
    if(va == 0 && qq == 0){
        uchar *tab = im.scanLine(y);
        tab[x*4] = b;
        tab[x*4+1] = g;
        tab[x*4+2] = r;
        tab[x*4+3] = 255;
    }else if(va == 1){
        tab2 = im5.scanLine(y);
        tab2[x*4] = b;
        tab2[x*4+1] = g;
        tab2[x*4+2] = r;
        tab2[x*4+3] = 255;
    }else{
        uchar *tab = im6.scanLine(y);
        tab[x*4] = b;
        tab[x*4+1] = g;
        tab[x*4+2] = r;
        tab[x*4+3] = 255;
    }
}

void Ekran::clear(){
    for(int y=0; y<im6.height(); y++){
        uchar *tab = im6.scanLine(y);
        for(int x=0; x<im6.width(); ++x){
            tab[x*4] = 0;
            tab[x*4+1] = 0;
            tab[x*4+2] = 0;
            tab[x*4+3] = 255;
        }
    }
}

void Ekran::addPoint(const std::vector< std::pair <double, double> > vect, int x, int y, int r, int g, int b)
{
    if(x<0 || y<0 || x>=1300 || y>=1300){
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
    im3 = im.copy();
}

void Ekran::addPoint3(const std::vector< std::pair <double, double> > vect3, int x, int y, int r, int g, int b)
{
    if(x<0 || y<0 || x>=1300 || y>=1300){
        return;
    }
    int y2 = y;
    for(int i=0; i<4; i++){
        uchar *tab = im5.scanLine(y);
        uchar *tab2 = im5.scanLine(y2);
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

    if(aa==2 || aa==3){
        BresenhamLine(vect3[aa-2].first, vect3[aa-2].second, vect3[aa-1].first, vect3[aa-1].second);
        BresenhamLine(vect3[aa-1].first, vect3[aa-1].second, vect3[aa].first, vect3[aa].second);
        BresenhamLine(vect3[aa].first, vect3[aa].second, vect3[aa-2].first, vect3[aa-2].second);
    }

}

void Ekran::move(const std::vector< std::pair <double, double> > vect2, double val, double alpha){

    auto max = std::max_element(begin(vect2), end(vect2), [](const std::pair<int, int>& left, const std::pair<int, int>& right){
        return left.second <  right.second;
    });
    auto min = std::max_element(begin(vect2), end(vect2), [](const std::pair<int, int>& left, const std::pair<int, int>& right){
        return left.second >  right.second;
    });
    //qDebug("MIN MAX = %d %d",  min->second, max->second);

    for(double i=min->second; i<max->second; i++){
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

        for (double g=point_x[0]; g<point_x[1]; g++) {
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
                    double Ptx1, Ptx2, Pty1, Pty2;

                    Ptx = u*vect2[0].first + v*vect2[1].first + w*vect2[2].first;
                    Pty = u*vect2[0].second + v*vect2[1].second + w*vect2[2].second;

                    Ptx1 = u*vect[0].first + v*vect[1].first + w*vect[2].first;
                    Pty1 = u*vect[0].second + v*vect[1].second + w*vect[2].second;

                    Ptx2 = u*vect3[0].first + v*vect3[1].first + w*vect3[2].first;
                    Pty2 = u*vect3[0].second + v*vect3[1].second + w*vect3[2].second;


                    tab2 = im6.scanLine(Pty);
                    uchar *t1 = im4.scanLine(Pty1);
                    uchar *t2 = im7.scanLine(Pty2);
                    tab2[Ptx*4] = (alpha * t1[(int)Ptx1*4]) + (val * t2[(int)Ptx2*4]);
                    tab2[Ptx*4+1] = (alpha * t1[(int)Ptx1*4+1]) + (val * t2[(int)Ptx2*4+1]);
                    tab2[Ptx*4+2] = (alpha * t1[(int)Ptx1*4+2]) + (val * t2[(int)Ptx2*4+2]);
                    tab2[Ptx*4+3] = 255;

            }

        }

        point_x.clear();
    }





    BresenhamLine(vect2[0].first, vect2[0].second, vect2[1].first, vect2[1].second);
    BresenhamLine(vect2[1].first, vect2[1].second, vect2[2].first, vect2[2].second);
    BresenhamLine(vect2[2].first, vect2[2].second, vect2[0].first, vect2[0].second);
    im2 = im6.copy();
    clear();
    update();
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

    auto max = std::max_element(begin(vect), end(vect), [](const std::pair<int, int>& left, const std::pair<int, int>& right){
        return left.second <  right.second;
    });
    auto min = std::max_element(begin(vect), end(vect), [](const std::pair<int, int>& left, const std::pair<int, int>& right){
        return left.second >  right.second;
    });
    //qDebug("MIN MAX = %d %d",  min->second, max->second);

    for(int i=min->second; i<max->second; i++){
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

        for (int g=point_x[0]; g<point_x[1]; g++) {
            //qDebug( "SIZE %d", point_x.size());
            //qDebug( "LICZBY: %f %d %f %d \n", point_x[2*g], i, point_x[2*g+1], i);
            Px = g;
            Py = i;
            W = ((vect[1].first - vect[0].first)*(vect[2].second - vect[0].second)) - ((vect[1].second - vect[0].second)*(vect[2].first - vect[0].first));
            Wv = ((Px - vect[0].first)*(vect[2].second - vect[0].second)) - ((Py - vect[0].second)*(vect[2].first - vect[0].first));
            Ww = ((vect[1].first - vect[0].first)*(Py - vect[0].second)) - ((vect[1].second - vect[0].second)*(Px - vect[0].first));
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

                    tab2 = im4.scanLine(i);
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


void Ekran::wspolrzedneBarycentryczne2(){

    auto max = std::max_element(begin(vect3), end(vect3), [](const std::pair<int, int>& left, const std::pair<int, int>& right){
        return left.second <  right.second;
    });
    auto min = std::max_element(begin(vect3), end(vect3), [](const std::pair<int, int>& left, const std::pair<int, int>& right){
        return left.second >  right.second;
    });
    //qDebug("MIN MAX = %d %d",  min->second, max->second);

    for(int i=min->second; i<max->second; i++){
        //qDebug("I WYNOSI = %d", i);
        std::vector < double > point_x;
        double wzor;
        for (size_t j=0; j<vect3.size()-1; j++) {
            wzor = vect3[j].first + ((i - vect3[j].second) * ((vect3[j+1.0].first - vect3[j].first) / (vect3[j+1.0].second - vect3[j].second)));
            //qDebug("WZOR = %f", wzor);
            if(wzor <= vect3[j].first && wzor > vect3[j+1].first){
                point_x.push_back(wzor);
            }else if(wzor >= vect3[j].first && wzor < vect3[j+1].first ){
                point_x.push_back(wzor);
            }
        }

        sort(point_x.begin(), point_x.end());

        for (int g=point_x[0]; g<point_x[1]; g++) {
            //qDebug( "SIZE %d", point_x.size());
            //qDebug( "LICZBY: %f %d %f %d \n", point_x[2*g], i, point_x[2*g+1], i);
            Px = g;
            Py = i;
            W = ((vect3[1].first - vect3[0].first)*(vect3[2].second - vect3[0].second)) - ((vect3[1].second - vect3[0].second)*(vect3[2].first - vect3[0].first));
            Wv = ((Px - vect3[0].first)*(vect3[2].second - vect3[0].second)) - ((Py - vect3[0].second)*(vect3[2].first - vect3[0].first));
            Ww = ((vect3[1].first - vect3[0].first)*(Py - vect3[0].second)) - ((vect3[1].second - vect3[0].second)*(Px - vect3[0].first));
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
                    Ptx = u*vect3[0].first + v*vect3[1].first + w*vect3[2].first;
                    Pty = u*vect3[0].second + v*vect3[1].second + w*vect3[2].second;

                    tab2 = im7.scanLine(i);
                    uchar *t = im5.scanLine(Pty);
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

void Ekran::morphing(double val){
    qDebug("%f", val);
    double alpha;
    double pointx, pointy;
    alpha = 1.0 - val;
    qDebug("%f", alpha);
    qq = 1;
    for (int i=0; i<vect.size(); i++) {
        pointx = alpha*vect[i].first + (val * vect3[i].first);
        pointy = alpha*vect[i].second + (val * vect3[i].second);
        //qDebug("POINT %f, %f", pointx, pointy);
        vect2.push_back( std::make_pair(pointx,pointy));

    }
    for (int i=0; i<vect2.size(); i++) {
        qDebug("vector[%d] = %f %f", i, vect2[i].first, vect2[i].second);
    }

    move(vect2, val, alpha);
    vect2.clear();
    update();
}
/*
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
    addPoint3(vect3, vect3[z].first, vect3[z].second, 0, 0, 0);
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
*/

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
            qDebug("PAIR[%d]: %f %f", a, vect[a].first, vect[a].second);
            addPoint(vect, x, y, 255, 51, 91);
            a++;
            if(a==3){
                vect.push_back(std::make_pair(vect[0].first, vect[0].second));
                qDebug("PAIR[%d]: %f %f", a, vect[a].first, vect[a].second);
            }

        }else if(aa>=0 && aa<=2){
            vect3.push_back( std::make_pair(x,y));
            qDebug("PAIR[%d]: %f %f", aa, vect3[aa].first, vect3[aa].second);
            addPoint3(vect3, x, y, 255, 51, 91);
            aa++;
            if(aa==3){
                vect3.push_back(std::make_pair(vect3[0].first, vect3[0].second));
                qDebug("PAIR[%d]: %f %f", aa, vect3[aa].first, vect3[aa].second);

            }
        }
        update();
    }else if(e->button() == Qt::BackButton){
        int x = e->x();
        int y = e->y();
        //qDebug("M I N = %d %d", x, y);
        //nearestPoint(x, y);
        update();
    }else if(e->button() == Qt::ForwardButton){
        int x = e->x();
        int y = e->y();
        //qDebug("M I N = %d %d", x, y);
        //nearestPoint2(x, y);
        update();
    }
}

void Ekran::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        if(a==3){
            wspolrzedneBarycentryczne();
        }
        if(aa==3){
            wspolrzedneBarycentryczne2();
        }
        update();
    }else if(e->button() == Qt::BackButton){
        vect2[z].first = e->x();
        vect2[z].second = e->y();
        if(z==0){
            vect2[3].first = e->x();
            vect2[3].second = e->y();
            addPoint3(vect3, vect3[3].first, vect3[3].second, 255, 51, 91);

        }
        addPoint3(vect3, vect3[z].first, vect3[z].second, 255, 51, 91);
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

void Ekran::on_horizontalSlider_2_valueChanged(int value)
{
    if(value == 1){
        im = im5.copy();
        va = 1;
        im2 = im7.copy();
    }else{
        im = im3.copy();
        va = 0;
        im2 = im4.copy();
    }
    update();
}

void Ekran::on_horizontalSlider_valueChanged(int value)
{
    double val;
    val = value/100.0;
    morphing(val);
}

