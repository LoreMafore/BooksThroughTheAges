//
// Created by Conrad Mercer on 5/5/2025.
//
#ifndef BOOKSTHROUGHTHEAGES_BUTTONS_H
#define BOOKSTHROUGHTHEAGES_BUTTONS_H
#include "Books.h"
#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QVector>
#include <QGraphicsScene>
#include <QGraphicsView>

class Buttons : public QWidget{
private:
    struct button_details_strc {
        QString button_color;
        QString text_color;
        //determines shape
        QString tag;
        bool border;
        float width;
        float height;
        float pos_x;
        float pos_y;

        button_details_strc(const QString &bt_clr, const QString &txt_clr, bool bord, float wdth, float hght, float x, float y, const QString& shape)
                : button_color(bt_clr), text_color(txt_clr), border(bord), width(wdth), height(hght), pos_x(x), pos_y(y), tag(shape){};

    };

    QVector<button_details_strc> button_struct_list;
    QVector<QPushButton*> push_button_list;

    Books *book_ref;

public:

    explicit Buttons(QWidget * parent = nullptr, Books* books = nullptr, int window_x = 0, int window_y = 0);

    ~Buttons() override;

    void add_book_button();

    void show_buttons(const QVector<QString>& button_text_list);
};
#endif //BOOKSTHROUGHTHEAGES_BUTTONS_H
