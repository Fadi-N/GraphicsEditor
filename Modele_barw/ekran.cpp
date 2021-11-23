#include "ekran.h"
#include <QPainter>
#include <QMouseEvent>

float c, r1, g1, b1, m;

Ekran::Ekran(QWidget *parent) : QWidget(parent)
{
    im = QImage(256,256, QImage::Format_RGB32);
    int line = 255;

    for(int y=0; y<im.height(); y++){
        uchar *tab = im.scanLine(line);
        for(int x=0; x<im.width(); ++x){
            tab[x*4] = y;
            tab[x*4+1] = x;
            tab[x*4+2] = 0;
        }
        line--;
    }

}


void Ekran::RGB_R(int r)
{
    im2 = im.copy();
    int line = 255;

    for(int y=0; y<=255; y++){
        uchar *tab = im.scanLine(line);
        for(int x=0; x<=255; ++x){
            tab[x*4] = y;
            tab[x*4+1] = x;
            tab[x*4+2] = r;
        }
        line--;
    }
    update();
}

void Ekran::RGB_G(int g)
{
    im2 = im.copy();
    int line = 255;
    for(int y=0; y<=255; y++){
        uchar *tab = im.scanLine(line);
        for(int x=0; x<=255; ++x){
            tab[x*4] = y;
            tab[x*4+1] = g;
            tab[x*4+2] = x;
        }
        line--;
    }
    update();
}
void Ekran::RGB_B(int b)
{
    im2 = im.copy();
    int line = 255;
    for(int y=0; y<=255; y++){
        uchar *tab = im.scanLine(line);
        for(int x=0; x<=255; ++x){
            tab[x*4] = b;
            tab[x*4+1] = y;
            tab[x*4+2] = x;
        }
        line--;
    }
    update();
}

void Ekran::HSV_H(int h)
{
    im2 = im.copy();
    int line = 255;
    for(int y=0; y<im.height(); y++){
        uchar *tab = im.scanLine(line);
        for(int x=im.width()-1; x>=0; --x){
            HSV_RGB(h, y/(float)im.height(), x/(float)im.width());
            tab[x*4] = (b1+m)*255;
            tab[x*4+1] = (g1+m)*255;
            tab[x*4+2] = (r1+m)*255;
        }
        line--;
    }
    update();
}

void Ekran::HSV_S(int s)
{
    im2 = im.copy();
    int line = 255;
    for(int y=0; y<im.height(); y++){
        uchar *tab = im.scanLine(line);
        for(int x=im.width()-1; x>=0; --x){
            HSV_RGB(x*360/(float)im.height(), s/100.0, y/(float)im.height());
            tab[x*4] = (g1+m)*255;
            tab[x*4+1] = (b1+m)*255;
            tab[x*4+2] = (r1+m)*255;
        }
        line--;
    }
    update();
}

void Ekran::HSV_V(int v)
{
    im2 = im.copy();
    int line = 255;
    for(int y=0; y<im.height(); y++){
        uchar *tab = im.scanLine(line);
        for(int x=im.width()-1; x>=0; --x){
            HSV_RGB(x*360/(float)im.height(), y/(float)im.height(), v/100.0);
            tab[x*4] = (g1+m)*255;
            tab[x*4+1] = (b1+m)*255;
            tab[x*4+2] = (r1+m)*255;
        }
        line--;
    }
    update();
}

void Ekran::HSV_RGB(float h, float s, float v){

    c = v * s;
    float j = h/60;
    float X = c * (1 - abs(fmod(j, 2)-1));
    if(j>=0 && j<=1){
        b1 = 0;
        g1 = X;
        r1 = c;
    }else if(j>1 && j<=2){
        b1 = 0;
        g1 = c;
        r1 = X;
    }else if(j>2 && j<=3){
        b1 = X;
        g1 = c;
        r1 = 0;
    }else if(j>3 && j<=4){
        b1 = c;
        g1 = X;
        r1 = 0;
    }else if(j>4 && j<=5){
        b1 = c;
        g1 = 0;
        r1 = X;
    }else if(j>5 && j<=6){
        b1 = X;
        g1 = 0;
        r1 = c;
    }else{
        b1 = 0;
        g1 = 0;
        r1 = 0;
    }

    m = v - c;

}

void Ekran::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.drawImage(0, 35, im);
}
