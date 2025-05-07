//
// Created by Conrad Mercer on 5/5/2025.
//
#include "Buttons.h"
#include <QGraphicsProxyWidget>

Buttons::Buttons(QWidget *parent, Books *books, Scene *scene, int window_x, int window_y): QWidget(parent), book_ref(books), scene_ref(scene) {
}

Buttons::~Buttons() {
    push_button_list.clear();
}


void Buttons::add_book_button() {

    //allowing me to access the pos of the different books
    const auto& book_list = book_ref->get_book_struct_list();

    //no books - default
    if(book_list.isEmpty()){
        button_struct_list.append(
                button_details_strc("yellow", "black", true, 150, 100, 50,50, "circle")
                );
    }

    else{
        //last book
        int end = book_list.size() - 1;

        button_struct_list.append(
                button_details_strc("yellow", "black", true, 150, 50, book_list[end].pos_x + 25, book_list[end].pos_y + 50, "circle")
                );
    }

}

void Buttons::show_buttons(const QVector<QString> &button_text_list) {
    //ensures no duplicates
    push_button_list.clear();

    if (!scene_ref) {
        qDebug() << "Error: No reference available in Books object.";
        return;
    }

    QGraphicsScene *scene = const_cast<QGraphicsScene *>(scene_ref->get_scene());
    if (!scene) {
        qDebug() << "Error: Invalid scene in Scene object.";
        return;
    }

    //num of buttons
    int num_buttons = qMin(button_struct_list.size(), button_text_list.size());

    for (int i = 0; i < num_buttons; i++) {
        const QString& button_text = button_text_list[i];

        //make new buttons
        QPushButton* button = new QPushButton(button_text);

        //essential to making it a circle
        int size = qMin(button_struct_list[i].width, button_struct_list[i].height);
        button->setFixedSize(size,size);

        QColor temp_color = button_struct_list[i].button_color;
        QString darker_color = temp_color.darker(110).name();

        QString style_sheet = QString(
                "QPushButton {"
                "  background-color: %1;"
                "  color: %2;"
                "  border: %3;"
                "}"
                "QPushButton:hover {"
                "  background-color: %4;"
                "}"
        )
        .arg(button_struct_list[i].button_color)
        .arg(button_struct_list[i].text_color)
        .arg(button_struct_list[i].border ? "1px solid black" : "none")
        .arg(darker_color);

        if (button_struct_list[i].tag == "circle") {
            style_sheet += "QPushButton { border-radius: " + QString::number(button_struct_list[i].height / 2) + "px; }";
        }


        button->setStyleSheet(style_sheet);
        push_button_list.append(button);

        QGraphicsProxyWidget *button_wrapper = scene->addWidget(button);
        button_wrapper->setPos(button_struct_list[i].pos_x, button_struct_list[i].pos_y);
    }

    scene_ref->update_scene_rect();
}

