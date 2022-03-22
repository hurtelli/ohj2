#include "cards.hh"
#include <iostream>
#include <memory>

Cards::Cards()
{

}

Cards::~Cards()
{
    Card_data* current = top_;
    while(current){
        Card_data* removable = current;
        current = current->next;
        delete removable;
    }

}

void Cards::add(int id)
{

    Card_data* newid = new Card_data;
    newid->data = id;
    newid->next = nullptr;

    if(top_ == nullptr){
        top_ = newid;
        return;
    }

    newid->next = top_;
    top_ = newid;


}

void Cards::print_from_top_to_bottom(std::ostream& s)
{

    Card_data* current = top_;
    int n=1;
    while(current){
        s<<n<<": "<<current->data<<std::endl;
        current = current->next;
        ++n;
    }
}

bool Cards::bottom_to_top()
{
    Card_data* current = top_;
    while(current and current->next){
        current = current->next;
    }

    Card_data* newid = new Card_data;
    newid->data = current->data;

    newid->next = top_;
    top_ = newid;

    Card_data* current2 = top_;
    while(current2 and current2->next != current){
        current2 = current2->next;
    }
    current2->next = nullptr;


    return true;
}

bool Cards::top_to_bottom()
{
    Card_data* current = top_;
    Card_data* newid = new Card_data;
    newid->data = current->data;
    newid->next = nullptr;
    Card_data* current2 = top_;
    while(current2 and current2->next){
        current2 = current2->next;
    }

    current2->next = newid;

    Card_data* current3 = top_;
    top_ = current3->next;
    return true;
}

bool Cards::remove(int &id){
    id = top_->data;
    Card_data* current = top_;

    top_ = current->next;

    if(current->data != id){
        return false;
    }

    delete current;
    return true;
}







