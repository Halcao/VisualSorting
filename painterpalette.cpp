//
//  painterpalette.cpp
//  VisualSorting
//
//  Created by Halcao on 2017/10/30.
//
//

#include "painterpalette.h"

void PainterPalette::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);

    // 反走样
    painter.setRenderHint(QPainter::Antialiasing, true);
    // 设置画笔颜色、宽
    painter.setPen(QPen(QColor(0, 160, 230), 2));
    // 设置画刷颜色
    painter.setBrush(QColor(255, 160, 90));
    
    int dataCount = dataSource.size();
    int baseWeight = this->width()/(dataCount*1.1);
    printf("baseWeight: %d\n", baseWeight);
    
    int maxHeight = 0;
    for (auto height: dataSource) {
        maxHeight = height > maxHeight ? height: maxHeight;
    }
    
    int heightRatio = height()/(maxHeight*0.8);
//    painter.drawRect(height(), width(), 0, 0);
    
    for (int i = 0; i < dataCount; i++) {
        painter.drawRect(i*this->width()/dataCount, this->height()-dataSource[i]*heightRatio, baseWeight, dataSource[i]*heightRatio);
//        printf("height: %d, x: %d, y: %d\n", dataSource[i], i*this->width()/dataCount, this->height()-dataSource[i]);
    }
//    painter.drawRect(50, 50, 160, 100);
}
