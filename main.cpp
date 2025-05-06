//
// Created by Conrad Mercer on 4/29/2025.
//

#include <QApplication>
#include <QMainWindow>
#include "BookInfo.h"
#include "Books.h"
#include "Buttons.h"

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

        Books *books = new Books(this, width(), height());

        QVector<QString> book_titles;
        book_titles.append("Speaker for the Dead");
        book_titles.append("Ender's Game");
        book_titles.append("War and Peace");
        book_titles.append("Harry Pottery");

        books->show_books(book_titles);

        Buttons *buttons = new Buttons(this, books);
        buttons->add_book_button();

        QVector<QString> button_text_list;
        button_text_list.append("+");

        buttons->show_buttons(button_text_list);

        setCentralWidget(books);

    }
};



int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();
}
