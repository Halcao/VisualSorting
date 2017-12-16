//
//  painterpalette.hpp
//  VisualSorting
//
//  Created by Halcao on 2017/10/30.
//
//

#ifndef painterpalette_h
#define painterpalette_h

#include <QFrame>
#include <vector>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
//#include <qwt_plot.h>

class PainterPalette: public QWidget {
    Q_OBJECT
    
    // end with -1
public:
    std::vector<int> dataSource;
    void paintEvent(QPaintEvent *event);
    void drawCircle();
    void timerEvent(QTimerEvent *event);
};

#endif /* painterpalette_h */
