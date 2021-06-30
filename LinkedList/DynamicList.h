#include <iostream>
#include <string>
#ifndef DYNAMICLIST
#define DYNAMICLIST
// template <class T>
// struct Item{

// };

template <class T>
struct ListCell{
    ListCell<T>* next; 
    T item {};
    // bool is_empty = true;
    ListCell(T item, ListCell<T>* next):item(item),next(next){};
    ListCell(T item):ListCell(item,nullptr){};
    ListCell():ListCell({},nullptr){};
};

template <class T>
class AbstractList{
    protected:
    int size = 0;
    public:
    virtual bool is_empty() = 0;
    virtual int get_size() = 0;
    virtual T get_item(int pos) = 0;
    virtual void set_item(T const &item, int pos) = 0;
    virtual void push_back(T const &item)  = 0;
    virtual void push_front(T const &item)  = 0;
    virtual void push_pos(T const &item, int pos)  = 0;
    virtual void pop_back() = 0;
    virtual void pop_front() = 0;
    virtual void pop_pos(int pos) = 0;
    virtual void clear() = 0;
    virtual ListCell<T> search(T const &item) = 0;
    virtual void print() = 0;
    virtual ~AbstractList() {};
};

template <class T>
class DynamicList: public AbstractList<T>{
    private:
    ListCell<T>* first;
    ListCell<T>* last;
    public:
    class EmptyListError{
        public:
        std::string message = "EmptyListError: Trying to access an empty list!";
    };
    class IndexError{
        public:
        int pos;
        IndexError(int x):pos(x){};
    };
    DynamicList():first(nullptr),last(nullptr){};
    ~DynamicList(){
        this->clear();
    };
    ListCell<T>* get_first(){ //O(1)
        return this->first;
    }
    ListCell<T>* get_last(){ //O(1)
        return this->last;
    }
    int get_size() { //O(1)
        return this->size;
    };
    bool is_empty(){ //O(1)
        if(this->first == this->last && this->first == nullptr){
            return true;
        }
        return false;
    };
    ListCell<T>* get_cell(int pos){ //best: O(1), worst: O(n)
        try{
            if(this->is_empty()){
                throw EmptyListError();
            }
            else if(pos < 0 || pos >= this->get_size()){
                throw IndexError(pos);
            }
        }
        catch(EmptyListError e){
            std::cout << e.message << std::endl;
            return 0;
        }
        catch(IndexError i){
            std::cout << "IndexError: Index " << i.pos << " is out of bounds with list of size " << this->get_size() << std::endl;
            return 0;
        }
        ListCell<T>* temp = this->first;
        int curr_pos = 0;
        while(curr_pos != pos){
            curr_pos++;
            temp = temp->next;
        }
        return temp;
    };
    T get_item(int pos) { //best: O(1), worst: O(n)
        try{
            if(this->is_empty()){
                throw EmptyListError();
            }
            else if(pos < 0 || pos >= this->get_size()){
                throw IndexError(pos);
            }
        }
        catch(EmptyListError e){
            std::cout << e.message << std::endl;
            return 0;
        }
        catch(IndexError i){
            std::cout << "IndexError: Index " << i.pos << " is out of bounds with list of size " << this->get_size() << std::endl;
            return 0;
        }
        ListCell<T>* temp = this->get_cell(pos);
        return temp->item;
    };

