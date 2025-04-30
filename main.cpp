//
// Created by Conrad Mercer on 4/29/2025.
//

#include <QApplication>
#include <QPainter>
#include <QPaintEvent>
#include <QMainWindow>
#include "BookInfo.h"
#include "Background.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QMainWindow window;
    int window_x = 800;
    int window_y = 600;
    window.setWindowTitle("Info");
    window.resize(window_x, window_y);

    Background *background = new Background(&window);
    background->setGeometry(0,0,window_x, window_y);
    Text *text = new Text(&window, window_x, window_y);

    window.setCentralWidget(background);
    //window.setCentralWidget(text);

    window.show();
    return QApplication::exec();
}

