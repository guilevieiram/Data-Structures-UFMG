#ifndef QUEUE
#define QUEUE
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
struct QueueCell{
    Item<T>* item;
    QueueCell<T>* next;
    QueueCell(Item<T>* item, QueueCell<T>* next):item(item),next(next){};
    QueueCell(Item<T>* item):item(item),next(nullptr){};
    QueueCell(){};
};


template <class T>
class Queue{
    private:
    QueueCell<T>* front;
    QueueCell<T>* back;
    int size = 0;
    int item_key_counter = 0;
    public:
    Queue(){
        this->front = nullptr;
        this->back = nullptr;
    };
    ~Queue(){
        this->clear();
    }
    class EmptyQueueError{
        public:
        std::string message = "EmptyQueueError: Trying to access an empty Queue!";
    };
    bool is_empty(){
        if(this->size == 0){
            return true;
        }
        return false;
    }
    void enqueue(T const &item){
        if(this->is_empty()){
            this->front = new QueueCell<T>(new Item<T>(item_key_counter,item),this->back);
        }
        else{
            if(this->back == nullptr){
                this->front->next = new QueueCell<T>(new Item<T>(item_key_counter,item));
                this->back = this->front->next;
            }
            else{
                QueueCell<T>* new_cell = new QueueCell<T>(new Item<T>(item_key_counter,item));
                this->back->next = new_cell;
                this->back = new_cell;
            }
        }
        item_key_counter++;
        this->size++;
    }
    Item<T> dequeue(){
        try{
            if(this->is_empty()){
                throw EmptyQueueError();
            }
        }
        catch(EmptyQueueError e){
            std::cout << __func__ << "-> " << e.message << std::endl;
        }

        QueueCell<T>* temp = this->front->next;
        Item<T> item = *(this->front->item);
        delete this->front;
        this->front = temp;
        this->size--;
        if(this->front == nullptr || this->front->next == nullptr){
            this->back = this->front;
        }
        return item;
    }
    void print(bool print_content=true){
        if(this->is_empty()){
            std::cout << "Empty Queue!" << std::endl;
            return;
        }
        QueueCell<T>* temp = this->front;
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
            this->dequeue();
        }
        this->size = 0;
    }

};

#endif