#include "account.hh"
#include <iostream>

Account::Account(const std::string& owner, bool has_credit):
    owner_(owner), has_credit_(has_credit)
{
    generate_iban();
    account_money_set(0);

}




// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}

void Account::print() const
        {

            std::cout << owner_ << " : " << iban_ << " : " << money_ << std::endl;
        }

void Account::set_credit_limit(int amount)
{
    if (Account::has_credit_)
    {
        credit_limit_ = amount;
    }
    else
    {
        std::cout << "Cannot set credit limit: the account has no credit card"<<std::endl;
    }
}

void Account::save_money(int amount)
{
    Account::money_ += amount;

}

void Account::take_money(int amount)
{
    if (Account::has_credit_)
    {

       if (money_ + Account::credit_limit_ >= amount)
            {
                Account::credit_left = (money_+ credit_limit_) - amount;
                money_ -= amount;

                std::cout << amount << " euros taken: new balance of " << Account::iban_ << " is " << money_ << " euros"<<std::endl;
            }
       else
            {
                std::cout <<  "Cannot take money: credit limit overflow"<< std::endl;;
            }

     }
     else
    {
        if (money_ < amount)
        {
            std::cout << "Cannot take money: balance underflow"<<std::endl;
        }
        else
        {
            money_ -= amount;
            std::cout << amount << " euros taken: new balance of " << Account::iban_ << " is " << money_ << " euros" << std::endl;
        }
    }
}


void Account::transfer_to(Account& dest, int amount)
{
    Account& kohde = dest;
    if(Account::has_credit_)
    {
        if((Account::money_ + Account::credit_left) > amount)
        {

            Account::money_ -= amount;
            kohde.money_ += amount;
            std::cout << amount << " euros taken: new balance of "<< Account::iban_ << " is "<< money_ << " euros" << std::endl;
        }
        else
        {

            std::cout << "Cannot take money: credit limit overflow" << std::endl;
            std::cout << "Transfer from " << Account::iban_ << " failed" << std::endl;
        }
    }
    else
    {
        if(Account::money_ > amount)
        {
            Account::money_ -= amount;
            kohde.money_ += amount;
            std::cout << amount << " euros taken: new balance of "<< Account::iban_ << " is "<< money_ << " euros" << std::endl;
        }
        else
        {
            std::cout << "Cannot take money: balance underflow" << std::endl;
            std::cout << "Transfer from " << Account::iban_ << " failed" << std::endl;
        }
    }

}

void Account::account_money_set(int amount)
{
    money_ = amount;
}


