//
// Created by momer on 5/5/2025.
//
#include "Books.h"
#include <QBoxLayout>
#include <QGraphicsProxyWidget>
#include <QGraphicsRotation>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTransform>

Buttons::Buttons(QWidget *parent, int window_x, int window_y) : QWidget(parent) {

}

Buttons::~Buttons() {
    //Qt will delete scene and view automatically due to parent-child
    //relationships, but we clear the pointers to be safe
    scene = nullptr;
    view = nullptr;

    push_button_list.clear();
}

void Buttons::add_button(const QString &bt_clr, const QString &txt_clr, bool bord, float wdth, float hght, float x, float y){
    button_struct_list.append(button_details_strc(bt_clr, txt_clr, bord, wdth, hght, x, y));
}

void Buttons::show_buttons(const QVector<QString>& title_list) {

    //ensures no duplicates
    push_button_list.clear();

    //clean up any existing layout
    if (layout()) {
        delete layout();
    }

    QHBoxLayout *main_layout = new QHBoxLayout(this);
    main_layout->setContentsMargins(0, 0, 0, 0); // Remove margins

    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    view->setRenderHint(QPainter::Antialiasing);
    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    view->setFrameStyle(QFrame::NoFrame); // Remove the frame

    main_layout->addWidget(view);
    setLayout(main_layout);

    //number of buttons
    int num_buttons = qMin(button_struct_list.size(), title_list.size());

    if (button_struct_list.isEmpty() && !title_list.isEmpty()) {
        // Add default button for each title
        for (int i = 0; i < title_list.size(); i++) {
            button_struct_list.append(button_details_strc("tan", "black", true, 150, 40, 50 +i*50, 50));
        }
        num_buttons = title_list.size();
    }


    for(int i = 0; i< num_buttons;i ++)
    {
        QPushButton* button = new QPushButton();
        button->setText(title_list[i]);

        button->setGeometry(
                button_struct_list[i].pos_x,
                button_struct_list[i].pos_y,
                button_struct_list[i].width,
                button_struct_list[i].height
        );

        //colors of button and text
        QString style_sheet = QString(
                "QPushButton {"
                "   background-color: %1;"
                "   color: %2;"
        ).arg(button_struct_list[i].button_color).arg(button_struct_list[i].text_color);

        //border around button
        if(button_struct_list[i].border){
            style_sheet += "    border: 1px solid black";
        }
        else{
            style_sheet += "    border: none";
        }

        //position and size
        style_sheet += "}";

        button->setStyleSheet(style_sheet);
        push_button_list.append(button);

        QGraphicsProxyWidget *button_wrapper = scene->addWidget(button);

        QTransform rotate;
        rotate.rotate(90);
        button_wrapper->setTransform(rotate);


        button_wrapper->setPos(button_struct_list[i].pos_x, button_struct_list[i].pos_y);

        //set rotation to middle of button
        button_wrapper->setTransformOriginPoint(button->width()/2, button->height()/2);

    }

    if(num_buttons == 0){
        printf("No Buttons");
    }

    scene->setSceneRect(scene->itemsBoundingRect());
}