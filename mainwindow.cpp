#include "mainwindow.h"
#include <algorithm>
#include <QSignalMapper>
#include <QFrame>

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
        mapper->setMapping(button, sorter->type);
        QObject::connect(mapper, SIGNAL(mapped(int)), this, SLOT(setSorterType(int)));
        
        // add to the group, add to layout
        sorterGroup->addButton(button);
        topLayout->addWidget(button);
//        topLayout->setStretchFactor(button, 1);
    }
    speedSlider->setOrientation(Qt::Horizontal);
    topLayout->addWidget(speedSlider);
//    topLayout->setStretchFactor(speedSlider, 5);

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
    
    // set central widget
    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

void MainWindow::setSorterType(int type) {
    printf("%d", type);
    switch (type) {
        case BubbleSorterType:
            sorter = SorterFactory::getSorter("BubbleSort");
            break;
        case QuickSorterType:
            sorter = SorterFactory::getSorter("QuickSort");
            break;
        case HeapSorterType:
            sorter = SorterFactory::getSorter("HeapSort");
            break;
        default:
            break;
    }
}

void MainWindow::setSpeed(int speed) {
    this->speed = speed;
}

void MainWindow::setSize(int size) {
//    std::cout << size << std::endl;
//    sorter->array.clear();
    int currentSize = sorter->array.size();
    if (currentSize < size) {
        for (int i = 0; i < size - currentSize; i++) {
            QFrame *frame = new QFrame;
            frame->setMinimumWidth(3);
            frame->setFixedWidth(5);
//            frame->setStyleSheet("background-color: #6cf;");
            frame->setStyleSheet("background-color: white;");
            bottomLayout->addWidget(frame, 0, Qt::AlignBottom);
        }
    } else if (currentSize > size) {
        printf("%d", currentSize - size);
        for (int i = 0; i < currentSize - size; i++) {
            QLayoutItem *item = bottomLayout->takeAt(0);
            QWidget *widget = item->widget();
            bottomLayout->removeWidget(widget);
            widget->deleteLater();
        }
    }
    
    sorter->array.clear();
    for (int i = 0; i < size; i++) {
        sorter->array.push_back(i);
    }
//    shuffle(sorter->array);
    
    bottomLayout->update();
    float baseHeight = (bottomLayout->parentWidget()->height() * 0.8)/size;
//    float baseHeight = (800 * 0.8)/size;
//    for (int i = 0; i < size; i++) {
//        QWidget *widget = bottomLayout->itemAt(i)->widget();
////        widget->setFixedWidth(sorter->array[i]*baseHeight);
//        widget->setFixedWidth(sorter->array[i]*10);
//        printf("%d, ", sorter->array[i]);
//    }
    
    for (int i = 0; i < size; i++) {
        int randIndex = random()%(sorter->array.size()-i) + i;
        int tmp = sorter->array[i];
        sorter->array[i] = sorter->array[randIndex];
        sorter->array[randIndex] = tmp;
        QLayoutItem *item = bottomLayout->itemAt(i);
        QWidget *widget = item->widget();
        widget->setFixedHeight(sorter->array[i]*baseHeight);
    }

}

void MainWindow::restart() {
    sorter->onStopSorting();
    shuffle(sorter->array);
    sorter->onStartSorting();
}

void MainWindow::shuffle(vector<int> &array) {
    random_shuffle(array.begin(), array.end());
}

