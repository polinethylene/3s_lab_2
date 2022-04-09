#ifndef LAB_2_SEQUENCE_H
#define LAB_2_SEQUENCE_H

#include <iostream>
//#include "ISorter.h"

template <class T> class Sequence{
public:
    Sequence(){};
    virtual T &GetFirst()=0;
    virtual T &GetLast()=0;
    virtual T &Get(int index)=0;
    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex)=0;
    virtual int GetLength()=0;
    virtual void Set(int index, T value)=0;
    virtual void Append(T item)=0;
    virtual void Prepend(T item)=0;
    virtual void InsertAt(T item, int index)=0;
    virtual Sequence <T>* Concat(Sequence <T> *list)=0;
//    virtual Sequence<T>* Sort(ISorter<T> &&f)=0;              // for pybind use ISorter<T> &f
    virtual ~Sequence(){};
};

#endif //LAB_2_SEQUENCE_H
