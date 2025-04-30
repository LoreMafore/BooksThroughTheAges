//
// Created by Conrad Mercer on 4/29/2025.
//
#ifndef BOOKSTHROUGHTHEAGES_BOOKINFO_H
#define BOOKSTHROUGHTHEAGES_BOOKINFO_H
#include <QWidget>
#include <QPainter>
#include <QMainWindow>

class Text : public QWidget{
private:
    struct text_items_strc {
        QString text;
        QFont font;
        QColor color;
        QPoint pos;
        int width;
        bool is_word_wrap;


        text_items_strc(const QString& txt, const QFont& f, const QColor& clor, const QPoint& position, int w = 0, bool wrap = false)
        : text(txt), font(f), color(clor),  pos(position), width(w), is_word_wrap(wrap){};
    };

    QVector<text_items_strc> text_items;

public:
    Text(QWidget *parent = nullptr, int window_x = 0, int window_y = 0) : QWidget(parent){
        QFont font1;
        font1.setPixelSize(16);
        int title_x = window_x/4;
        int title_y = window_y/6;
        text_items.append(text_items_strc("Title:", font1, QColor(0,0,255), QPoint(title_x, title_y), 200, true));

        QFont font2;
        font1.setPixelSize(16);
        int author_x = window_x/4;
        int author_y = window_y/4.5;
        text_items.append(text_items_strc("Author:", font1, Qt::black, QPoint(author_x, author_y), 200, true));


    }

    void add_text(const QString& text, QFont& font, const QColor& color, int &x, int &y, int width = 0, bool wrap = false){
        text_items.append(text_items_strc(text,font,color, QPoint(x,y), width, wrap));
        update();
    }

    void paintEvent(QPaintEvent *event) override{
        QPainter painter(this);

        for(const text_items_strc& item : text_items)
        {
            painter.setFont(item.font);
            painter.setPen(item.color);

            if(item.is_word_wrap && item.width > 0)
            {
                QRect rect(item.pos.x(), item.pos.y(), item.width, 1000/*Height*/);
                painter.drawText(rect,Qt::TextWordWrap, item.text);
            }
            else
            {
                painter.drawText(item.pos, item.text);
            };
        }
    }

};



#endif //BOOKSTHROUGHTHEAGES_BOOKINFO_H
