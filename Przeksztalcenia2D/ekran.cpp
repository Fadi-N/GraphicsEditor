#include "ekran.h"
#include <QPainter>
#include <QMouseEvent>

QImage img, img2;

Ekran::Ekran(QWidget *parent) : QWidget(parent)
{
    im = QImage(800,800, QImage::Format_RGB32);
    for(int y=0; y<im.height(); y++){
        uchar *tab = im.scanLine(y);
        for(int x=0; x<im.width(); ++x){
            tab[x*4] = 0;
            tab[x*4+1] = 0;
            tab[x*4+2] = 0;
            tab[x*4+3] = 255;
        }
    }
    draw();
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

void Ekran::macierz(){
    int n=3, m=3, r=3;
    int T[3*3] = {1, 0, dx, 0, 1, dy, 0, 0, 1}; //macierz translacji
    double R[3*3] = {cos(alpha), -sin(alpha), 0, sin(alpha), cos(alpha), 0, 0, 0, 1}; //rotacja
    float S[3*3] = {sx, 0, 0, 0, sy, 0, 0, 0, 1}; //skalowalnosc
    float Shx[3*3] = {1, shx, 0, 0, 1, 0, 0, 0, 1}; //pochylenie
    float Shy[3*3] = {1, 0, 0, shy, 1, 0 ,0 ,0, 1}; //pochylenie

    float P[3*3] = {1, 0, 0, 0, 1, 0, 0, 0, 1}; //pomocnicza macierz
    float wynik;
    float P1[3*3];

    //translacja
    for (int i=0; i<n; i++) {
        for (int j=0; j<r; j++) {
            wynik = 0;
            for (int p=0; p<m; p++) {
                wynik += P[i*m+p] * T[p*r+j];
            }
            P1[i*r+j] = wynik;
        }
    }

    //rotacja
    for (int i=0; i<n; i++) {
        for (int j=0; j<r; j++) {
            wynik =0;
            for (int p=0; p<m; p++) {
                wynik += P1[i*m+p] * pom2[p*r+j];
            }
            P[i*r+j] = wynik;
        }
    }
    for (int i=0; i<n; i++) {
        for (int j=0; j<r; j++) {
            wynik =0;
            for (int p=0; p<m; p++) {
                wynik += P[i*m+p] * R[p*r+j];
            }
            P1[i*r+j] = wynik;
        }
    }

    for (int i=0; i<n; i++) {
        for (int j=0; j<r; j++) {
            wynik =0;
            for (int p=0; p<m; p++) {
                wynik += P1[i*m+p] * pom1[p*r+j];
            }
            P[i*r+j] = wynik;
        }
    }
    //skalowalnosc
    for (int i=0; i<n; i++) {
        for (int j=0; j<r; j++) {
            wynik =0;
            for (int p=0; p<m; p++) {
                wynik += P[i*m+p] * pom2[p*r+j];
            }
            P1[i*r+j] = wynik;
        }
    }
    for (int i=0; i<n; i++) {
        for (int j=0; j<r; j++) {
            wynik =0;
            for (int p=0; p<m; p++) {
                wynik += P1[i*m+p] * S[p*r+j];
            }
            P[i*r+j] = wynik;
        }
    }

    for (int i=0; i<n; i++) {
        for (int j=0; j<r; j++) {
            wynik =0;
            for (int p=0; p<m; p++) {
                wynik += P[i*m+p] * pom1[p*r+j];
            }
            P1[i*r+j] = wynik;
        }
    }

    //pochylenie shx
    for (int i=0; i<n; i++) {
        for (int j=0; j<r; j++) {
            wynik =0;
            for (int p=0; p<m; p++) {
                wynik += P1[i*m+p] * pom2[p*r+j];
            }
            P[i*r+j] = wynik;
        }
    }
    for (int i=0; i<n; i++) {
        for (int j=0; j<r; j++) {
            wynik =0;
            for (int p=0; p<m; p++) {
                wynik += P[i*m+p] * Shx[p*r+j];
            }
            P1[i*r+j] = wynik;
        }
    }

    for (int i=0; i<n; i++) {
        for (int j=0; j<r; j++) {
            wynik =0;
            for (int p=0; p<m; p++) {
                wynik += P1[i*m+p] * pom1[p*r+j];
            }
            P[i*r+j] = wynik;
        }
    }

    //pochylenie shy
    for (int i=0; i<n; i++) {
        for (int j=0; j<r; j++) {
            wynik =0;
            for (int p=0; p<m; p++) {
                wynik += P[i*m+p] * pom2[p*r+j];
            }
            P1[i*r+j] = wynik;
        }
    }
    for (int i=0; i<n; i++) {
        for (int j=0; j<r; j++) {
            wynik =0;
            for (int p=0; p<m; p++) {
                wynik += P1[i*m+p] * Shy[p*r+j];
            }
            P[i*r+j] = wynik;
        }
    }

    for (int i=0; i<n; i++) {
        for (int j=0; j<r; j++) {
            wynik =0;
            for (int p=0; p<m; p++) {
                wynik += P[i*m+p] * pom1[p*r+j];
            }
            M[i*r+j] = wynik;
        }
    }

}

void Ekran::clear(){
    for(int y=0; y<im.height(); y++){
        uchar *tab = im.scanLine(y);
        for(int x=0; x<im.width(); ++x){
            tab[x*4] = 0;
            tab[x*4+1] = 0;
            tab[x*4+2] = 0;
            tab[x*4+3] = 255;
        }
    }
}

void Ekran::draw(){
    int m=3, n=3, r=1, B[3*1], wynik;
    clear();
    macierz();
    for (int q=0; q<12; q+=2) {
        //qDebug("FOR");
        B[0] = point[q];
        B[1] = point[q+1];
        B[2] = 1;
        //qDebug("B = %d %d %d", B[0], B[1], B[2]);
        for (int i=0; i<n; i++)
            //qDebug("FOR_2");
            for (int j=0; j<r; j++)
            {
                //qDebug("FOR_3");
                wynik = 0;
                for (int p=0; p<m; p++){
                    wynik += M[i*m+p] * B[p*r+j];
                }
                wynik1[i*r+j] = wynik;
            }

        pointp[q] = wynik1[0];
        pointp[q+1] = wynik1[1];
    }

    for (int i=0; i<10; i+=2){
        BresenhamLine(pointp[i], pointp[i+1], pointp[i+2], pointp[i+3]);
    }
    update();
}



void Ekran::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.fillRect(0, 0, width(), height(), Qt::blue);
    p.drawImage(0, 0, im);
}

void Ekran::on_right_left_valueChanged(int value){
    qDebug("%d", value);
    dx = value;
    draw();

}

void Ekran::on_up_down_valueChanged(int value){
    qDebug("%d", value);
    dy = value;
    draw();

}

void Ekran::on_rotation_valueChanged(int value){
    qDebug("%d", value);
    alpha = value * M_PI / 180.0;
    draw();
}

void Ekran::on_scaling_rl_valueChanged(int value){
    qDebug("%d", value);
    sx = value/400.0;
    draw();
}

void Ekran::on_scaling_ud_valueChanged(int value){
    qDebug("%d", value);
    sy = value/400.0;
    draw();
}

void Ekran::on_shearing1_valueChanged(int value){
    qDebug("%d", value);
    shx = value/100.0;
    draw();
}

void Ekran::on_shearing2_valueChanged(int value){
    qDebug("%d", value);
    shy = value/100.0;
    draw();
}

void Ekran::on_reset_clicked(){
    dx = 1;
    dy = 1;
    sx = 1;
    sy = 1;
    alpha = 0;
    shx = 0;
    shy = 0;
    draw();
}
