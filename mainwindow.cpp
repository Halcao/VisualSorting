#include "mainwindow.h"
#include <algorithm>
#include <QSignalMapper>
#include <QFrame>
#include <QTime>
#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
sorterGroup(new QButtonGroup()),
speedSlider(new QSlider()),
sizeGroup(new QButtonGroup()),
restartButton(new QPushButton()),
bottomLayout(new QHBoxLayout) {
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
        QPushButton *button = new QPushButton;
        button->setChecked(true);
        button->setAutoExclusive(true);
        // TODO: fix style sheet
        button->setStyleSheet("background-color: white;");
//        button->setText(tr(sorter->name.c_str()));
        button->setText(QString(sorter->name.c_str()));
        // create the mapper, connect signal to slot
        QSignalMapper *mapper = new QSignalMapper;
        QObject::connect(button, SIGNAL(clicked()), mapper, SLOT(map()));
        printf("%s->%d\n", sorter->name.c_str(), sorter->type);
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
    topLayout->addWidget(speedSlider);
    
    vector<int> sizeVec = {5, 10, 20, 50, 100, 150};
    for (auto size: sizeVec) {
        // init the button, set the style
        QPushButton *button = new QPushButton;
        button->setChecked(true);
        button->setAutoExclusive(true);
        // TODO: fix style sheet
        button->setStyleSheet("background-color: white;");
        // Arabic numbers so don't worry the internationalization
        button->setText(QString::number(size));
        // create the mapper, connect signal to slot
        QSignalMapper *mapper = new QSignalMapper;
        QObject::connect(button, SIGNAL(clicked()), mapper, SLOT(map()));
        mapper->setMapping(button, size);
        QObject::connect(mapper, SIGNAL(mapped(int)), this, SLOT(setSize(int)));
        
        // add to the group, add to layout
        sizeGroup->addButton(button);
        topLayout->addWidget(button);
//        topLayout->setStretchFactor(button, 0.5);
    }
    
    // FIXME: read size from config
//    setSize(size);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(bottomLayout);
    
//    QFrame *painterPanel = new QFrame;
//    bottomLayout->addWidget(painterPanel);
    painterPalette = new PainterPalette;
//    painterPalette->setFixedSize(600, 1500);
    
    painterPalette->dataSource = {14, 23, 34, 41, 15, 63, 7, 82, 39, 10};
    bottomLayout->addWidget(painterPalette);

//    painterPalette->setMaximumSize(400, 400);
//    painterPalette->setMinimumSize(100, 100);
    // set central widget
    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

void MainWindow::setSorterType(int type) {
    printf("%d", type);
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

void MainWindow::setSize(int size) {
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
//    cout << speed/100.0 << endl;
    while(t.elapsed()<speed/100.0)
        QCoreApplication::processEvents();
    int temp = painterPalette->dataSource[i];
    
    if (sorter->state == SortingStateNotSorting) {
        return;
    }
    painterPalette->dataSource[i] = painterPalette->dataSource[j];
    painterPalette->dataSource[j] = temp;
    painterPalette->update();
}
