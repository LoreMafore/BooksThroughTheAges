//
// Created by Conrad Mercer on 4/29/2025.
//
#ifndef BOOKSTHROUGHTHEAGES_BOOKINFO_H
#define BOOKSTHROUGHTHEAGES_BOOKINFO_H
#include <QWidget>
#include <QPainter>

class TitleText : public QWidget{

private:
    int x_pos;
    int y_pos;
    int x_dis = 10;
    int y_dis = 3;

public:
    //constructor
    TitleText(int window_x, int window_y) : QWidget(){
        //Unsure bout the value but top middle
        x_pos = window_x/x_dis;
        y_pos = window_y/y_dis;
    }

    void paintEvent(QPaintEvent* ) override
    {
        QPainter painter(this);
        QFont font = painter.font();
        font.setPixelSize(24);
        painter.setFont(font);
        painter.setBrush(Qt::GlobalColor::black);

        const QRect rectangle = QRect(1, 1, 100, 50);
        QRect bounding_rect;
        painter.drawText(rectangle, 0, tr("Title"), &bounding_rect);
    }
};

void _draw_info(int window_x, int window_y)
{
    TitleText title(window_x, window_y);
    title.show();
}






#endif //BOOKSTHROUGHTHEAGES_BOOKINFO_H
