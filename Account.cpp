#include "Account.h"

void swap(Transaction *xp,Transaction *yp)  
{  
    Transaction temp = *xp;  
    *xp = *yp;  
    *yp = temp;  
}  
void bubbleSort(Transaction* arr,int n)  
{
	int i, j;  
	for (i = 0; i < n-1; i++){        
		for (j = 0; j < n-i-1; j++)
		{	
        		if (arr[j] > arr[j+1])
			{
				swap(&arr[j], &arr[j+1]);
			}
		}
	}	
}
int helper(Transaction* arr,time_t baslangic,time_t bitis,int size){
	int c=0;
	for (int i=0;i<size;i++)
	{
		if ((arr[i]>baslangic)&&(arr[i]<bitis)){c++;}
		else {continue;}
	}
	return c;
}
Account::Account(){
	_id=-1;
	_activity=NULL;
	_monthly_activity_frequency=NULL;
}
Account::Account(int id,Transaction** const activity,int* monthly_activity_frequency){
	int i; 
	_activity = new Transaction*[12];
	_monthly_activity_frequency= new int[12];
	_id=id;                   
	for(i=0;i<12;i++)
	{
		int c = monthly_activity_frequency[i];
		_monthly_activity_frequency[i]=c;
		_activity[i]=new Transaction[c];
		for (int j=0;j<c;j++)
		{
			_activity[i][j]=activity[i][j];			
		}
	}
	for (i=0;i<12;i++)
	{
		bubbleSort(_activity[i],_monthly_activity_frequency[i]);
	}
}
Account::~Account(){
	if (_activity!=NULL)
	{
		for (int i=0;i<12;i++){
			delete [] _activity[i];
		}
		delete []  _activity;
		delete [] _monthly_activity_frequency;
	}
}
Account::Account(const Account& rhs){
        _id=-1;
	_activity=NULL;
	_monthly_activity_frequency=NULL;
	*this=rhs;
}
Account::Account(const Account& rhs,time_t start_date,time_t end_date){
	int i=0;
        _activity = new Transaction*[12];
        _monthly_activity_frequency=new int[12];
        _id=rhs._id;
        for (i=0;i<12;i++)
        {
		int c=helper((rhs._activity)[i],start_date,end_date,(rhs._monthly_activity_frequency)[i]);
		_monthly_activity_frequency[i]=c;
		_activity[i]=new Transaction[c];
		for (int j=0,k=0;j<(rhs._monthly_activity_frequency)[i];j++)
		{
			if (((rhs._activity)[i][j]>start_date)&&((rhs._activity)[i][j]<end_date))
			{
				_activity[i][k]=(rhs._activity)[i][j];
				k++;
			}
			else {continue;}
		}
	}
        for (i=0;i<12;i++)
        {
                bubbleSort(_activity[i],_monthly_activity_frequency[i]);
        }
}
Account::Account(Account&& rhs){
	_id=rhs._id;
	_activity=rhs._activity;
	_monthly_activity_frequency=rhs._monthly_activity_frequency;
	rhs._id=-1;
	rhs._activity=NULL;
	rhs._monthly_activity_frequency=NULL;
}
Account& Account::operator=(Account&& rhs){
	if (this!=&rhs){
		if (_activity!=NULL)
		{
			for (int i=0;i<12;i++)
			{
                		delete [] _activity[i];
        		}
        		delete []  _activity;
        		delete [] _monthly_activity_frequency;
		}
        _id=rhs._id;
        _activity=rhs._activity;
        _monthly_activity_frequency=rhs._monthly_activity_frequency;
        rhs._id=-1;
        rhs._activity=NULL;
        rhs._monthly_activity_frequency=NULL;
	}
	return *this;
}
Account& Account::operator=(const Account&rhs){
	if (this!=&rhs)
	{
		int i=0;
		if (_activity!=NULL)
		{
			for (int k=0;k<12;k++)
        		{
                		delete [] _activity[k];
        		}
        		delete []  _activity;
        		delete [] _monthly_activity_frequency;
		}
		_activity = new Transaction*[12];
        	_monthly_activity_frequency=new int[12];
        	_id=rhs._id;
        	for (i=0;i<12;i++)
        	{
                	int c = (rhs._monthly_activity_frequency)[i];
                	_monthly_activity_frequency[i]=c;
                	_activity[i]=new Transaction[c];
                	for (int j=0;j<c;j++)
                	{
                        	_activity[i][j]=(rhs._activity)[i][j];
                	}
        	}
        	for (i=0;i<12;i++)
        	{
                	bubbleSort(_activity[i],_monthly_activity_frequency[i]);
        	}
	}
	return *this;
}
bool Account::operator==(const Account& rhs) const {
	if (_id==rhs._id){return true;}
	return false;
}
bool Account::operator==(int id) const {
	if (_id==id){return true;}
	return false;
}
Account& Account::operator+=(const Account& rhs){
	if (this!=&rhs)
	{
		int i=0;
		int *rhsfrekans=rhs._monthly_activity_frequency;
		int arr[12];
		int c;
		for (i=0;i<12;i++)
		{
			arr[i]=rhsfrekans[i]+_monthly_activity_frequency[i];
		}	
		for (i=0;i<12;i++)
		{
			int j=0;
			c=arr[i];
			Transaction *objecttransaction=_activity[i];
			Transaction *rhstransaction=(rhs._activity)[i];	
			_activity[i]=new Transaction[c];
			for (;j<_monthly_activity_frequency[i];j++)                                 
			{
				_activity[i][j]=objecttransaction[j];
			}
			for (int k=0;k<rhsfrekans[i];k++,j++)
			{
				_activity[i][j]=rhstransaction[k];
			}	
			delete []  objecttransaction;
		}
		for (i=0;i<12;i++)
		{
			_monthly_activity_frequency[i]=arr[i];
			bubbleSort(_activity[i],_monthly_activity_frequency[i]);
		}
	}
	return *this;
}
double Account::balance(){
	double sonuc=0;
	for (int i=0;i<12;i++)
	{
		for (int j=0;j<_monthly_activity_frequency[i];j++)
		{
			sonuc=_activity[i][j]+sonuc;
		}
	}
	return sonuc;
}
double Account::balance(time_t end_date){
        double sonuc=0;
        for (int i=0;i<12;i++)
        {
                for (int j=0;j<_monthly_activity_frequency[i];j++)
                {
			if (_activity[i][j]<end_date)
			{
				sonuc=_activity[i][j]+sonuc;
			}
                }
        }
        return sonuc;
}
double Account::balance(time_t start_date,time_t end_date){
        double sonuc=0;
        for (int i=0;i<12;i++)
        {
                for (int j=0;j<_monthly_activity_frequency[i];j++)
                {
                        if (_activity[i][j]<end_date && _activity[i][j]>start_date)
                        {
                                sonuc=_activity[i][j]+sonuc;
                        }
                }
        }
        return sonuc;
}
std::ostream& operator<<(std::ostream& os,const Account& account){
	if (account._activity==NULL || account._monthly_activity_frequency==NULL)
	{
		os<<-1<<"\n";
		return os;
	}
	else
	{
		os<<account._id<<"\n";
		for (int i=0;i<12;i++)
        	{
                	for (int j=0;j<(account._monthly_activity_frequency)[i];j++)
                	{
				os<<(account._activity)[i][j];
			}
		}
		return os;
	}
}








		



	



			
		
	
















































































