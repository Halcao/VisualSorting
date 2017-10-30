//
//  painterpalette.hpp
//  VisualSorting
//
//  Created by Halcao on 2017/10/30.
//
//

#ifndef painterpalette_h
#define painterpalette_h

#endif /* painterpalette_h */

#include <QFrame>
#include <vector>
#include <QPainter>

class PainterPalette: public QWidget {
    Q_OBJECT
    
    // end with -1
public:
    std::vector<int> dataSource;
    void paintEvent(QPaintEvent *event);
};
