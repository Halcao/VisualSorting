//
//  painterpalette.cpp
//  VisualSorting
//
//  Created by Halcao on 2017/10/30.
//
//

#include "painterpalette.h"
#include <math.h>

void PainterPalette::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    
    // draw rect
    QPainter painter(this);
    // 反走样
    painter.setRenderHint(QPainter::Antialiasing, true);
    // 设置画笔颜色、宽
    painter.setPen(QPen(QColor(0, 160, 230), 2));
    // 设置画刷颜色
    painter.setBrush(QColor(255, 160, 90));
    
    
    int dataCount = dataSource.size();
    int baseWeight = this->width()/(dataCount*1.1);
    
    int maxHeight = 0;
    for (auto height: dataSource) {
        maxHeight = height > maxHeight ? height: maxHeight;
    }
    
    int heightRatio = height()/maxHeight;
    
    for (int i = 0; i < dataCount; i++) {
        painter.drawRect(i*this->width()/dataCount, this->height()-dataSource[i]*heightRatio, baseWeight, dataSource[i]*heightRatio);
    }
//    drawCircle();
}

void PainterPalette::drawCircle() {
    
    
    // draw rect
    QPainter painter(this);
    // 反走样
    painter.setRenderHint(QPainter::Antialiasing, true);
//    // 设置画笔颜色、宽
//    painter.setPen(QPen(QColor(0, 160, 230), 2));
//    // 设置画刷颜色
//    painter.setBrush(QColor(255, 160, 90));
    
    QGraphicsItem *ball = new QGraphicsEllipseItem(0, 0, 20, 20);
    
    QTimeLine *timer = new QTimeLine(5000);
    timer->setFrameRange(0, 100);
    
    
    QPainterPath *linePath = new QPainterPath;
    QGraphicsPathItem *line = new QGraphicsPathItem;
    QGraphicsEllipseItem *ellipse = new QGraphicsEllipseItem;
    QGraphicsPolygonItem *polygon = new QGraphicsPolygonItem;
    
    QPolygonF *poly = new QPolygonF;
    ellipse->setRect(0, 0, 200, 200);
    line->setPath(*linePath);
    QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
    QGraphicsItemAnimation *animation2 = new QGraphicsItemAnimation;
    //    QGraphicsItem *line = new QGraphicsLineItem
    animation->setItem(ball);
    animation->setTimeLine(timer);
    animation2->setItem(polygon);
    animation2->setTimeLine(timer);

    ellipse->setStartAngle(210*16);
    ellipse->setSpanAngle(120*16);
    
    
    for (int i = 0; i < 60; i++) {
        //        (x-60)*(x-60) + (y+30)*(y+30) = 60*60;
//        animation->setPosAt(i / 120.0, QPointF(2*i, sqrt(60*60-(2*i-60)*(2*i-60))-30+100));
        //        (x-60)*(x-60) + (y+30)*(y+30) = 60*60;
        animation->setPosAt(i / 120.0, QPointF(2*i, sqrt(60*60-(2*i-60)*(2*i-60))-30+100));
        poly->append(QPointF(2*i, sqrt(60*60-(2*i-60)*(2*i-60))-30+100));
//        animation2->setPosAt(i / 120.0, QPointF(2*i, sqrt(60*60-(2*i-60)*(2*i-60))-30+100));
//        linePath->lineTo(2*i, sqrt(60*60-(2*i-60)*(2*i-60))-30+100);
//        animation2->setPosAt(i / 120.0, QPointF(2*i, sqrt(60*60-(2*i-60)*(2*i-60))-30+100));
//        path->lineTo(2*i, sqrt(60*60-(2*i-60)*(2*i-60))-30+100);
    }
    polygon->setPolygon(*poly);

    
    QGraphicsScene *scene = new QGraphicsScene();
//    scene->setSceneRect(0, 0, height(), width());
    scene->setSceneRect(0, 0, 300, 300);
    scene->addItem(ball);
    scene->addItem(polygon);
    
    QGraphicsView *view = new QGraphicsView;
    
    view->setScene(scene);
    view->show();
    timer->start();
    
    startTimer(1000);
}

void PainterPalette::timerEvent(QTimerEvent *event)
{
    printf("foo");
//    (QTimerEvent *)event->timerId();
//    qDebug( "timer event, id %d", event->);
}

