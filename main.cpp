//
// Created by Conrad Mercer on 4/29/2025.
//

#include <QApplication>
#include <QPushButton>
#include <QPainter>
#include <QMainWindow>
#include "BookInfo.h"

class TestText : public QWidget{

public:
    //constructor
    TestText() : QWidget() {};

    //overriding normal paint event
    void paintEvent(QPaintEvent *) override{
        QPainter painter(this);
        QFont font = painter.font();
        font.setPixelSize(24);
        painter.setFont(font);
        painter.setBrush(Qt::GlobalColor::black);

        const QRect rectangle = QRect(1, 1, 100, 50);
        QRect bounding_rect;
        painter.drawText(rectangle, 0, tr("Jesus"), &bounding_rect);
    }

};

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QMainWindow window;
    int window_x = 800;
    int window_y = 600;
    window.setWindowTitle("Info");
    window.resize(window_x, window_y);

    window.show();
    _draw_info(window_x, window_y);
    return QApplication::exec();
}

