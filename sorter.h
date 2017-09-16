#ifndef Sorter_h
#define Sorter_h

#include <string>
#include <vector>
#include <functional>

using namespace std;

// enumeration of sorting state
typedef enum {
    SortingStateSorting,
    SortingStateNotSorting
} SortingState;

// TODO: Comment here
typedef enum {
    BubbleSorterType = 0,
    QuickSorterType = 1,
    HeapSorterType = 2,
} SorterType;

// class of sorter
class Sorter {
public:
    string name;
    SorterType type;
    // array to sort
    vector<int> array;
    // size of the array
    unsigned long size() const { return array.size(); }
    // the state of sorting
    SortingState state;
    
    bool isAscending = true;

    // operations on starting sorting
//    virtual void onStartSorting();
    function<void()> onStartSorting;
    // method of sorting
    virtual void sort() {};
    // operations on stoping sorting
//    virtual void onStopSorting();
    function<void()> onStopSorting;

    // callback to update UI
//    virtual void render(int, int);
    function<void(int, int)> render;
};

#endif /* Sorter_h */

