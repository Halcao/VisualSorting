#ifndef mainwindow_h
#define mainwindow_h

#include <QMainWindow>
#include <QBoxLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QSlider>
#include "sorterfactory.h"
#include "painterpalette.h"
#include <qtmaterialradiobutton.h>
#include <qtmaterialflatbutton.h>
#include <qtmaterialraisedbutton.h>
#include <QDesktopWidget>


enum ResizeRegion
{
    Default,
    North,
    NorthEast,
    East,
    SouthEast,
    South,
    SouthWest,
    West,
    NorthWest
};


class MainWindow: public QMainWindow {
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow() {};
    
    Sorter *sorter;
    // TODO: set a config file
    // default speed
    int speed = 5;
    // default size
    int size = 50;
    
    vector<Sorter *> sorters;
    QButtonGroup *sorterGroup;
//    QSlider *speedSlider;
    QAbstractSlider *speedSlider;
    QButtonGroup *sizeGroup;
    QPushButton *restartButton;
    PainterPalette *painterPalette;
    
protected:
//    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
//    void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
//    void mouseMoveEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
//    void handleResize();
//    void setResizeCursor();
//    ResizeRegion getResizeRegion(QPoint clientPos);
//    void handleMove(QPoint pt);
//    void setResizeCursor(ResizeRegion region);
    
private:
    // generate random dataset
    void shuffle(vector<int> &);
    vector<QtMaterialRaisedButton *> sizeButtons;
    // swap two frame in layout
//    void swap(int i, int j);
    QHBoxLayout *bottomLayout;
    
    bool m_drag, m_move;
    QPoint dragPos, resizeDownPos;
    const int resizeBorderWidth = 5;
    ResizeRegion resizeRegion;
    QRect mouseDownRect;
    QDesktopWidget *desktop;
    
signals:
    void sorterTypeWillChange(SorterType);
    void sizeWillChange(int);
    void restartTapped();
public slots:
    void setSpeed(int);
    void setSorterType(int);
//    void setSize(int);
    void setSize(int);
    void swapFrame(int, int);
    void restart();
};

#endif /* mainwindow_h */
