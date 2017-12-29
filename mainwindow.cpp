#include "mainwindow.h"
#include <algorithm>
#include <QSignalMapper>
#include <QFrame>
#include <QTime>
#include <QCoreApplication>
#include "graphicsview.h"
#include <qtmaterialslider.h>
#include <QStatusBar>
#include <QMouseEvent>
#include <QStatusBar>
#include "frameless_helper.h"

MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
sorterGroup(new QButtonGroup()),
//speedSlider(new QSlider()),
speedSlider(new QtMaterialSlider),
sizeGroup(new QButtonGroup()),
restartButton(new QPushButton()),
bottomLayout(new QHBoxLayout),
desktop(new QDesktopWidget) {
    // set style of main window
    this->setWindowTitle("Visual Sort");
    this->setStyleSheet("background-color: #333;");
    
    // initialize sorters
    sorters = {SorterFactory::getSorter("BubbleSort"), SorterFactory::getSorter("QuickSort"), SorterFactory::getSorter("HeapSort")};
    sorter = sorters[0];
    QHBoxLayout *topLayout = new QHBoxLayout;
    
    // prepare for various kind of buttons
    for (auto sorter: sorters) {
        sorter->array.clear();
        // init the button, set the style
        QtMaterialRadioButton *button = new QtMaterialRadioButton;
        
        if (sorter->name == "BubbleSort")
            button->toggle();

//        button->setChecked(true);
        button->setAutoExclusive(true);
        button->setTextColor(Qt::white);
        // TODO: fix style sheet
        button->setStyleSheet("background-color: white;");
        button->setText(QString(sorter->name.c_str()));
        // create the mapper, connect signal to slot
        QSignalMapper *mapper = new QSignalMapper;
        QObject::connect(button, SIGNAL(toggled(bool)), mapper, SLOT(map()));
        mapper->setMapping(button, sorter->type);
        QObject::connect(mapper, SIGNAL(mapped(int)), this, SLOT(setSorterType(int)));
        QObject::connect(sorter, SIGNAL(render1(int, int)), this, SLOT(swapFrame(int, int)));
        // add to the group, add to layout
        sorterGroup->addButton(button);
        topLayout->addWidget(button);
    }
    speedSlider->setRange(1, 100);
    QObject::connect(speedSlider, SIGNAL(valueChanged(int)), this, SLOT(setSpeed(int)));
    speedSlider->setOrientation(Qt::Horizontal);
    speedSlider->setMinimumWidth(100);
    topLayout->addWidget(speedSlider);
    
    vector<int> sizeVec = {5, 10, 20, 50, 100, 150};
//    QWidget *buttonWidget = new QWidget;
    for (int i = 0; i < (int)sizeVec.size(); i++) {
        int size = sizeVec[i];
        // init the button, set the style
        QtMaterialRaisedButton *button = new QtMaterialRaisedButton;
        button->setAutoExclusive(true);
        
        // Arabic numbers so don't worry the internationalization
        button->setText(QString::number(size));
        button->setCheckable(true);
        button->setBackgroundColor(QColor(0x1FBCD2));
        button->setFontSize(13);
//        button->setForegroundColor(QColor(0xbcaaa4));
        button->setOverlayColor(QColor(0x1FBCD2));
        button->setFixedWidth(34);
        button->setFixedHeight(25);
        button->setCornerRadius(3);
        // create the mapper, connect signal to slot
        
        QSignalMapper *mapper = new QSignalMapper;
        QObject::connect(button, SIGNAL(clicked(bool)), mapper, SLOT(map()));
        mapper->setMapping(button, i);
        QObject::connect(mapper, SIGNAL(mapped(int)), this, SLOT(setSize(int)));
        // add to the group, add to layout
        sizeGroup->addButton(button);
        topLayout->addWidget(button);

        sizeButtons.push_back(button);
    }
    
    // FIXME: read size from config
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(bottomLayout);
    
//    QFrame *painterPanel = new QFrame;
//    bottomLayout->addWidget(painterPanel);
    painterPalette = new PainterPalette;
//    painterPalette->resize(300, 300);
//    painterPalette->setFixedSize(600, 1500);
    
    painterPalette->dataSource = {14, 23, 34, 41, 15, 63, 7, 82, 39, 10};
    bottomLayout->addWidget(painterPalette);

//    painterPalette->setMaximumSize(400, 400);
    painterPalette->setMinimumSize(100, 100);
    painterPalette->from = -1;
    painterPalette->to = -1;
    QSizePolicy painterPolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    painterPalette->setSizePolicy(painterPolicy);

    // set central widget
    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
    
    
    this->setWindowTitle("Visual Sorting");
    this->setWindowIcon(QIcon(":/resources/icon.png"));
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    this->setGeometry(QRect(100, 55, 350, 250));//可设置窗口显示的方位与大小
    
    this->setWindowOpacity(0.98);//设置透明1-全体透明
    this->setAttribute(Qt::WA_TranslucentBackground, true);//设置透明2-窗体标题栏不透明,背景透明
    this->setMinimumSize(sizeHint());
//    this->resize(300,300);//显示大小
    
    this->setMouseTracking(true);
    
    QStatusBar *statusBar = new QStatusBar;
//    statusBar->
    
    FramelessHelper *pHelper = new FramelessHelper(this);
    pHelper->activateOn(this);  //激活当前窗体
    pHelper->setTitleHeight(20);  //设置窗体的标题栏高度
    pHelper->setWidgetMovable(true);  //设置窗体可移动
    pHelper->setWidgetResizable(true);  //设置窗体可缩放
    pHelper->setRubberBandOnMove(true);  //设置橡皮筋效果-可移动
    pHelper->setRubberBandOnResize(true);  //设置橡皮筋效果-可缩放
    
    QSizePolicy policy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
    centralWidget->setSizePolicy(policy);
}