    void set_item(T const &item, int pos){ //best: O(1), worst: O(n)
        try{
            if(this->is_empty()){
                throw EmptyListError();
            }
            else if(pos < 0 || pos >= this->get_size()){
                throw IndexError(pos);
            }
        }
        catch(EmptyListError e){
            std::cout << e.message << std::endl;
            return;
        }
        catch(IndexError i){
            std::cout << "IndexError: Index " << i.pos << " is out of bounds with list of size " << this->get_size() << std::endl;
            return;
        }
        ListCell<T>* temp = this->get_cell(pos);
        temp->item = item;
    };
    void push_back(T const &item) { //O(1)
        if(this->is_empty()){
            this->first = new ListCell<T>(item,this->last);
            this->size++;  
        }
        else{
            if(this->last == nullptr){
                this->last = new ListCell<T>(item);
                this->first->next = this->last;
                this->size++;
            }
            else{
                ListCell<T>* new_cell = new ListCell<T>(item);
                this->last->next = new_cell;
                this->last = new_cell;
                this->size++;
            }
        }
    };
    void push_front(T const &item){ //O(1)
        if(this->is_empty()){
            this->first = new ListCell<T>(item,this->last);
            this->size++;
        }
        else{
            ListCell<T>* temp = this->first;
            ListCell<T>* new_cell = new ListCell<T>(item,temp);
            this->first = new_cell;
            if(new_cell->next->next == nullptr){
                this->last = new_cell->next;
            }
            this->size++;
        }
    };
    void push_pos(T const &item,int pos){ //best: O(1), worst: O(n)
        try{
            if(this->is_empty()){
                throw EmptyListError();
            }
            else if(pos < 0 || pos >= this->get_size()){
                throw IndexError(pos);
            }
        }
        catch(EmptyListError e){
            std::cout << e.message << std::endl;
            return;
        }
        catch(IndexError i){
            std::cout << "IndexError: Index " << i.pos << " is out of bounds with list of size " << this->get_size() << std::endl;
            return;
        }
        if(pos == 0){
            this->push_front(item);
        }
        else if(pos == this->get_size - 1){
            this->push_back(item);
        }
        else{
            ListCell<T>* temp = this->get_cell(pos-1);
            ListCell<T>* new_cell = new ListCell<T>(item,temp->next);
            temp->next = new_cell;
            this->size++; 
        } 
    } ;
    void pop_back(){ //O(n)
        try{
            if(this->is_empty()){
                throw EmptyListError();
            }
        }
        catch(EmptyListError e){
            std::cout << e.message << std::endl;
            return;
        }
        ListCell<T>* temp = this->get_cell(this->size - 2);
        delete temp->next;
        temp->next = nullptr;
        this->last = temp;
        this->size--;
    };
    void pop_front(){ //O(1)
        try{
            if(this->is_empty()){
                throw EmptyListError();
            }
        }
        catch(EmptyListError e){
            std::cout << e.message << std::endl;
            return;
        }
        ListCell<T>* temp = this->first->next;
        delete this->first;
        this->first = temp;
        this->size--;
    };
    void pop_pos(int pos){ //best: O(1), worst: O(n)
        try{
            if(this->is_empty()){
                throw EmptyListError();
            }
            else if(pos < 0 || pos >= this->get_size()){
                throw IndexError(pos);
            }
        }
        catch(EmptyListError e){
            std::cout << e.message << std::endl;
            return;
        }
        catch(IndexError i){
            std::cout << "IndexError: Index " << i.pos << " is out of bounds with list of size " << this->get_size() << std::endl; 
            return;
        }
        if(pos == 0){
            this->pop_front();
        }
        else if(pos == this->get_size() - 1){
            this->pop_back();
        }
        else{
            ListCell<T>* temp = this->get_cell(pos-1);
            ListCell<T>* temp2 = temp->next->next;
            delete temp->next;
            temp->next = temp2;
            this->size--;
        }
    }; 
    void print() { //O(n)
        if(this->is_empty()){
            std::cout << "Empty List!" << std::endl;
            return;
        }
        ListCell<T>* temp = this->first;
        while(temp != nullptr){
            if(temp->next != nullptr){
                std::cout << temp->item << " -> ";
            } 
            else{
                std::cout << temp->item << " -> END" ;
            }
            temp = temp->next;
        }
        std::cout << std::endl;
    };
    void clear(){ //best: O(1), worst: O(n)
        if(this->is_empty()){
            return;
        }
        ListCell<T>* temp = this->first->next;
        while(temp != nullptr){
            this->first->next = temp->next;
            delete temp;
            temp = first->next;
        }
        delete this->first;
        this->first = nullptr;
        this->last = this->first; 
        this->size = 0;
    };
    ListCell<T> search(T const &item){ //best: O(1), worst: O(n)
        try{
            if(this->is_empty()){
                throw EmptyListError();
            }
        }
        catch(EmptyListError e){
            std::cout << e.message << std::endl;
            std::abort();
        }
        ListCell<T>* temp = this->first;
        int curr_pos = 0;
        while(temp->item != item){
            temp = temp->next;
            if(curr_pos > this->get_size()){
                break;
            }
        }
        if(temp->item == item){
            return *temp;
        }
        std::cout << "Item: " << item << " not found!" << std::endl;
        return ListCell<T>();
    };
};
#endif
