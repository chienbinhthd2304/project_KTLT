#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include "Header.h"
#include <direct.h>

using namespace std;


int ngay_trong_thang_cua_nam_nhuan[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
int ngay_trong_thang_cua_nam_khong_nhuan[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

string address_Main_folder = "\\Main_folder",
address_Account_folder = "\\Main_folder\\Account_folder",
address_Student_Management_folder = "\\Main_folder\\Student_Management_folder",
address_Student_folder = "\\Main_folder\\Account_folder\\Student_folder",
address_Teacher_folder = "\\Main_folder\\Account_folder\\Teacher_folder";

//ham check ngay thanng
bool check_Nam_Nhuan(Date a) {
	if ((a.year % 400 == 0) || (a.year % 4 == 0 && a.year % 100 != 0))return 1;
	else return 0;
}

bool check_Ngay_Thang(Date a) {
	if (check_Nam_Nhuan(a) == 1) {
		if (a.day <= 0 || a.day > ngay_trong_thang_cua_nam_nhuan[a.month - 1] || a.month <= 0 || a.month > 12)return 0;
		else return 1;
	}
	else
	{
		if (a.day <= 0 || a.day > ngay_trong_thang_cua_nam_khong_nhuan[a.month - 1] || a.month <= 0 || a.month > 12)return 0;
		else return 1;
	}
}

void input_Day_and_Month(Date& a) {
	while (1)
	{
		cout << "Day:\n";
		cin >> a.day;
		cout << "Month:\n";
		cin >> a.month;
		cout << "Year:\n";
		cin >> a.year;
		if (check_Ngay_Thang(a) == 1)break;
		else cout << "Invalid Date! Try Agains!\n";
	}
}

void input_Object(Object& a) {
	cout << "MS:\n";
	cin >> a.MS;
	cout << "Name:\n";
	cin.ignore();
	cin.get(a.name, 40);
	cout << "Birthday:\n";
	input_Day_and_Month(a.birthday);
	cout << "Sex:\n";
	cin >> a.sex;
	cout << "Social ID:\n";
	cin >> a.Social_ID;
}

//ham dang ki tai khoan Giang Vien
void register_Teacher(string id, string pass) {
	string address = address_Teacher_folder;
	cout << "----------AN ACADEMIC STAFF----------\n";
	cout << "----------REGISTER----------\n";
	cout << "--------------------\n";
	cout << "ID:\n";
	cin >> id;
	cout << "password:\n";
	cin >> pass;
	fstream f;
	string temp = address + "\\" + id + ".txt";
	f.open(temp, ios::in);
	if (f.is_open())cout << "ID already use! Please, try agains!\n";
	else
	{
		Object a;
		fstream file;
		file.open(temp, ios::out);
		file << pass << endl;
		cout << "enter account information!\n";
		input_Object(a);
		file << a.MS << endl;
		file << a.name << endl;
		file << a.birthday.day << "/" << a.birthday.month << "/" << a.birthday.year << endl;
		file << a.sex << endl;
		file << a.Social_ID << endl;
		file.close();
	}
	f.close();
}

//them 1 nam hoc.
void add_school_Year() {
	string address = address_Student_Management_folder;
	string year;
	cout << "Please enter a school year!\n";
	cin >> year;
	string temp = address + "//" + year;
	if (_mkdir(temp.c_str()) == 0) {
		string temp_file = address + "\\List_school_year.txt";
		fstream f;
		f.open(temp_file, ios::app);
		f << year << endl;
		f.close();
		while (1) {
			int dem = 0;
			cout << "Please enter a semester numbers (2 or 3):\n";
			cin >> dem;
			if (dem == 2) {
				string temp1 = temp + "\\1";
				string temp2 = temp + "\\2";
				if (_mkdir(temp1.c_str()) == 0)cout << "creat successfull semester 1.\n";
				if (_mkdir(temp2.c_str()) == 0)cout << "creat successfull semester 2.\n";
				system("pause");
				break;
			}
			else if (dem == 3) {
				string temp1 = temp + "\\1";
				string temp2 = temp + "\\2";
				string temp3 = temp + "\\3";
				if (_mkdir(temp1.c_str()) == 0)cout << "creat successfull semester 1.\n";
				if (_mkdir(temp2.c_str()) == 0)cout << "creat successfull semester 2.\n";
				if (_mkdir(temp3.c_str()) == 0)cout << "creat successfull semester 3.\n";
				system("pause");
				break;
			}
			else cout << "Eror. Please try agians.\n";
		}
	}
	else {
		cout << "That school year already exists!\n";
		system("pause");
	}
}

//in ra danh sach nam hoc
void output_List_school_year() {
	cout << "List school year:\n";
	string address = address_Student_Management_folder + "\\List_school_year.txt";
	fstream f;
	f.open(address, ios::in);
	if (f.is_open()) {
		while (!f.eof()) {
			string temp;
			getline(f, temp);
			cout << temp << endl;
		}
	}
	else
	{
		cout << "Not foud List!\n";
	}
}

// tao cac khoa hoc
void add_subject() {
	output_List_school_year();
	string year;
	cout << "Please enter 1 school year in list!\n";
	cin >> year;
	string address = address_Student_Management_folder + "\\" + year;
	if (_mkdir(address.c_str()) == 0) {
		if (_rmdir(address.c_str()) == 0) {
			cout << "Not found this school year. Try Agains!\n"; system("pause");
		}
	}
	else
	{
		string temp;
		cout << "Please enter semester:\n";
		cin >> temp;
		string address_semester = address + "\\" + temp;
		if (_mkdir(address_semester.c_str()) == 0) {
			if (_rmdir(address_semester.c_str()) == 0) {
				cout << "Not found this semester. Try Agains!\n"; system("pause");
			}
		}
		else
		{
			fstream f;
			string address_subject = address_semester + "\\Subject.csv";
			f.open(address_subject, ios::out);
			if (f.is_open()) {
				cout << "Enter number of subject:\n";
				int dem = 0;
				cin >> dem;
				for (int i = 1; i <= dem; i++) {
					cout << "Subject " << i << ":\n";
					cout << "Enter Subject ID:\n";
					string id_subject;
					cin >> id_subject;
					cout << "Enter Subject name:\n";
					char name_subject[50];
					cin.ignore();
					cin.get(name_subject, 50);
					cout << "Enter credit number:\n";
					unsigned int credit;
					cin >> credit;
					f << id_subject << "," << name_subject << "," << credit << endl;
				}
			}
			cout << "added a subject List!\n";
			system("pause");
		}
	}
}

//Menu he thong quan li sinh vien
void Menu_Student_Management(string name) {
	int kt;
	do {
		system("cls");
		cout << "Wellcome " << name << endl;
		cout << "----------MENU----------\n";
		cout << "1.Add school year, creat semester.\n2.Creat a course.\n3.Veiw list of courses.\n4.Update courses information.\n0.Log out.\n";
		cin >> kt;
		switch (kt)
		{
		case 0:
			break;
		case 1:
			add_school_Year();
			break;
		case 2:
			add_subject();
			break;

		default:
			cout << "Please, try agains!\n";
			break;
		}
	} while (kt != 0);
}


//ham dang nhap
void Login_Account_Teacher(string id, string pass) {
	string address = address_Teacher_folder;
	cout << "----------AN ACADEMIC STAFF----------\n";
	cout << "----------LOGIN----------\n";
	cout << "--------------------\n";
	cout << "ID:\n";
	cin >> id;
	cout << "password:\n";
	cin >> pass;
	string temp = address + "\\" + id + ".txt";
	fstream f;
	f.open(temp, ios::in);
	if (!f.is_open())cout << "ID is not correct!\n";
	else {
		string ch;
		getline(f, ch);
		if (ch != pass)cout << "password is not correct!\n";
		else
		{
			string name;
			getline(f, name);
			getline(f, name);
			Menu_Student_Management(name);
		}
	}
}



//dang nhap tk Sinh vien
void Login_Account_Student() {
	string id, pass;
	cout << "----------STUDENT----------\n";
	cout << "----------LOGIN----------\n";
	cout << "--------------------\n";
	cout << "ID:\n";
	cin >> id;
	cout << "password (if the first time login password is Social ID):\n";
	cin >> pass;
	string address = address_Student_folder;
	string temp = address + "\\" + id + ".txt";
	fstream f;
	f.open(temp, ios::in);
	if (!f.is_open())cout << "ID is not correct!\n";
	else {
		string ch;
		getline(f, ch);
		if (ch != pass)cout << "password is not correct!\n";
		else
		{
			string name;
			getline(f, name);
			getline(f, name);
			cout << "Hello, Wellcome " << name << endl;
		}
	}
}


void Menu_Login_Register_Teacher() {
	string id, pass;
	int kt = 0;
	do {
		system("cls");
		cout << "----------AN ACADEMIC STAFF----------\n";
		cout << "1.Register.\n2.Login.\n0.Exit.\n";
		cin >> kt;
		switch (kt)
		{
		case 1:
			register_Teacher(id, pass);
			system("pause");
			break;
		case 2:
			Login_Account_Teacher(id, pass);
			system("pause");
			break;
		case 0:
			break;
		default:
			cout << "Please, try agains!\n";
			break;
		}
	} while (kt != 0);
}

void check_menu(int& kt) {
	cout << "1.Continue!\n0.Exit!\n";
	cin >> kt;
}
