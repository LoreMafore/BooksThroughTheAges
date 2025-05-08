//
// Created by Conrad Mercer on 5/7/2025.
//

#ifndef BOOKSTHROUGHTHEAGES_BOOKCARD_H
#define BOOKSTHROUGHTHEAGES_BOOKCARD_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class BookCard : public QWidget {
Q_OBJECT
private slots:
    void on_select_clicked();
    void on_cover_image_downloaded();

public:

    QString title;
    QString author;
    QString cover_id;
    QString book_id;
    QLabel *cover_label;
    QLabel *title_label;
    QLabel *author_label;
    QPushButton *select_button;
    QNetworkAccessManager *manager;
    QNetworkReply *cover_reply;

    explicit BookCard(const QString &Title, const QString &Author, const QString &Cover, const QString &Book_id, QWidget *parent = nullptr);

    signals:
        void book_selected(const QString &book_id);

};


#endif //BOOKSTHROUGHTHEAGES_BOOKCARD_H
