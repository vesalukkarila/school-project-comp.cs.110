#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include <string>

class Account
{
public:
    // Constructor
    Account(const std::string& owner, bool has_credit = false);

    // More methods
    void print() const;
    bool set_credit_limit(int luottoraja);
    void save_money(int talletettu_summa);
    void take_money(int nostettu_summa);
    void transfer_to(Account nimi, int siirto_summa);       //epävarma ekasta parametrista, onhan se sen tietotyyppi


private:
    // Generates IBAN (based on running_number_ below).
    // Allows no more than 99 accounts.
    void generate_iban();

    // Used for generating IBAN.
    // Static keyword means that the value of running_number_ is the same for
    // all Account objects.
    // In other words, running_number_ is a class-wide attribute, there is
    // no own copies of it for each object of the class.
    static int running_number_;

    // More attributes/methods
    std::string ownerattr_;     //olion attribuutti
    bool creditattr_;    //olion attribuutti

};

#endif // ACCOUNT_HH
