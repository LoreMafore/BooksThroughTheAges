//
// Created by Conrad Mercer on 5/5/2025.
//
#include "Buttons.h"
#include <QBoxLayout>
#include <QGraphicsProxyWidget>
#include <QGraphicsRotation>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTransform>

Buttons::Buttons(QWidget *parent, int window_x, int window_y) {

}

Buttons::~Buttons() {
    //Qt will delete scene and view automatically due to parent-child
    //relationships, but we clear the pointers to be safe
    scene = nullptr;
    view = nullptr;

    push_button_list.clear();
}

void Buttons::add_book_button() {
    //button_struct_list.append();
}

void Buttons::show_buttons(const QVector<QString> &title_list) {

}

