#ifndef mainwindow_h
#define mainwindow_h

#include <QMainWindow>
#include <QBoxLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QSlider>
#include "sorterfactory.h"
#include "painterpalette.h"

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
    QSlider *speedSlider;
    QButtonGroup *sizeGroup;
    QPushButton *restartButton;
    PainterPalette *painterPalette;
    
private:
    // generate random dataset
    void shuffle(vector<int> &);
    // swap two frame in layout
//    void swap(int i, int j);
    QHBoxLayout *bottomLayout;
signals:
    void sorterTypeWillChange(SorterType);
    void sizeWillChange(int);
    void restartTapped();
public slots:
    void setSpeed(int);
    void setSorterType(int);
    void setSize(int);
    void swapFrame(int, int);
    void restart();
};

#endif /* mainwindow_h */
