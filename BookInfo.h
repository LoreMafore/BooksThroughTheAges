//
// Created by Conrad Mercer on 4/29/2025.
//
#ifndef BOOKSTHROUGHTHEAGES_BOOKINFO_H
#define BOOKSTHROUGHTHEAGES_BOOKINFO_H
#include <QWidget>
#include <QPainter>
#include <QMainWindow>
#include <QFile>
#include <QDebug>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

class Text : public QWidget{
private:
    //Struct that allows us to have more that one text
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
    QNetworkAccessManager *manager;
    QString book_title;
    QString book_author;
    QString book_pages;


public:
    explicit Text(QWidget *parent = nullptr, int window_x = 0, int window_y = 0);

    ~Text() override;

    //Get book_title and author as strings
    void get_book_info(const QString& workId, const std::function<void(QString, QString, QString)>& callback);

    //Fetch then update the UI
    void fetch_book_info(const QString& workId);

    //Add text
    void add_text(const QString& text, QFont& font, const QColor& color, int &x, int &y, int width = 0, bool wrap = false);

    //Make background
    void paintEvent(QPaintEvent *event) override;

};



#endif //BOOKSTHROUGHTHEAGES_BOOKINFO_H
