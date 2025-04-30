//
// Created by momer on 4/30/2025.
//
#ifndef BOOKSTHROUGHTHEAGES_BACKGROUND_H
#define BOOKSTHROUGHTHEAGES_BACKGROUND_H

#include <QMainWindow>
#include <QPixmap>
#include <QPalette>
#include <QDebug>
#include <QPainter>
class Background : public QWidget{
private:
    QImage background;
public:
    Background(QWidget *parent = nullptr): QWidget(parent)
    {
        background = QImage(":/images/Books.jpg");

        if (background.isNull()) {
            qDebug() << "WARNING: Failed to load image from resource path ':/images/Books.jpg'";

        }
        else {
            qDebug() << "Successfully loaded image with dimensions:" << background.width() << "x" << background.height();
        }
    }
protected:
    void paintEvent(QPaintEvent *event) override
    {
        QPainter painter(this);
        QRectF target(0.0, 0.0, width(), height());
        QRectF source(0.0, 0.0, 209.0, 148.0);
        painter.drawImage(target, background, source);
    }

};


#endif //BOOKSTHROUGHTHEAGES_BACKGROUND_H
