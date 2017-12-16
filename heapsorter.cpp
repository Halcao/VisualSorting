#include "heapsorter.h"
#include <iostream>

void HeapSorter::AdjustDown(int i, int len)
{
    int temp = array[i];  // 暂存array[i]
    
    for(int largest=2*i+1; largest<len; largest=2*largest+1)
    {
        if(largest!=len-1 && array[largest+1]>array[largest])
            ++largest;         // 如果右子结点大
        if(temp < array[largest])
        {
            if (state == SortingStateNotSorting) {
                return;
            }
            array[i] = array[largest];
            emit render1(i, largest);
            i = largest;         // 记录交换后的位置
        }
        else
            break;
    }
    array[i] = temp;    // 被筛选结点的值放入最终位置
}
void HeapSorter::BuildMaxHeap(int len)
{
    for(int i=len/2-1; i>=0; --i)  // 从i=[n/2]~1，反复调整堆
        AdjustDown(i, len);
}

void HeapSorter::sort() {
    int n = (int)array.size();
    BuildMaxHeap(n);       // 初始建堆
    for(int i=n-1; i>0; --i)  // n-1趟的交换和建堆过程
    {
        if (state == SortingStateNotSorting) {
            return;
        }
        // 输出最大的堆顶元素（和堆底元素交换）
        array[0] = array[0]^array[i];
        array[i] = array[0]^array[i];
        array[0] = array[0]^array[i];
        emit render1(i, 0);
        // 调整，把剩余的n-1个元素整理成堆
        AdjustDown(0, i);
    }
}

