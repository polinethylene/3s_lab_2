#ifndef LAB_2_DYNARRAY_H
#define LAB_2_DYNARRAY_H

#include <iostream>

template <class T>
class DynamicArray {
private:
    int length;
    T *data;
public:
    T &operator[](int index) {
        if (index >= length || index < 0) {
            throw std::runtime_error("Index out of range");
        }
        return *(data + index);
    }

    DynamicArray<T> &operator=(const DynamicArray<T> &array){
        if (this == &array) {
            return *this;
        }
        if (this->data!=NULL) {
            delete[] this->data;
            this->data = nullptr;
        }
        if (array.data == NULL){
            throw std::runtime_error("NULL list");
        }
        if (array.length > 0) {
            data = new T[array.length]();
            for (int i = 0; i < array.length; i++) {
                data[i] = array.data[i];
            }
        } else {
            data = new T[1]();
        }
        length = array.length;
        return *this;
    }

    DynamicArray(){
        length = 0;
        data = new T[1]();
    }

    DynamicArray(std::vector<T> items, int count){
        if (count < 0){
            throw std::runtime_error("count < 0");
        }
        data = new T[count]();
        if (items.size() == 0){
            throw std::runtime_error("NULL list");
        }
        for (int i = 0; i < count; i++){
            data[i] = items[i];
        }
        length = count;
    }

    DynamicArray(T* items, int count){
        if (count < 0){
            throw std::runtime_error("count < 0");
        }
        data = new T[count]();
        if (items == NULL){
            throw std::runtime_error("NULL list");
        }
        for (int i = 0; i < count; i++){
            data[i] = items[i];
        }
        length = count;
    }

    explicit DynamicArray(int size) {
        if (size < 0){
            throw std::runtime_error("count < 0");
        }
        data = new T[size]();
        length = size;
    }

    DynamicArray(const DynamicArray<T> & dynamicArray) : DynamicArray() {
        *this = dynamicArray;
    }

    ~DynamicArray() {
        delete[] data;
    }

    T &Get(int index) {
        if (index >= length || index < 0) {
            throw std::runtime_error("Index out of range");
        }
        return *(data + index);
    }

    int GetSize() {
        return length;
    }
    void Resize(int newSize){
        if (newSize < 0) {
            throw std::runtime_error("Size < 0");
        }
        data = static_cast<T *>(realloc(data, sizeof(T) * newSize));
        length = newSize;
    }

    void Set(int index, T value){
        if (index>=length){
            Resize(index+1);
        }
        if (index<0){
            throw std::runtime_error("Index out of range");
        }
        data[index] = value;
    }

};

#endif //LAB_2_DYNARRAY_H
