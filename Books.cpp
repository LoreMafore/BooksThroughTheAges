//
// Created by momer on 5/5/2025.
//
#include "Books.h"
#include <QBoxLayout>
#include <QGraphicsProxyWidget>
#include <QGraphicsRotation>
#include <QTransform>

Books::Books(QWidget *parent, Scene *scene, int window_x, int window_y): QWidget(parent), scene_ref(scene) {
}

Books::~Books() {
    push_book_list.clear();
}

void Books::add_book(const QString &bt_clr, const QString &txt_clr, bool bord, float wdth, float hght, float x, float y){
    book_struct_list.append(books_details_strc(bt_clr, txt_clr, bord, wdth, hght, x, y));
}

void Books::show_books(const QVector<QString>& title_list) {

    //ensures no duplicates
    push_book_list.clear();

    if(!scene_ref){
        qDebug() << "Error: No scene reference available in Books object.";
        return;
    }

    QGraphicsScene *scene = const_cast<QGraphicsScene *>(scene_ref->get_scene());
    if(!scene){
        qDebug() << "Error: Invalid scene in Scene object.";
        return;
    }

    //number of books
    int num_books = qMin(book_struct_list.size(), title_list.size());

    if (book_struct_list.isEmpty() && !title_list.isEmpty()) {
        // Add default book for each title
        for (int i = 0; i < title_list.size(); i++) {
            book_struct_list.append(books_details_strc("tan", "black", true, 150, 40, 50 +i*50, 50));
        }
        num_books = title_list.size();
    }


    for(int i = 0; i< num_books;i ++)
    {
        QPushButton* book = new QPushButton();
        book->setText(title_list[i]);

        book->setGeometry(
                book_struct_list[i].pos_x,
                book_struct_list[i].pos_y,
                book_struct_list[i].width,
                book_struct_list[i].height
        );

        QColor temp_color = book_struct_list[i].book_color;
        QString darker_color = temp_color.darker(110).name();

        //colors of book and text
        QString style_sheet = QString(
                "QPushButton {"
                "   background-color: %1;"
                "   color: %2;"
                "   border: %3"
                "}"
                "QPushButton:hover {"
                "  background-color: %4;"
                "}"
        )
       .arg(book_struct_list[i].book_color)
       .arg(book_struct_list[i].text_color)
       .arg(book_struct_list[i].border ? "1px solid black" : "none")
       .arg(darker_color);

        book->setStyleSheet(style_sheet);
        push_book_list.append(book);

        QGraphicsProxyWidget *book_wrapper = scene->addWidget(book);

        QTransform rotate;
        rotate.rotate(90);
        book_wrapper->setTransform(rotate);


        book_wrapper->setPos(book_struct_list[i].pos_x, book_struct_list[i].pos_y);

        //set rotation to middle of book
        book_wrapper->setTransformOriginPoint(book->width()/2, book->height()/2);

    }

    if(num_books == 0){
        printf("No books");
    }

    scene->setSceneRect(scene->itemsBoundingRect());
}

