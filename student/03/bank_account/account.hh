#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include <string>

class Account
{
public:
    // Constructor
    Account(const std::string& owner, bool has_credit = false);

    void print() const;
    void set_credit_limit(int amount);
    void save_money(int amount);
    void take_money(int amount);
    void transfer_to(Account& dest, int amount);

private:

    std::string owner_;

    void generate_iban();

    void account_money_set(int amount);

    static int running_number_;

    bool has_credit_;



    std::string iban_;



    int money_;

    int credit_limit_;

    int credit_left;


};

#endif // ACCOUNT_HH
