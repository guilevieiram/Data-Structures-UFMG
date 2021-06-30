#ifndef ABSTRACTLIST
#define ABSTRACTLIST
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
#endif