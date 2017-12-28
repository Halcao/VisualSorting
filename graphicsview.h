//
//  graphicsview.h
//  VisualSorting
//
//  Created by Halcao on 2017/12/17.
//
//

#ifndef graphicsview_h
#define graphicsview_h

#include <QGraphicsView>
#include <QTimeLine>
#include <QGraphicsItem>

class GraphicsView: public QGraphicsView {
    Q_OBJECT
    QTimeLine *timeline;
    int animaCount = 0;
public:
    GraphicsView();
    QGraphicsEllipseItem *ball;
    public slots:
    void frameChanged(int);
};

#endif /* graphicsview_h */
