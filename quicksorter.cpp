#include "quicksorter.h"
#include <iostream>

void QuickSorter::sort() {
    quickSort(0, (int)array.size()-1);
}

int QuickSorter::partition(int low, int high)
{
    int pivot = array[low];
    while(low < high)
    {
        while(low<high && array[high]>=pivot)
            --high;
        array[low] = array[high];
        emit render1(low, high);
        while(low<high && array[low]<=pivot)
            ++low;
        array[high] = array[low];
        emit render1(low, high);
    }
    
    array[low] = pivot;
    return low;
}

void QuickSorter::quickSort(int low, int high) {
    if(low < high)  // 递归跳出的条件
    {
        int pivotPos = partition(low, high); // 划分操作，返回基准元素的最终位置
        quickSort(low, pivotPos-1);  // 递归
        quickSort(pivotPos+1, high);
    }
}
