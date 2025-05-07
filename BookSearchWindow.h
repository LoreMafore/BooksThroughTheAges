//
// Created by momer on 5/7/2025.
//

#ifndef BOOKSTHROUGHTHEAGES_BOOKSEARCHWINDOW_H
#define BOOKSTHROUGHTHEAGES_BOOKSEARCHWINDOW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

class Book_Search_Window : public QDialog{
public:
    Book_Search_Window(QWidget *parent = nullptr) : QDialog(parent){
        setWindowTitle("New Book");
        setModal(true);

        QVBoxLayout *layout = new QVBoxLayout(this);
        QLabel *label = new QLabel("Hello World", this);

        QPushButton *close_button = new QPushButton("Close", this);
        connect(close_button, &QPushButton::clicked, this, &QDialog::accept);

        layout->addWidget(label);
        setLayout(layout);
        resize(300,100);
    }
};

#endif //BOOKSTHROUGHTHEAGES_BOOKSEARCHWINDOW_H