void MainWindow::setSorterType(int type) {
    sorter->state = SortingStateNotSorting;
    switch (type) {
        case BubbleSorterType:
            sorter = sorters[0];
//            sorter = SorterFactory::getSorter("BubbleSort");
            break;
        case QuickSorterType:
            sorter = sorters[1];
//            sorter = SorterFactory::getSorter("QuickSort");
            break;
        case HeapSorterType:
            sorter = sorters[2];
//            sorter = SorterFactory::getSorter("HeapSort");
            break;
        default:
            break;
    }
}

void MainWindow::setSpeed(int speed) {
    this->speed = 100 - speed;
}

void MainWindow::setSize(int index) {
    QtMaterialRaisedButton *button = sizeButtons[index];
    int size = button->text().toInt();
    
    sorter->state = SortingStateNotSorting;
//    string name = sorter->name;
//    this->sorter = SorterFactory::getSorter(name);
//    this->sorter->state = SortingStateNotSorting;
//    cout << sorter->type << endl;
    vector<int> array;
    array.clear();
    for (int i = 1; i <= size; i++) {
        array.push_back(i);
    }
    
    for (int i = 0; i < size; i++) {
        int randIndex = (int)random()%(array.size()-i) + i;
        int tmp = array[i];
        array[i] = array[randIndex];
        array[randIndex] = tmp;
    }
    
    sorter->array.clear();
    painterPalette->dataSource.clear();
    for (auto item: array) {
        sorter->array.push_back(item);
        painterPalette->dataSource.push_back(item);
    }
    sorter->state = SortingStateSorting;
    sorter->sort();
    sorter->state = SortingStateNotSorting;
    
    // reset
    painterPalette->from = -1;
    painterPalette->to = -1;
    painterPalette->update();
}

void MainWindow::restart() {
    sorter->state = SortingStateNotSorting;
    sorter->onStopSorting();
    shuffle(sorter->array);
    sorter->onStartSorting();
}

void MainWindow::shuffle(vector<int> &array) {
    sorter->state = SortingStateNotSorting;
    random_shuffle(array.begin(), array.end());
}

void MainWindow::swapFrame(int i, int j) {
    if (sorter->state == SortingStateNotSorting) {
        return;
    }
    QTime t;
    t.start();
    while(t.elapsed()<speed+0.1)
        QCoreApplication::processEvents();
    int temp = painterPalette->dataSource[i];
    
    if (sorter->state == SortingStateNotSorting) {
        return;
    }
    
    painterPalette->from = i;
    painterPalette->to = j;
    painterPalette->dataSource[i] = painterPalette->dataSource[j];
    painterPalette->dataSource[j] = temp;
    painterPalette->update();
}


