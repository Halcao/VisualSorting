#ifndef SorterFactory_h
#define SorterFactory_h

#include <iostream>
#include <bubblesorter.h>

class SorterFactory {
private:
    SorterFactory();
    // copy a factory
    SorterFactory(const SorterFactory &) {}
    SorterFactory &operator=(const SorterFactory&) { return *this; }
public:
    // dealloc
    ~SorterFactory();
    // generate a sorter instance pointer
    static Sorter *getSorter(const std::string &name);
};
#endif /* SorterFactory_h */
