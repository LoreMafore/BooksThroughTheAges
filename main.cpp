//
// Created by Conrad Mercer on 4/29/2025.
//

#include <QApplication>
#include <QMainWindow>
#include "BookInfo.h"
#include "Books.h"

class BookInfoWindow : public QMainWindow {
public:
    BookInfoWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("Book Info");
        resize(800, 600);

        // Create the Text widget
        Text *bookInfoWidget = new Text(this, width(), height());

        // Set as central widget
        setCentralWidget(bookInfoWidget);

        // Fetch book info
        bookInfoWidget->fetch_book_info("OL9639573M"); // Speaker for the Dead
    }
};

class MainWindow : public QMainWindow {
public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("Books Through The Ages");
        resize(800, 600);

        Buttons *test_button = new Buttons(this, width(), height());

        QVector<QString> button_titles;
        button_titles.append("Speaker for the Dead");
        button_titles.append("Ender's Game");
        button_titles.append("War and Peace");

        test_button->show_buttons(button_titles);

        setCentralWidget(test_button);

    }
};



int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();
}
