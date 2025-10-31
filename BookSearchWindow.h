//
// Created by Conrad Mercer on 5/7/2025.
//

#ifndef BOOKSTHROUGHTHEAGES_BOOKSEARCHWINDOW_H
#define BOOKSTHROUGHTHEAGES_BOOKSEARCHWINDOW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QScrollArea>
#include <QNetworkAccessManager>
#include <QSslConfiguration>
#include <QNetworkRequest>


class Book_Search_Window : public QDialog{
Q_OBJECT
private slots:
    void on_search_clicked();
    void on_book_selected(const QString &book_id);
    void clear_search_results();
//    void fetchBookDetails(const QString &edition_id);

public:
    explicit Book_Search_Window(QWidget *parent = nullptr);

    QLineEdit * search_text_box;
    QVBoxLayout *main_layout;
    QScrollArea *scroll_area;
    QWidget *scroll_content;
    QVBoxLayout *scroll_layout;
    QNetworkAccessManager *network_manager;
    QLabel *status_label;
    QString selected_book_id;
    QString selected_book_title;
    QString selected_book_author;
    QString selected_book_pages;
    QPixmap selected_book_cover;

};

#endif //BOOKSTHROUGHTHEAGES_BOOKSEARCHWINDOW_H
