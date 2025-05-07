//
// Created by momer on 5/7/2025.
//

#include "BookSearchWindow.h"
#include <QLine>

Book_Search_Window::Book_Search_Window(QWidget *parent) : QDialog(parent){
    setWindowTitle("New Book");
    setModal(true);

    QVBoxLayout *layout = new QVBoxLayout(this);
    QHBoxLayout *button_layout = new QHBoxLayout(this);

    layout->addLayout(button_layout);

    search_text_box = new QLineEdit(this);
    search_text_box->setPlaceholderText("Enter book title to search");
    button_layout->addWidget(search_text_box);


    QPushButton *search_button = new QPushButton("Search", this);
    connect(search_button, &QPushButton::clicked, this, &Book_Search_Window::on_search_clicked);
    button_layout->addWidget(search_button);

    setLayout(layout);
    resize(400,150);
}

void Book_Search_Window::on_search_clicked() {
    QString search_text = search_text_box->text();
    qDebug() << search_text;
}