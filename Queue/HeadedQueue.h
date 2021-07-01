#ifndef HEADEDQUEUE
#define HEADEDQUEUE
#include <iostream>
#include <string>

const int HEAD_FLAG = -1;
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
class HeadedQueue{
    private:
    QueueCell<T>* front;
    QueueCell<T>* back;
    int size = 0;
    int item_key_counter = 0;
    public:
    HeadedQueue(){
        this->front = new QueueCell<T>(new Item<T>(HEAD_FLAG));
        this->back = nullptr;
    };
    ~HeadedQueue(){
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
        QueueCell<T>* new_cell = new QueueCell<T>(new Item<T>(item_key_counter,item));
        this->back->next = new_cell;
        this->back = new_cell;
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

        QueueCell<T>* temp = this->front;
        Item<T> item = *(this->front->next->item);
        this->front = this->front->next;
        this->front->item->key = HEAD_FLAG;
        delete temp;
        this->size--;
        return item;
    }
    void print(bool print_content=true){
        if(this->is_empty()){
            std::cout << "Empty Queue!" << std::endl;
            return;
        }
        QueueCell<T>* temp = this->front->next;
        std::cout << "HEAD -> ";
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