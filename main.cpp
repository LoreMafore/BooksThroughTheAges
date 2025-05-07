//
// Created by Conrad Mercer on 4/29/2025.
//
#include <QApplication>
#include <QMainWindow>
#include "BookInfo.h"
#include "Books.h"
#include "Buttons.h"
#include "BookSearchWindow.h"

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
private:
    Buttons *buttons;

private slots:

    void open_book_search_window(){
        Book_Search_Window* search_window = new Book_Search_Window(this);
        search_window->setAttribute(Qt::WA_DeleteOnClose);
        search_window->exec();
    };

public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("Books Through The Ages");
        resize(800, 600);

        Scene *scene = new Scene(this, width(), height());
        setCentralWidget(scene);

        Books *books = new Books(this, scene,width(), height());

        QVector<QString> book_titles;
        book_titles<<"Speaker for the Dead" << "Ender's Game"<<"War and Peace"<<"Harry Pottery";

        books->show_books(book_titles);

        buttons = new Buttons(this, books, scene, width(), height());
        buttons->add_book_button();

        QVector<QString> button_text_list;
        button_text_list.append("+");

        buttons->show_buttons(button_text_list);

        QPushButton* add_book_button = buttons->get_button(0);
        if(add_book_button){
            connect(add_book_button, &QPushButton::clicked, this, &MainWindow::open_book_search_window);
        }



    }
};



int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();
}