//
// Created by Conrad Mercer on 4/29/2025.
//

#include <QApplication>
#include <QMainWindow>
#include "BookInfo.h"

class MainWindow : public QMainWindow {
public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("Books Through The Ages");
        resize(800, 600);

        // Create the Text widget
        Text *bookInfoWidget = new Text(this, width(), height());

        // Set as central widget
        setCentralWidget(bookInfoWidget);

        // Fetch book info
        bookInfoWidget->fetch_book_info("OL9639573M"); // Speaker for the Dead
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();
}
