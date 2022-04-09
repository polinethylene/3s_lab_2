#ifndef LAB_2_LINKLIST_H
#define LAB_2_LINKLIST_H

#include <iostream>

template <class T>
class LinkedList {
private:
    int length;
    struct Elem{
        T data;
        struct Elem *next;
    };
    Elem* head;
    Elem* tail;
public:
    LinkedList<T> &operator=(const LinkedList<T> &list){
        if (this == &list) {
            return *this;
        }
        if (this->head!=NULL) {
            Elem *ptr = head;
            Elem *ptr_prev;
            while(ptr){
                ptr_prev = ptr;
                ptr = ptr->next;
                delete ptr_prev;
            }
            head = NULL;
            tail = NULL;
        }
        if (list.head == NULL){
            throw std::runtime_error("NULL list");
        }
        if (list.length > 0) {
            head = NULL;
            tail = NULL;
            Elem* ptr = list.head;
            for (int i = 0; i < list.length; i++) {
                Append(ptr->data);
                ptr = ptr->next;
            }
            length = list.length;
        } else {
            head = NULL;
            tail = NULL;
        }
        length = list.length;
        return *this;
    }

    T &Get(int index){
        if (index >= length || index < 0) {
            throw std::runtime_error("Index out of range");
        }
        Elem *ptr = head;
        for(int i=0; i<index; i++){
            ptr = ptr->next;
        }
        return ptr->data;
    }

    LinkedList (){
        length = 0;
        head = NULL;
        tail = NULL;
    }

    void Append(T item){
        Elem *tmp = new Elem;
        tmp->data = item;
        tmp->next = NULL;

        if(head == NULL)
        {
            head = tmp;
            tail = tmp;
        }
        else
        {
            tail->next = tmp;
            tail = tail->next;
        }
        length += 1;
    }

    LinkedList (int count){
        if (count < 0){
            throw std::runtime_error("count < 0");
        }
        if (count > 0) {
            head = new Elem();
            Elem *prev = head;
            for (size_t i = 1; i < count; ++i) {
                prev->next = new Elem();
                prev = prev->next;
            }
            tail = prev;
            length = count;
        }
    }

    LinkedList (std::vector<T>items, int count){
        if (count < 0){
            throw std::runtime_error("count < 0");
        }
        if (items.size() == 0){
            throw std::runtime_error("NULL list");
        }
        head = NULL;
        tail = NULL;
        for (int i = 0; i < count; i++) {
            Append(items[i]);
        }
        length = count;
    }

    LinkedList (T* items, int count){
        if (count < 0){
            throw std::runtime_error("count < 0");
        }
        if (items == NULL){
            throw std::runtime_error("NULL list");
        }
        head = NULL;
        tail = NULL;
        for (int i = 0; i < count; i++) {
            Append(items[i]);
        }
        length = count;
    }

    LinkedList (const LinkedList <T> & list ) : LinkedList() {
        *this = list;
    }

    ~LinkedList(){
        Elem *ptr = head;
        Elem *ptr_prev;
        while(ptr){
            ptr_prev = ptr;
            ptr = ptr->next;
            delete ptr_prev;
        }
    }

    T &GetFirst(){
        if (length == 0){
            throw std::runtime_error("Index out of range");
        }
        return head->data;
    }

    T &GetLast(){
        if (length == 0){
            throw std::runtime_error("Index out of range");
        }
        return tail->data;
    }

    LinkedList<T>* GetSubList(int startIndex, int endIndex){
        if (startIndex >= length || startIndex < 0) {
            throw std::runtime_error("Index out of range");
        }
        if (endIndex >= length || endIndex < 0) {
            throw std::runtime_error("Index out of range");
        }
        if (startIndex >= endIndex){
            throw std::runtime_error("Incorrect indexes");
        }
        Elem *ptr = head;
        for(int i=0; i<startIndex; i++){
            ptr = ptr->next;
        }
        LinkedList<T> *new_list = new LinkedList<T>();
        for(int i=startIndex; i<=endIndex; i++){
            (*new_list).Append(ptr->data);
            ptr = ptr->next;
        }

        return new_list;
    }

    int GetLength(){
        return length;
    }

    void Prepend(T item){
        Elem *tmp = new Elem;
        tmp->data = item;
        tmp->next = NULL;

        if(head == NULL)
        {
            head = tmp;
            tail = tmp;
        }
        else
        {
            tmp->next = head;
            head = tmp;
        }
        length += 1;
    }
    void InsertAt(T item, int index){
        if (index >= length || index < 0) {
            throw std::runtime_error("Index out of range");
        }

        Elem *tmp = new Elem;
        tmp->data = item;

        Elem *ptr = head;
        Elem *ptr_prev;
        for(int i=0; i<index; i++){
            ptr_prev = ptr;
            ptr = ptr->next;
        }
        if(ptr == head){
            tmp->next = head;
            head = tmp;
        } else {
            ptr_prev->next = tmp;
            tmp->next = ptr;
        }

        length += 1;
    }

    T Pop() {
        if (length < 1)
            throw std::range_error("Incorrect length");
        Elem *ptr = head;
        head = ptr->next;
        T data = ptr->data;
        delete ptr;
        length -= 1;
        if (length == 0) {
            tail = NULL;
            head = NULL;
        }
        return data;
    }

    LinkedList<T>* Concat(LinkedList<T> *list){
        if (list->head == NULL){
            throw std::runtime_error("NULL list");
        }
        LinkedList<T> *new_list = new LinkedList<T>;
        for(int i=0; i<this->GetLength(); i++){
            new_list->Append(this->Get(i));
        }
        for(int i=0; i<list->GetLength(); i++){
            new_list->Append(list->Get(i));
        }
        return new_list;
    }

};

#endif //LAB_2_LINKLIST_H
