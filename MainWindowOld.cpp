//
// Created by Conrad Mercer on 5/6/2025.
//

#include "MainWindowOld.h"

//serach_window = newSearchWindow

Scene::Scene(QWidget *parent, int window_x, int window_y) {
    init_scene();
}

Scene::~Scene() {
    //qt will delete scene and view automatically due to parent-child
    //relationships, but we clear the pointers to be safe
    scene = nullptr;
    view = nullptr;
}

void Scene::init_scene() {
    //clean up any existing layout
    if(layout()){
        delete layout();
    }

    main_layout = new QHBoxLayout(this);
    //remove margins
    main_layout->setContentsMargins(0,0,0,0);

    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    view->setRenderHint(QPainter::Antialiasing);
    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    //remove from frame
    view->setFrameStyle(QFrame::NoFrame);

    main_layout->addWidget(view);
    setLayout(main_layout);
}

void Scene::update_scene_rect() {
    if(scene){
        scene->setSceneRect(scene->itemsBoundingRect());
    }
}
