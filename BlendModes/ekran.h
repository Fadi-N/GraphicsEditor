#ifndef EKRAN_H
#define EKRAN_H

#include <QWidget>

class Ekran : public QWidget
{
    Q_OBJECT
public:
    QImage im, im2, im3, im4;
    explicit Ekran(QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *);
    void blend(QImage &b, QImage f, float alpha, int mode, QImage &o);
    void blending();
    uchar normal(uchar l, uchar r);
    uchar multiply(uchar l, uchar r);
    uchar lighten(uchar l, uchar r);
    uchar darken(uchar l, uchar r);
    uchar screeen(uchar l, uchar r);
signals:
    void signalSlider(int);
    void signalComboBox(int);

public slots:
    void on_comboBox_activated(int);
    void on_horizontalSlider_sliderMoved(int);
    void on_listWidget_currentRowChanged(int);
};

#endif // EKRAN_H
