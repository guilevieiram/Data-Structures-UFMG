#ifndef STACK
#define STACK
#include <iostream>
#include <string>

template <class T>
struct Item{
    int key;
    T content {};
    Item(int key, T content):key(key),content(content){};
    Item(int key):key(key){};
    ~Item(){};
};

template <class T>
struct StackCell{
    Item<T>* item;
    StackCell<T>* next;
    StackCell(Item<T>* item, StackCell<T>* next):item(item),next(next){};
    StackCell(Item<T>* item):item(item),next(nullptr){};
    StackCell(){};
};


template <class T>
class Stack{
    private:
    StackCell<T>* top;
    int size = 0;
    int item_key_counter = 0;
    public:
    Stack(){
        this->top = nullptr;
    };
    ~Stack(){
        this->clear();
    }
    class EmptyStackError{
        public:
        std::string message = "EmptyStackError: Trying to access an empty stack!";
    };
    bool is_empty(){
        if(this->size == 0){
            return true;
        }
        return false;
    }
    void push(T const &item){
        StackCell<T>* new_cell = new StackCell<T>(new Item<T>(item_key_counter,item),this->top);
        this->top = new_cell;
        item_key_counter++;
        this->size++;
    }
    Item<T> pop(){
        try{
            if(this->is_empty()){
                throw EmptyStackError();
            }
        }
        catch(EmptyStackError e){
            std::cout << __func__ << "-> " << e.message << std::endl;
        }

        StackCell<T>* temp = this->top->next;
        Item<T> item = *(this->top->item);
        delete this->top;
        this->top = temp;
        this->size--;
        return item;
    }
    void print(bool print_content=true){
        if(this->is_empty()){
            std::cout << "Empty Stack!" << std::endl;
            return;
        }
        StackCell<T>* temp = this->top;
        while(temp != nullptr){
            if(temp->next != nullptr){
                std::cout << temp->item->content << " -> ";
            } 
            else{
                std::cout << temp->item->content << " -> END" ;
            }
            temp = temp->next;
        }
        std::cout << std::endl;
    }
    void clear(){
        if(this->is_empty()){
            return;
        }
        while(!this->is_empty()){
            this->pop();
        }
        this->size = 0;
    }

};
#endif