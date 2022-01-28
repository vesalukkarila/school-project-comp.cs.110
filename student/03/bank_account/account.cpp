#include "account.hh"
#include <iostream>

Account::Account(const std::string& owner, bool has_credit):
    ownerattr_(owner), creditattr_(has_credit), luottorajaattr_(0), rahaatililla_(0), iban_("")
{
    generate_iban();

}

void Account::print() const
{
    std::cout << ownerattr_ << " : " << iban_ << " : " << rahaatililla_ << " euros" << std::endl;

}

void Account::set_credit_limit(int luottomaara)      //bool voidiks?
{
    if (creditattr_ == false)
    {
        std::cout << "Cannot set credit limit: the account has no credit card" << std::endl;

    }
    else
    {
        luottorajaattr_ = luottomaara;
    }
}

void Account::save_money(int talletettu_summa)
{
    rahaatililla_ += talletettu_summa;

}

bool Account::take_money(int nostettu_summa)
{
    if (nostettu_summa < rahaatililla_ or (creditattr_ == true and rahaatililla_ + luottorajaattr_ > nostettu_summa))
    {
        rahaatililla_ -= nostettu_summa;
        std::cout << nostettu_summa << " euros taken: new balance of " << iban_
                 << " is " << rahaatililla_ << " euros" << std::endl;
        return 0;
    }

    else
    {
        if (creditattr_ == false)
            std::cout << "Cannot take money: balance underflow" << std::endl;
        else if (creditattr_ == true)
            std::cout << "Cannot take money: credit limit overflow" << std::endl;
        return 1;
    }
}

void Account::transfer_to(Account& nimi, int siirto_summa)
{
    if (take_money(siirto_summa) == 1)

        std::cout << "Transfer from " << iban_ << " failed" << std::endl;

    else
        nimi.save_money(siirto_summa);
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
