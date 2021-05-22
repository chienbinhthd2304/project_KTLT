#ifndef _Header_h_
#define _Header_h_

using namespace std;

struct Date
{
	unsigned int day;
	unsigned int month;
	unsigned int year;
};

struct Object
{
	unsigned int MS;
	char name[40];
	Date birthday;
	string sex;
	unsigned int Social_ID;
};



void Menu_Login_Register_Teacher();
void Login_Account_Student();

#endif // !_Header_h_