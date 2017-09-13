//
//  Sorter.h
//  VisualSorting
//
//  Created by Halcao on 2017/9/11.
//
//

#ifndef Sorter_h
#define Sorter_h

#include <stdio.h>
#include <string>
#include <vector>
#include <functional>

using namespace std;

// enumeration of sorting state
typedef enum {
    Sorting,
    NotSorting
} SortingState;

// class of sorter
class Sorter {
public:
    string name;
    // array to sort
    vector<int> array;
    // the state of sorting
    SortingState state;
    
    // operations on starting sorting
    virtual void onStartSorting();
    // method of sorting
    virtual void sort();
    // operations on stoping sorting
    virtual void onStopSorting();
    
    // callback to update UI
//    virtual void render(int, int);
    function<void(int, int)> render;
    // generate random dataset
    void shuffle();
};

#endif /* Sorter_h */

