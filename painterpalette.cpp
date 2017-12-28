//
//  painterpalette.cpp
//  VisualSorting
//
//  Created by Halcao on 2017/10/30.
//
//

#include "painterpalette.h"
#include <math.h>
#include <QtGui>

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
    QGraphicsItem *ball = new QGraphicsEllipseItem(0, 0, 20, 20);
    
    QTimeLine *timer = new QTimeLine(5000);
    timer->setFrameRange(0, 100);
    
    QPainterPath *linePath = new QPainterPath;
    QGraphicsPathItem *line = new QGraphicsPathItem;
    QGraphicsEllipseItem *ellipse = new QGraphicsEllipseItem;
    QGraphicsPolygonItem *polygon = new QGraphicsPolygonItem;
    
    QGraphicsScene *scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 300, 300);
    scene->addItem(ball);
//    scene->addItem(polygon);
    
    QGraphicsView *view = new QGraphicsView;
    
    view->setScene(scene);
    view->show();
    timer->start();
    
    startTimer(1000);
    QTimeLine *timeLine = new QTimeLine(1000);
    timeLine->start();
}

void PainterPalette::timerEvent(QTimerEvent *event)
{
    printf("foo");
//    (QTimerEvent *)event->timerId();
//    qDebug( "timer event, id %d", event->);
}

