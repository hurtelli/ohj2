#include "queue.hh"
#include <iostream>

Queue::Queue(const unsigned int c)
{
    cycle_ = c;
}

Queue::~Queue()
{
    Vehicle* current = first_;
    while(current){
        Vehicle* removable = current;
        current = current->next;
        delete removable;
    }
}

void Queue::enqueue(const string &reg)
{

    if(!is_green_){
        Vehicle* newid = new Vehicle;
        newid->reg_num = reg;
        newid->next = nullptr;

        //jos que on tyhjä
        if(first_ == nullptr){
            first_ = newid;
            last_ = newid;
            return;
        }

        //lisää sen perään
        last_->next = newid;
        last_ = newid;
    }
    else{
        std::cout<<"GREEN: The vehicle "<<reg<<" need not stop to wait"<<std::endl;

    }
}

void Queue::dequeue()
{
    if(!first_){
        return;
    }
    //jos on seuraava
    if(first_->next){
        Vehicle* removable = first_;
        first_ = removable->next;
        //poistetaan poistettava
        delete removable;
        return;
    }else{ //jos ei ole seuraavaa autoa
        Vehicle* lonely = first_;
        delete lonely;
        first_ = nullptr;
        last_ = nullptr;
    }

}

void Queue::switch_light()
{
    //jos jonossa on auto
    if(first_){
        std::cout<<"GREEN: Vehicle(s) ";
        Vehicle* current = first_;
        unsigned int passed = 0;
        //löytyy seuraava jonosta ja passattu alle 3
        while(current and current->next and passed<cycle_){
            Vehicle* remove = current;
            std::cout<<remove->reg_num<<" ";
            current = remove->next;
            dequeue();
            ++passed;
        }
        //jos ei ole sueraavaa
        if(!current->next and passed<cycle_){
            std::cout<<current->reg_num<<" ";
            dequeue();
            passed++;
        }

        std::cout<<"can go on"<<std::endl;
    }

    //jos jonossa ei ole autoja pelkästään valokytkin toiminta
    else{
        if(is_green_){
            is_green_ = false;
            std::cout<<"RED: No vehicles waiting in traffic lights"<<std::endl;
        }else{
            is_green_ = true;
            std::cout<<"GREEN: No vehicles waiting in traffic lights"<<std::endl;
        }
    }

}

void Queue::reset_cycle(unsigned int cycle)
{
    cycle_ =cycle;


}

void Queue::print() const
{
    if(first_){
        if(!is_green_){
            std::cout<<"RED: Vehicle(s) ";
            Vehicle* current = first_;
            while(current and current->next){
                std::cout<<current->reg_num<<" ";
                current = current->next;
            }
            std::cout<<current->reg_num<<" ";
            std::cout<<"waiting in traffic lights"<<std::endl;
        }

    }
    else{
        if(is_green_){
            std::cout<<"GREEN: No vehicles in traffic lights"<<std::endl;
        }
        else{
            std::cout<<"RED: No vehicles in traffic lights"<<std::endl;
        }
    }


}
