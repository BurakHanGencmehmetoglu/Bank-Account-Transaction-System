#include "Transaction.h"



Transaction::Transaction (){
	_amount=-1;
	_date=-1;
}

Transaction::Transaction (double amount,time_t date){
	_amount=amount;
	_date=date;
}
Transaction::Transaction (const Transaction& rhs){
	_amount=-1;
	_date=-1;
	*this=rhs;
}
bool Transaction::operator<(const Transaction& rhs) const {
	if (difftime(_date,rhs._date) < 0) {
		return true;
	}
	return false;
}
bool Transaction::operator>(const Transaction& rhs) const {
        if (difftime(_date,rhs._date) > 0) {
                return true;
        }
        return false;
}
bool Transaction::operator<(const time_t date) const {
        if (difftime(_date,date) < 0) {
                return true;
        }
        return false;
}
bool Transaction::operator>(const time_t date) const {
        if (difftime(_date,date) > 0) {
                return true;
        }
        return false;
}
double Transaction::operator+(const Transaction& rhs){
	double a;
	a=_amount+rhs._amount;
	return a;
}
double Transaction::operator+(const double add){
        double a;
        a=_amount+add;
        return a;
}
Transaction& Transaction::operator=(const Transaction& rhs){
	_amount=rhs._amount;
	_date=rhs._date;
	return *this;
}
std::ostream& operator << (std::ostream& os,const Transaction& transaction) {
	time_t a=transaction._date;
	struct tm *convert = localtime(&a);
	int c=(convert->tm_mon)+1;
	int year=(convert->tm_year)+1900;
	os<<transaction._amount<<"\t"<<"-"<<"\t";
	os<<convert->tm_hour<<":"<<convert->tm_min<<":"<<convert->tm_sec<<"-";
	os<<convert->tm_mday<<"/"<<c<<"/"<<year<<"\n";
	return os;
}

	










































































