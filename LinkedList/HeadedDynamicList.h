#include <iostream>
#include <string>
#ifndef HEADEDDYNAMICLIST
#define HEADEDDYNAMICLIST
int item_key_counter = 0;
const int HEAD_FLAG = -1;
const int NOT_FOUND_FLAG = -2;

template <class T>
struct Item{
    int key;
    T content;
    Item(int x, T c):key(x),content(c){};
    Item(int x):key(x){};
    ~Item(){};
    
};
template <class T>
struct ListCell{
    ListCell<T>* next; 
    Item<T>* item;
    ListCell(Item<T>* item,ListCell<T>* next): item(item),next(next){};
    ListCell(Item<T>* item): item(item),next(nullptr){};
    ListCell():next(nullptr){};
    ~ListCell(){};
};

template <class T>
class HeadedAbstractList{
    protected:
    int size = 0;
    public:
    virtual bool is_empty() = 0;
    virtual int get_size() = 0;
    virtual Item<T> get_item(int pos) = 0;
    virtual void set_item(T const &item, int pos) = 0;
    virtual void push_back(T const &item)  = 0;
    virtual void push_front(T const &item)  = 0;
    virtual void push_pos(T const &item, int pos)  = 0;
    virtual void pop_back() = 0;
    virtual void pop_front() = 0;
    virtual void pop_pos(int pos) = 0;
    virtual void clear() = 0;
    virtual Item<T> search(int key) = 0;
    virtual void print(bool print_content=true) = 0;
    virtual ~AbstractList() {};
};

template <class T>
class HeadedDynamicList: public HeadedAbstractList<T>{
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
    HeadedDynamicList(){
        this->first = new ListCell<T>(new Item<T>(HEAD_FLAG),nullptr);
        this->last = nullptr;
    };
    ~HeadedDynamicList(){
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
        if(this->first->next == nullptr){
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
            std::cout << __func__ <<"(" << i.pos << ")-> IndexError: Index " << i.pos << " is out of bounds with list of size " << this->get_size() << std::endl; 
            return 0;
        }
        ListCell<T>* temp = this->first;
        int curr_pos = -1;
        while(curr_pos != pos){
            curr_pos++;
            temp = temp->next;
        }
        return temp;
    };
    Item<T> get_item(int pos) { //best: O(1), worst: O(n)
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
            std::cout << __func__ <<"(" << i.pos << ")-> IndexError: Index " << i.pos << " is out of bounds with list of size " << this->get_size() << std::endl; 
            return 0;
        }
        ListCell<T>* temp = this->get_cell(pos);
        return *(temp->item);
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
            std::cout << __func__ <<"(" << item << "," << i.pos << ")-> IndexError: Index " << i.pos << " is out of bounds with list of size " << this->get_size() << std::endl; 
            return;
        }
        ListCell<T>* temp = this->get_cell(pos);
        temp->item = new Item<T>(item_key_counter,item);
        item_key_counter++;
    };
    void push_back(T const &item) { //O(1)
        if(this->is_empty()){
            this->first->next = new ListCell<T>(new Item<T>(item_key_counter,item),this->last);
            this->last = this->first->next;
            this->size++;  
            item_key_counter++;
        }
        else{
            ListCell<T>* new_cell = new ListCell<T>(new Item<T>(item_key_counter,item));
            this->last->next = new_cell;
            this->last = new_cell;
            this->size++;
            item_key_counter++;
        }

    };
    void push_front(T const &item){ //O(1)
        if(this->is_empty()){
            this->first->next = new ListCell<T>(new Item<T>(item_key_counter,item),this->last);
            this->size++;
            item_key_counter++;
        }
        else{
            ListCell<T>* temp = this->first->next;
            ListCell<T>* new_cell = new ListCell<T>(new Item<T>(item_key_counter,item),temp);
            this->first->next = new_cell;
            if(new_cell->next->next == nullptr){
                this->last = new_cell->next;
            }
            this->size++;
            item_key_counter++;
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
            std::cout << __func__ <<"(" << item << "," << i.pos << ")-> IndexError: Index " << i.pos << " is out of bounds with list of size " << this->get_size() << std::endl; 
            return;
        }
        if(pos == 0){
            this->push_front(item);
        }
        else if(pos == this->get_size() - 1){
            this->push_back(item);
        }
        else{
            ListCell<T>* temp = this->get_cell(pos-1);
            ListCell<T>* new_cell = new ListCell<T>(new Item<T>(item_key_counter,item),temp->next);
            temp->next = new_cell;
            this->size++; 
            item_key_counter++;
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
            std::cout << __func__ <<"(" << i.pos << ")-> IndexError: Index " << i.pos << " is out of bounds with list of size " << this->get_size() << std::endl; 
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
    void print(bool print_content=true) { //O(n)
        if(this->is_empty()){
            std::cout << "Empty List!" << std::endl;
            return;
        }
        ListCell<T>* temp = this->first->next;
        std::cout << "HEAD -> ";
        if(print_content){
            while(temp != nullptr){
                if(temp->next != nullptr){
                    std::cout << temp->item->content << " -> ";
                } 
                else{
                    std::cout << temp->item->content << " -> END" ;
                }
                temp = temp->next;
            }
        }
        else{
            while(temp != nullptr){
                if(temp->next != nullptr){
                    std::cout << temp->item->key << " -> ";
                } 
                else{
                    std::cout << temp->item->key << " -> END" ;
                }
                temp = temp->next;
            }
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
    Item<T> search(int key){ //best: O(1), worst: O(n)
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
        int curr_pos = -1;
        while(temp->item->key != key){
            temp = temp->next;
            if(curr_pos > this->get_size()){
                break;
            }
        }
        if(temp->item->key == key){
            return *(temp->item);
        }
        std::cout << "Item with key: " << key << " not found!" << std::endl;
        return Item<T>(NOT_FOUND_FLAG);
    };
};
#endif