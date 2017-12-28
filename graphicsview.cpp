//
//  graphicsview.cpp
//  VisualSorting
//
//  Created by Halcao on 2017/12/16.
//
//
#include "graphicsview.h"
#include <QtMath>
#include <QGraphicsItemAnimation>
#include <functional>

GraphicsView::GraphicsView() {
    QGraphicsScene *scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 500, 500);
    this->setScene(scene);
    
    ball = new QGraphicsEllipseItem(0, 150, 20, 20);

    scene->addItem(ball);
    
    QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
    animation->setItem(ball);
    QTimeLine *timer = new QTimeLine(1000);
    animation->setTimeLine(timer);
    
    for(int i = 0; i < 600; ++i) {
        double angle = M_PI * (600-i) / 600.0;
        qreal x = 150 + 150*qCos(angle);
        qreal y = 150 - 50*qSin(angle);
        
        animation->setPosAt(sqrt(i)/sqrt(600.0), QPointF(x, y));
    }
    timer->start();
    timeline = new QTimeLine(1000);
    timeline->setFrameRange(0, 1000);
    timeline->setUpdateInterval(1);
    timeline->setCurveShape(QTimeLine::LinearCurve);
    connect(timeline, SIGNAL(frameChanged(int)), this, SLOT(frameChanged(int)));
//    timeline->start();
}

void GraphicsView::frameChanged(int order) {
    int t = 1000 - animaCount;
    animaCount = animaCount + 1;
    printf("%d\n", t);
    int angle = M_PI * t / 1000.0;
    qreal x = 150 + 150*qCos(angle);
    qreal y = 150 - 50*qSin(angle);
    ball->setPos(x, y);
    this->update();
}

QGraphicsItemAnimation animationGenerator(QGraphicsEllipseItem *ball, int i, int j) {
    QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
    QTimeLine *timer = new QTimeLine(1000);
    animation->setItem(ball);
    animation->setTimeLine(timer);
    
    for(int i = 0; i < 600; ++i) {
        double angle = M_PI * (600-i) / 600.0;
        qreal x = 150 + 150*qCos(angle);
        qreal y = 150 - 50*qSin(angle);
        
        animation->setPosAt(sqrt(i)/sqrt(600.0), QPointF(x, y));
    }
    return animation;
}
