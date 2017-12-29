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


void gradientArc(QPainter *painter, int radius, double startAngle, double angleLength, int arcHeight, QColor color)
{
    // 渐变色
    QRadialGradient gradient(0, 0, radius);
    gradient.setColorAt(0, QColor(0x21BACF));
    gradient.setColorAt(1.0, color);
    painter->setBrush(gradient);
    
    // << 1（左移1位）相当于radius*2 即：150*2=300
    //QRectF(-150, -150, 300, 300)
    QRectF rect(-radius, -radius, radius << 1, radius << 1);
    QPainterPath path;
    path.arcTo(rect, startAngle, angleLength);
    
    painter->setPen(Qt::NoPen);
    painter->drawPath(path);
}

unsigned int rgb(double hue)
{
    int h = int(hue * 256 * 6);
    int x = h % 0x100;
    
    int r = 0, g = 0, b = 0;
    switch (h / 256)
    {
        case 0: r = 255; g = x;       break;
        case 1: g = 255; r = 255 - x; break;
        case 2: g = 255; b = x;       break;
        case 3: b = 255; g = 255 - x; break;
        case 4: b = 255; r = x;       break;
        case 5: r = 255; b = 255 - x; break;
    }
    
    return r + (g << 8) + (b << 16);
}


void PainterPalette::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    
    // draw rect
    QPainter painter(this);
    // 反走样
    painter.setRenderHint(QPainter::Antialiasing, true);
    // 设置画笔颜色、宽
//    painter.setPen(QPen(QColor(0, 160, 230), 0.5));
//    // 设置画刷颜色
//    painter.setBrush(QColor(255, 160, 90));
    
    
    int dataCount = dataSource.size();
//    int baseWeight = this->width()/(dataCount*1.1);
//    
//    int maxHeight = 0;
//    for (auto height: dataSource) {
//        maxHeight = height > maxHeight ? height: maxHeight;
//    }
//    
//    int heightRatio = height()/maxHeight;
//    
//    for (int i = 0; i < dataCount; i++) {
//        if (i == from || i == to) {
//            painter.setBrush(QColor(0, 160, 230));
//        } else {
//            painter.setBrush(QColor(255, 160, 90));
//        }
//        painter.drawRect(i*this->width()/dataCount, this->height()-dataSource[i]*heightRatio, baseWeight, dataSource[i]*heightRatio);
//    }
    
    int radius = 250;
    int arcHeight = 30;
    
    // >> 1（右移1位）相当于width() / 2
    painter.translate(this->width() >> 1, height() >> 1);
    
    /**
     * 参数二：半径
     * 参数三：开始的角度
     * 参数四：指扫取的角度-顺时针（360度 / 8 = 45度）
     * 参数五：圆环的高度
     * 参数六：填充色
     **/

    double interval = 360.0/dataCount;
    for(int i = 0; i < dataCount; i++) {
        gradientArc(&painter, radius, i*interval, interval, arcHeight, QColor(rgb((double)dataSource[i]/(double)dataCount)));
    }
}

