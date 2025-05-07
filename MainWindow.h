//
// Created by Conrad Mercer on 5/6/2025.
//
#ifndef BOOKSTHROUGHTHEAGES_MAINWINDOW_H
#define BOOKSTHROUGHTHEAGES_MAINWINDOW_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QBoxLayout>

class Scene : public QWidget{
private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    QHBoxLayout *main_layout;

public:
    explicit Scene(QWidget *parent = nullptr, int window_x = 0, int window_y = 0);

    ~Scene() override;

    void init_scene();

    const QGraphicsScene* get_scene(){
        return scene;
    }

    const QGraphicsView* get_view(){
        return view;
    }

    void update_scene_rect();

};

#endif //BOOKSTHROUGHTHEAGES_MAINWINDOW_H
