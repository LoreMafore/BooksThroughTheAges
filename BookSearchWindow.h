//
// Created by momer on 5/7/2025.
//

#ifndef BOOKSTHROUGHTHEAGES_BOOKSEARCHWINDOW_H
#define BOOKSTHROUGHTHEAGES_BOOKSEARCHWINDOW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>


class Book_Search_Window : public QDialog{
private slots:
    void on_search_clicked();

public:
    explicit Book_Search_Window(QWidget *parent = nullptr);

    QLineEdit * search_text_box;

    QString get_search_text()const{
        return search_text_box ? search_text_box->text() : QString();
    }
};

#endif //BOOKSTHROUGHTHEAGES_BOOKSEARCHWINDOW_H
