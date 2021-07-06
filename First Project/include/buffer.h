#ifndef BUFFER
#define BUFFER
#include <iostream>
#include <string>
#include <cassert>
template <class T>
struct Item{
    T content{};
    Item(T c){
        this->content = c;
    };
    Item() = default;
    ~Item(){};
    
};
template <class T>
struct BufferCell{
    Item<T> item;
    BufferCell<T> *next;
    BufferCell(Item<T> item, BufferCell<T>* next):item(item),next(next){};
    BufferCell(Item<T> item):item(item),next(nullptr){};
    BufferCell(){};
};


template <class T>
class Buffer{
    private:
    BufferCell<T>* front;
    BufferCell<T>* back;
    int size = 0;
    public:
    Buffer(){
        this->front = new BufferCell<T>(Item<T>());
        this->back = this->front;
    };
    ~Buffer(){
        this->clear();
        this->sanity_check();
        delete this->front;
    }
    class EmptyBufferError{
        public:
        std::string message = "EmptyBufferError: Trying to access an empty Buffer!";
    };
    bool is_empty(){
        if(this->size == 0){
            return true;
        }
        return false;
    }
    int get_size(){
        return this->size;
    }
    void push_back(Item<T> item){
        BufferCell<T>* new_cell = new BufferCell<T>(item);
        this->back->next = new_cell;
        this->back = new_cell;
        this->size++;
    }
    void push_back(T &content){
        this->push_back(Item<T>(content));
    }
    void push_front(Item<T> item){
        BufferCell<T>* new_cell = new BufferCell<T>(item);
        new_cell->next = this->front->next;
        this->front->next = new_cell;
        this->size++;
    }
    Item<T> pop_front(){
        if(this->is_empty()){
            throw EmptyBufferError();
        }
        BufferCell<T>* temp = this->front;
        Item<T> item = this->front->next->item;
        this->front = this->front->next;
        delete temp;
        this->size--;
        return item;
    }
    Item<T> pop_pos(int pos){
        if(this->is_empty()){
            throw EmptyBufferError();
        }
        BufferCell<T> *temp = this->front, *aux;
        int curr_pos = -1;
        while(curr_pos != (pos-1)){
            temp = temp->next;
            curr_pos++;
        }
        aux = temp->next;
        Item<T> item = aux->item;
        temp->next = aux->next;
        delete aux;
        this->size--;
        if(temp->next == nullptr){
            this->back = temp;
        }
        return item;
    }
    void print(){
        if(this->is_empty()){
            std::cout << "Empty Buffer!" << std::endl;
            return;
        }
        BufferCell<T>* temp = this->front->next;
        std::cout << "Buffer:[";
        while(temp != nullptr){
            if(temp->next != nullptr){
                std::cout << temp->item.content << ",";
            } 
            else{
                std::cout << temp->item.content << "]" ;
            }
            temp = temp->next;
        }
        std::cout << std::endl;
    }
    void print_content();
    void clear(){
        if(this->is_empty()){
            return;
        }
        while(!this->is_empty()){
            this->pop_front();
        }
        this->size = 0;
    }
    void sanity_check(){
        if(this->is_empty()){
            assert(this->front == this->back);
            assert(this->front != nullptr);
        }
    }
};
#endif