#include "ekran.h"
#include <QPainter>
#include <QMouseEvent>

int mode = 0, row = 0, rowFixed;
double alpha = 1.0, alphaFixed;
QImage img, img2;

struct Layer{
    QImage im;
    double alpha = 1.0;
    int mode;
}layer[10];

Ekran::Ekran(QWidget *parent) : QWidget(parent)
{
    layer[0].im = QImage("C:/Users/Fadi/Desktop/Grafika_Komputerowa/zadania/BlendModes/car.jpg");
    layer[0].im = layer[0].im.scaled(750, 630);
    if(layer[0].im.isNull()){
        qDebug("LOADING ERROR");
    }

    layer[1].im = QImage("C:/Users/Fadi/Desktop/Grafika_Komputerowa/zadania/BlendModes/chess.jpg");
    layer[1].im = layer[1].im.scaled(750, 630);
    if(layer[1].im.isNull()){
        qDebug("LOADING ERROR");
    }

    layer[2].im = QImage("C:/Users/Fadi/Desktop/Grafika_Komputerowa/zadania/BlendModes/tree.jpg");
    layer[2].im = layer[2].im.scaled(750, 630);
    if(layer[2].im.isNull()){
        qDebug("LOADING ERROR");
    }

    layer[3].im = QImage(750, 630, QImage::Format_RGB32);
    for(int y=0; y<layer[3].im.height(); y++){
        uchar *tab = layer[3].im.scanLine(y);
        for(int x=0; x<layer[3].im.width(); ++x){
            tab[x*4] = 255;
            tab[x*4+1] = 255;
            tab[x*4+2] = 255;
        }
    }
    img = QImage(750, 630, QImage::Format_RGB32);
}

void Ekran::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.drawImage(0, 0, layer[3].im);
    p.drawImage(0, 0, layer[2].im);
    p.drawImage(0, 0, layer[1].im);
    p.drawImage(0, 0, layer[0].im);
    p.drawImage(0, 0, img);
}

uchar Ekran::normal(uchar l, uchar r){
    return r;
}

uchar Ekran::multiply(uchar l, uchar r){
    return l*r >> 8;
}

uchar Ekran::lighten(uchar l, uchar r){
    if(l>r){
        return l;
    }else{
        return r;
    }
}

uchar Ekran::darken(uchar l, uchar r){
    if(l<r){
        return l;
    }else{
        return r;
    }
}

uchar Ekran::screeen(uchar l, uchar r){
    return 255 - ((255-l) * (255-r) >> 8);
}

void Ekran::blending(){

    for (int i=2; i>=0; i--) {
        blend(img, layer[i].im, layer[i].alpha, layer[i].mode, img);
    }
    update();
}

void Ekran::blend(QImage &b, QImage f, float alpha, int m, QImage &o){

    qDebug("ALPHA: %f", alpha);
    //qDebug("MODE: %d", mode);

    for (int y=0; y<b.height(); ++y) {

        uchar *FPB = b.scanLine(y);
        uchar *FPF = f.scanLine(y);
        uchar *FPO = o.scanLine(y);

        //qDebug("Y: %d", y);

        for (int x=0; x<b.width(); ++x) {
            //qDebug("X: %d", x);
            uchar c, d, e, f;
            if(m==0){
                c = normal(FPB[x*4], FPF[x*4]);
                d = normal(FPB[x*4+1], FPF[x*4+1]);
                e = normal(FPB[x*4+2], FPF[x*4+2]);
                f = normal(FPB[x*4+3], FPF[x*4+3]);
            }else if(m==1){
                c = multiply(FPB[x*4], FPF[x*4]);
                d = multiply(FPB[x*4+1], FPF[x*4+1]);
                e = multiply(FPB[x*4+2], FPF[x*4+2]);
                f = multiply(FPB[x*4+3], FPF[x*4+3]);
            }else if(m==2){
                c = lighten(FPB[x*4], FPF[x*4]);
                d = lighten(FPB[x*4+1], FPF[x*4+1]);
                e = lighten(FPB[x*4+2], FPF[x*4+2]);
                f = lighten(FPB[x*4+3], FPF[x*4+3]);
            }else if(m==3){
                c = darken(FPB[x*4], FPF[x*4]);
                d = darken(FPB[x*4+1], FPF[x*4+1]);
                e = darken(FPB[x*4+2], FPF[x*4+2]);
                f = darken(FPB[x*4+3], FPF[x*4+3]);
            }else if(m==4){
                c = screeen(FPB[x*4], FPF[x*4]);
                d = screeen(FPB[x*4+1], FPF[x*4+1]);
                e = screeen(FPB[x*4+2], FPF[x*4+2]);
                f = screeen(FPB[x*4+3], FPF[x*4+3]);
            }

            FPO[x*4] = alpha * c + (1-alpha) * FPB[x*4];
            FPO[x*4+1] = alpha * d + (1-alpha) * FPB[x*4+1];
            FPO[x*4+2] = alpha * e + (1-alpha) * FPB[x*4+2];
            FPO[x*4+3] = alpha * f + (1-alpha) * FPB[x*4+3];
        }
    }

}

void Ekran::on_comboBox_activated(int index)
{
    qDebug("INDEX: %d", index);
    layer[row].mode = index;
    emit signalComboBox(layer[row].mode);
    blending();
    update();
}


void Ekran::on_horizontalSlider_sliderMoved(int a)
{
    layer[row].alpha = a / 100.0;
    blending();
    update();
}

void Ekran::on_listWidget_currentRowChanged(int currentRow)
{
    row = currentRow;
    emit signalSlider(layer[row].alpha*100.0);
    blending();
    update();
}
