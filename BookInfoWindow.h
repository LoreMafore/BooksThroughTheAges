//
// Created by Conrad Mercer on 5/10/2025.
//

#ifndef BOOKSTHROUGHTHEAGES_BOOKINFOWINDOW_H
#define BOOKSTHROUGHTHEAGES_BOOKINFOWINDOW_H
#include <QMainWindow>
#include <QApplication>
#include "BookInfo.h"
class BookInfoWindow : public QMainWindow{
    BookInfoWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("Book Info");
        resize(800, 600);

        // Create the Text widget
        Text *bookInfoWidget = new Text(this, width(), height());

        // Set as central widget
        setCentralWidget(bookInfoWidget);
};

#endif //BOOKSTHROUGHTHEAGES_BOOKINFOWINDOW_H
