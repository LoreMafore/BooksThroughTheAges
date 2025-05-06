//
// Created by momer on 5/5/2025.
//

#ifndef BOOKSTHROUGHTHEAGES_BOOKS_H
#define BOOKSTHROUGHTHEAGES_BOOKS_H

#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QVector>
#include <QGraphicsScene>
#include <QGraphicsView>

class Books : public QWidget{
private:
    struct books_details_strc {
        QString book_color;
        QString text_color;
        bool border;
        float width;
        float height;
        float pos_x;
        float pos_y;

        books_details_strc(const QString &bt_clr, const QString &txt_clr, bool bord, float wdth, float hght, float x, float y)
                : book_color(bt_clr), text_color(txt_clr), border(bord), width(wdth), height(hght), pos_x(x), pos_y(y) {};

    };

    QVector<books_details_strc> book_struct_list;
    QVector<QPushButton*> push_book_list;

    QGraphicsScene *scene;
    QGraphicsView *view;

public:

    explicit Books(QWidget * parent = nullptr, int window_x = 0, int window_y = 0);

    ~Books() override;

    void add_book(const QString &bt_clr, const QString &txt_clr, bool bord, float wdth, float hght, float x, float y);

    void show_books(const QVector<QString>& title_list);

    const QVector<books_details_strc>& get_book_struct_list(){
        return book_struct_list;
    }

    QGraphicsScene *get_scene(){
        return scene;
    }

};


#endif //BOOKSTHROUGHTHEAGES_BOOKS_H
