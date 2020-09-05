#include "Bank.h"
bool helper(Account* arr,const Account& rhs,int size){
	for (int i=0;i<size;i++)
	{
		if (arr[i]==rhs)
		{
			return true;
		}
	}
	return false;
}
void helper2(Account* arr,const Account& rhs,int size){
	for (int i=0;i<size;i++)
	{
		if (arr[i]==rhs)
		{
			arr[i]+=rhs;
		}
	}
}
bool helper3(Account& account)
{
	int arr[12]; 
	struct tm some_date = {0};
    	some_date.tm_hour = 0;   some_date.tm_min = 0; some_date.tm_sec = 0;
    	some_date.tm_year = 120; some_date.tm_mon = 0; some_date.tm_mday = 1;
    	time_t ocak1 = mktime(&some_date);
    	some_date.tm_hour = 0;   some_date.tm_min = 0; some_date.tm_sec = 0;
    	some_date.tm_year = 119; some_date.tm_mon = 1; some_date.tm_mday = 1;
    	time_t subat1 = mktime(&some_date);
    	some_date.tm_hour = 0;   some_date.tm_min = 0; some_date.tm_sec = 0;
    	some_date.tm_year = 119; some_date.tm_mon = 2; some_date.tm_mday = 1;
    	time_t mart1 = mktime(&some_date);
    	some_date.tm_hour = 0;   some_date.tm_min = 0; some_date.tm_sec = 0;
    	some_date.tm_year = 119; some_date.tm_mon = 3; some_date.tm_mday = 1;
    	time_t nisan1 = mktime(&some_date);
    	some_date.tm_hour = 0;   some_date.tm_min = 0; some_date.tm_sec = 0;
    	some_date.tm_year = 119; some_date.tm_mon = 4; some_date.tm_mday = 1;
    	time_t mayis1 = mktime(&some_date);
    	some_date.tm_hour = 0;   some_date.tm_min = 0; some_date.tm_sec = 0;
    	some_date.tm_year = 119; some_date.tm_mon = 5; some_date.tm_mday = 1;
    	time_t haziran1 = mktime(&some_date);
    	some_date.tm_hour = 0;   some_date.tm_min = 0; some_date.tm_sec = 0;
    	some_date.tm_year = 119; some_date.tm_mon = 6; some_date.tm_mday = 1;
    	time_t temmuz1 = mktime(&some_date);
    	some_date.tm_hour = 0;   some_date.tm_min = 0; some_date.tm_sec = 0;
    	some_date.tm_year = 119; some_date.tm_mon = 7; some_date.tm_mday = 1;
    	time_t agustos1 = mktime(&some_date);
    	some_date.tm_hour = 0;   some_date.tm_min = 0; some_date.tm_sec = 0;
    	some_date.tm_year = 119; some_date.tm_mon = 8; some_date.tm_mday = 1;
    	time_t eylul1 = mktime(&some_date);
    	some_date.tm_hour = 0;   some_date.tm_min = 0; some_date.tm_sec = 0;
    	some_date.tm_year = 119; some_date.tm_mon = 9; some_date.tm_mday = 1;
    	time_t ekim1 = mktime(&some_date);
    	some_date.tm_hour = 0;   some_date.tm_min = 0; some_date.tm_sec = 0;
    	some_date.tm_year = 119; some_date.tm_mon = 10; some_date.tm_mday = 1;
    	time_t kasim1 = mktime(&some_date);
    	some_date.tm_hour = 0;   some_date.tm_min = 0; some_date.tm_sec = 0;
    	some_date.tm_year = 119; some_date.tm_mon = 11; some_date.tm_mday = 1;
    	time_t aralik1 = mktime(&some_date);
	arr[0]=account.balance(subat1);
	arr[1]=account.balance(mart1)-account.balance(subat1);
	arr[2]=account.balance(nisan1)-account.balance(mart1);
	arr[3]=account.balance(mayis1)-account.balance(nisan1);
	arr[4]=account.balance(haziran1)-account.balance(mayis1);
	arr[5]=account.balance(temmuz1)-account.balance(haziran1);
	arr[6]=account.balance(agustos1)-account.balance(temmuz1);
	arr[7]=account.balance(eylul1)-account.balance(agustos1);	
	arr[8]=account.balance(ekim1)-account.balance(eylul1);
	arr[9]=account.balance(kasim1)-account.balance(ekim1);
	arr[10]=account.balance(aralik1)-account.balance(kasim1);
	arr[11]=account.balance()-account.balance(aralik1);
	for (int i=0;i<11;i++)
	{
		if (arr[i]<0 && arr[i+1]<0)
		{
			return false;
		}
	}
	return true;
}
int helper4(Account* arr,int size)
{
	int k=0;
	for (int i=0;i<size;i++)
	{
		if (helper3(arr[i])){k++;}
		else{continue;}
	}
	return k;
}
Bank::Bank(){
	_bank_name="not_defined";
	_users=NULL;
	_user_count=0;
}
Bank::Bank(std::string bank_name,Account* const users,int user_count){
	_bank_name=bank_name;
	_user_count=user_count;
	_users=new Account[user_count];
	for (int i=0;i<user_count;i++)
	{
		_users[i]=users[i];
	}
}
Bank::~Bank(){
	if (_users!=NULL){
		delete  [] _users;
                _users=NULL;
		_bank_name="not_defined";
		_user_count=0;
	}
}
Bank::Bank(const Bank& rhs){
        _bank_name=rhs._bank_name;
        _user_count=rhs._user_count;
        _users=new Account[rhs._user_count];
        for (int i=0;i<rhs._user_count;i++)
        {
                _users[i]=(rhs._users)[i];
        }
}
Bank& Bank::operator+=(const Bank& rhs){
	if (this!=&rhs)
	{
		int i=0;
		int c=_user_count+rhs._user_count;
		Account* temp=_users;
		_users=new Account[c];
		for (;i<_user_count;i++)
		{
			_users[i]=temp[i];
		}
		delete [] temp;
		temp=rhs._users;
		for (int k=0;k<rhs._user_count;k++)
		{
			if (helper(_users,temp[k],i))
			{
				helper2(_users,temp[k],i);
			}
			else
			{
				_users[i]=temp[k];
				i++;
			}
		}
		_user_count=i;
	}
	return *this;
}
Bank& Bank::operator+=(const Account& new_acc){
	if (helper(_users,new_acc,_user_count))
	{
		helper2(_users,new_acc,_user_count);
	}
	else 
	{
		int i=0;
                int c=_user_count+1;
                Account* temp=_users;
                _users=new Account[c];
                for (i=0;i<_user_count;i++)
                {
                        _users[i]=temp[i];
                }
		_users[i]=new_acc;
		_user_count+=1;
		delete [] temp;
	}
	return *this;
}
Account& Bank::operator[](int account_id){
	for (int i=0;i<_user_count;i++)
	{
		if (_users[i]==account_id)
		{
			return _users[i];
		}
	}
	return _users[0];
}
std::ostream& operator<<(std::ostream& os,const Bank& bank){
	if (bank._users==NULL){os<<-1<<"\n";}
	else
	{
		double b=0;
		os<<bank._bank_name<<"\t";
		os<<helper4(bank._users,bank._user_count)<<"\t";
		for (int i=0;i<bank._user_count;i++)
		{
			b+=(bank._users[i]).balance();
		}
		os<<b<<"\n";
	}
	return os;
}







	







































