//void MainWindow::mousePressEvent(QMouseEvent *event)
//{
//    if (event->button() == Qt::LeftButton) {
//        this->m_drag = true;
//        this->dragPos = event->pos();
//        this->resizeDownPos = event->globalPos();
//        this->mouseDownRect = this->rect();
//    }
//}
//void MainWindow::mouseMoveEvent(QMouseEvent * event)
//{
//    if (resizeRegion != Default)
//    {
//        handleResize();
//        return;
//    }
//    if(m_move) {
//        move(event->globalPos() - dragPos);
//        return;
//    }
//    QPoint clientCursorPos = event->pos();
//    QRect r = this->rect();
//    QRect resizeInnerRect(resizeBorderWidth, resizeBorderWidth, r.width() - 2*resizeBorderWidth, r.height() - 2*resizeBorderWidth);
//    if(r.contains(clientCursorPos) && !resizeInnerRect.contains(clientCursorPos)) { //调整窗体大小
//        ResizeRegion resizeReg = getResizeRegion(clientCursorPos);
//        setResizeCursor(resizeReg);
//        if (m_drag && (event->buttons() & Qt::LeftButton)) {
//            resizeRegion = resizeReg;
//            handleResize();
//        }
//    }
//    else { //移动窗体
//        setCursor(Qt::ArrowCursor);
//        if (m_drag && (event->buttons() & Qt::LeftButton)) {
//            m_move = true;
//            move(event->globalPos() - dragPos);
//        }
//    }
//}
//void MainWindow::mouseReleaseEvent(QMouseEvent *event)
//{
//    m_drag = false;
//    if(m_move) {
//        m_move = false;
//        handleMove(event->globalPos()); //鼠标放开后若超出屏幕区域自动吸附于屏幕顶部/左侧/右侧
//    }
//    resizeRegion = Default;
//    setCursor(Qt::ArrowCursor);
//}
//void MainWindow::setResizeCursor(ResizeRegion region)
//{
//    switch (region)
//    {
//        case North:
//        case South:
//            setCursor(Qt::SizeVerCursor);
//            break;
//        case East:
//        case West:
//            setCursor(Qt::SizeHorCursor);
//            break;
//        case NorthWest:
//        case SouthEast:
//            setCursor(Qt::SizeFDiagCursor);
//            break;
//        default:
//            setCursor(Qt::SizeBDiagCursor);
//            break;
//    }
//}
//ResizeRegion MainWindow::getResizeRegion(QPoint clientPos)
//{
//    if (clientPos.y() <= resizeBorderWidth) {
//        if (clientPos.x() <= resizeBorderWidth)
//            return NorthWest;
//        else if (clientPos.x() >= this->width() - resizeBorderWidth)
//            return NorthEast;
//        else
//            return North;
//    }
//    else if (clientPos.y() >= this->height() - resizeBorderWidth) {
//        if (clientPos.x() <= resizeBorderWidth)
//            return SouthWest;
//        else if (clientPos.x() >= this->width() - resizeBorderWidth)
//            return SouthEast;
//        else
//            return South;
//    }
//    else {
//        if (clientPos.x() <= resizeBorderWidth)
//            return West;
//        else
//            return East;
//    }
//}
//void MainWindow::handleMove(QPoint pt)
//{
//    QPoint currentPos = pt - dragPos;
//    if(currentPos.x()<desktop->x()) { //吸附于屏幕左侧
//        currentPos.setX(desktop->x());
//    }
//    else if (currentPos.x()+this->width()>desktop->width()) { //吸附于屏幕右侧
//        currentPos.setX(desktop->width()-this->width());
//    }
//    if(currentPos.y()<desktop->y()) { //吸附于屏幕顶部
//        currentPos.setY(desktop->y());
//    }
//    move(currentPos);
//}
//void MainWindow::handleResize()
//{
//    int xdiff = QCursor::pos().x() - resizeDownPos.x();
//    int ydiff = QCursor::pos().y() - resizeDownPos.y();
//    switch (resizeRegion)
//    {
//        case East:
//        {
//            resize(mouseDownRect.width()+xdiff, this->height());
//            break;
//        }
//        case West:
//        {
//            resize(mouseDownRect.width()-xdiff, this->height());
//            move(resizeDownPos.x()+xdiff, this->y());
//            break;
//        }
//        case South:
//        {
//            resize(this->width(),mouseDownRect.height()+ydiff);
//            break;
//        }
//        case North:
//        {
//            resize(this->width(),mouseDownRect.height()-ydiff);
//            move(this->x(), resizeDownPos.y()+ydiff);
//            break;
//        }
//        case SouthEast:
//        {
//            resize(mouseDownRect.width() + xdiff, mouseDownRect.height() + ydiff);
//            break;
//        }
//        case NorthEast:
//        {
//            resize(mouseDownRect.width()+xdiff, mouseDownRect.height()-ydiff);
//            move(this->x(), resizeDownPos.y()+ydiff);
//            break;
//        }
//        case NorthWest:
//        {
//            resize(mouseDownRect.width()-xdiff, mouseDownRect.height()-ydiff);
//            move(resizeDownPos.x()+xdiff, resizeDownPos.y()+ydiff);
//            break;
//        }
//        case SouthWest:
//        {
//            resize(mouseDownRect.width()-xdiff, mouseDownRect.height()+ydiff);
//            move(resizeDownPos.x()+xdiff, this->y());
//            break;
//        }
//        case Default:
//            break;
//    }
//}
