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


class Book_Search_Window : public QDialog{
Q_OBJECT
private slots:
    void on_search_clicked();
    void on_book_selected(const QString &book_id);

public:
    explicit Book_Search_Window(QWidget *parent = nullptr);

    QLineEdit * search_text_box;
    QVBoxLayout *main_layout;
    QScrollArea *scroll_area;
    QWidget *scroll_content;
    QVBoxLayout *scroll_layout;
    QNetworkAccessManager *network_manager;
    QString selected_book_id;
    QLabel *status_label;
    QPushButton *select_button;

    QString get_search_text(){
        return search_text_box ? search_text_box->text() : QString();
    }

    QString get_selected_book_id(){
        return selected_book_id;
    }

    void clear_search_results();
};

#endif //BOOKSTHROUGHTHEAGES_BOOKSEARCHWINDOW_H
