//
// Created by Conrad Mercer on 4/29/2025.
//

#include <QApplication>
#include <QPushButton>
#include <QPainter>
#include <QPaintEvent>
#include <QMainWindow>
#include <QWidget>

class Test : public QWidget{
public:
    Test(QWidget *parent = nullptr) : QWidget(parent){}

    void paintEvent(QPaintEvent *event) override;
};


void Test::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QString title = "Viva Cristo Rey";

    QFont font;
    font.setPointSize(12);
    painter.setFont(font);
    painter.setPen(Qt::red);

    const QRect rect = QRect(0,0,1000,100);
    QRect test_rect = painter.boundingRect(rect, Qt::TextWordWrap, title);

    int x = 50;
    int y = 50;

    painter.drawText(x,y,test_rect.width(), test_rect.height(), Qt::AlignLeft | Qt::AlignTop, title);

}


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QMainWindow window;
    int window_x = 800;
    int window_y = 600;
    window.setWindowTitle("Info");
    window.resize(window_x, window_y);

    Test *tester = new Test(&window);

    window.setCentralWidget(tester);

    window.show();
    return QApplication::exec();
}

