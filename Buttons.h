//
// Created by Conrad Mercer on 5/5/2025.
//
#ifndef BOOKSTHROUGHTHEAGES_BUTTONS_H
#define BOOKSTHROUGHTHEAGES_BUTTONS_H
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
        bool border;
        float width;
        float height;
        float pos_x;
        float pos_y;

        button_details_strc(const QString &bt_clr, const QString &txt_clr, bool bord, float wdth, float hght, float x, float y)
                : button_color(bt_clr), text_color(txt_clr), border(bord), width(wdth), height(hght), pos_x(x), pos_y(y) {};

    };

    QVector<button_details_strc> button_struct_list;
    QVector<QPushButton*> push_button_list;

    QGraphicsScene *scene;
    QGraphicsView *view;

public:

    explicit Buttons(QWidget * parent = nullptr, int window_x = 0, int window_y = 0);

    ~Buttons() override;

    void add_book_button();

    void show_buttons(const QVector<QString>& title_list);
};
#endif //BOOKSTHROUGHTHEAGES_BUTTONS_H
