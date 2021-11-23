#ifndef EKRAN_H
#define EKRAN_H

#include <QWidget>

class Ekran : public QWidget
{
    Q_OBJECT
public:
    QImage im;
    explicit Ekran(QWidget *parent = nullptr);
    int dx = 1, dy= 1;
    float sx = 1, sy = 1, alpha, shx = 0, shy = 0, M[3*3];
    float pom1[3*3] = {1, 0, -220, 0, 1, -180, 0, 0, 1};
    float pom2[3*3] = {1, 0, 220, 0, 1, 180, 0, 0, 1};
    int wynik1[3*1];

protected:
    std::vector<int> point{220, 50, 300, 140, 300, 240, 160, 240, 160, 140, 220, 50};
    std::vector<int> pointp{220, 50, 300, 140, 300, 240, 160, 240, 160, 140, 220, 50};
    void wstawPiksel(int x, int y, int r, int g, int b);
    void BresenhamLine(int x1, int y1, int x2, int y2);
    void paintEvent(QPaintEvent *);
    void draw();
    void macierz();
    void clear();
signals:

public slots:
    void on_right_left_valueChanged(int value);
    void on_shearing2_valueChanged(int value);
    void on_up_down_valueChanged(int value);
    void on_rotation_valueChanged(int value);
    void on_scaling_rl_valueChanged(int value);
    void on_scaling_ud_valueChanged(int value);
    void on_shearing1_valueChanged(int value);
    void on_reset_clicked();
};

#endif // EKRAN_H
