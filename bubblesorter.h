#ifndef BUBBLESORTER_H
#define BUBBLESORTER_H

#include <sorter.h>

class BubbleSorter: public Sorter {
    Q_OBJECT
public:
    BubbleSorter() {
        name = "BubbleSort";
        type = BubbleSorterType;
    };
//    string name = "BubbleSort";
    virtual void sort();
    
//signals:
//    void render1(int, int);
};

#endif // BUBBLESORTER_H
