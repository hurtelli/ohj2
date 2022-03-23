#include "queue.hh"
#include <iostream>

Queue::Queue(const unsigned int c)
{
    cycle_ = c;
}

Queue::~Queue()
{

}

void Queue::enqueue(const string &reg)
{
    if(!is_green_){
        Vehicle* newid = new Vehicle;
        newid->reg_num = reg;
        newid->next = nullptr;

        //jos que on tyhjä
        if(first_ == nullptr){
            std::cout<<"tyhjä que"<<std::endl;
            first_ = newid;
            last_ = newid;
            std::cout<<first_->reg_num<<std::endl;
            return;
        }

        //lisää sen perään
        last_->next = newid;
        last_ = newid;
    }
    else{
        std::cout<<"GREEN: Vehicle "<<reg<<" need not stop to wait"<<std::endl;
        is_green_ = false;
    }
}

void Queue::switch_light()
{
    //jos jonossa on auto
    if(first_){
        std::cout<<"GREEN: Vehicle(s) ";
        Vehicle* current = first_;
        unsigned int passed=0;
        while(current and current->next){
            //jos 3 autoa ei ole mennyt vielä
            if(passed<cycle_){
                //poistettava
                Vehicle* removable = current;
                std::cout<<removable->reg_num<<" ";
                //currentti sueraavaan

                current = current->next;
                //poistetaan poistettava
                delete removable;
            }
            first_ = current;
        }
        if(passed<cycle_){
            Vehicle* removable = current;
            std::cout<<removable->reg_num<<" ";
            delete removable;
            first_ = nullptr;
            last_ = nullptr;
        }
        is_green_ = false;
        std::cout<<"can go on";
    }
    //jos jonossa ei ole autoja pelkästään valokytkin toiminta
    else{
        if(is_green_){
            is_green_ = false;
            std::cout<<"RED: No vehicle in traffic lights"<<std::endl;
        }else{
            is_green_ = true;
            std::cout<<"GREEN: No vehicle in traffic lights"<<std::endl;
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
            std::cout<<"waiting in traffic lights."<<std::endl;
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
