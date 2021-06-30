#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iostream>
#include "doctest.h"
#include "DynamicList.h"

TEST_CASE("Push Back"){
    DynamicList<int> list;
    for(int i = 0; i < 10; i++){
        list.push_back(i);
    }
    CHECK(list.get_first()->item == 0);
    CHECK(list.get_last()->item == 9);
    ListCell<int>* temp = list.get_first();
    for(int i = 0; i < 10; i++){
        CHECK(temp->item == i);
        if(i != 9){
            CHECK(temp->next != nullptr);
        }
        temp = temp->next;
    }
    CHECK(temp == nullptr);
    CHECK(list.get_size() == 10);
    list.clear();
    CHECK(list.get_size() == 0);
}
TEST_CASE("Push Front"){
    DynamicList<int> list;
    for(int i = 0; i < 10; i++){
        list.push_front(i);
    }
    CHECK(list.get_first()->item == 9);
    CHECK(list.get_last()->item == 0);
    ListCell<int>* temp = list.get_first();
    for(int i = 9; i >= 0; i--){
        CHECK(temp->item == i);
        if(i != 0){
            CHECK(temp->next != nullptr);
        }
        temp = temp->next;
    }
    CHECK(temp == nullptr);
    CHECK(list.get_size() == 10);
    list.clear();
    CHECK(list.get_size() == 0);
}
TEST_CASE("Push pos"){
    DynamicList<int> list;
    for(int i = 0; i < 10; i++){
        list.push_front(i);
        list.push_back((2*i)+2);
    }
    for(int i = 0; i < 5; i++){
        list.push_pos((i*5 + 3),i);
    }
    for(int i = 0; i < 5; i++){
        CHECK(list.get_cell(i)->item == (i*5 + 3));
        if(i < 4) CHECK(list.get_cell(i)->next->item == ((i+1)*5 + 3));
    }
}
TEST_CASE("Pop Front"){
    
}