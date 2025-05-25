#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<limits>
#include<vector>
#include<conio.h>
#include<stdexcept>
#include<typeinfo>
#include"Device.hpp"

using std::string;

class User {
	private:
		size_t hash;
		string salt;
		std::vector<Device*> Devices;
	public:
		string name;
	public:
		User() =default;
		User(string n,string pw);
		User(string n, size_t h,string s,std::vector<Device*> &d);
		bool CheckPassword(string pw);
		void ChangePassword(string pw);
		bool CheckName(string n);
		void ChangeName(string n);
		friend bool operator==(const User&,const User&);
		friend std::ostream& operator<<(std::ostream& os,const User& u);
		friend std::istream& operator>>(std::istream& is,User& u);
		
		template<class Type>
		void connectDevice(Type& device);
		void ChangeDevice(string DeviceName);
		void displayConnectedDevices();
};
User::User(string n,string pw) {
	name = n;
    salt = std::to_string(rand());
    hash= std::hash<string>{}(pw+salt);
}
User::User(string n,size_t h,string s,std::vector<Device*> &d) {
	name = n;
	hash = h;
	salt = s;
	for(auto it : d){
		Devices.push_back(it);
	}
}
bool User::CheckPassword(string pw) {
	size_t h = std::hash<string>{}(pw+salt);
	return h==hash;
}
void User::ChangePassword(string pw) {
	salt = std::to_string(rand());
	hash= std::hash<string>{}(pw+salt);
}
bool User::CheckName(string n) {
	return n==name;
}
void User::ChangeName(string n) {
	name = n;
}
bool operator==(const User &u1,const User &u2) {
	bool n,h,s,d;
	n=(u1.name==u2.name);
	h=(u1.hash==u2.hash);
	s=(u1.salt==u2.salt);
	d=(u1.Devices.size()==u2.Devices.size());
	if (d) {
		for (int i = 0;i<u1.Devices.size();i++) {
			if (u1.Devices[i]->get_name()!=u2.Devices[i]->get_name())
				d = false;
				break;
		}
	}
	return n&&h&&s&&d;
}
template<class Type>
void User::connectDevice(Type &device) {//����豸�������豸
    this->Devices.push_back(&device); 
    std::cout << "�����豸�ɹ� ��" << std::endl;
}
void User::ChangeDevice(string DeviceName) {
    for (int i = 0;i<Devices.size();i++) {
		if (Devices[i]->get_name() == DeviceName) {
			Devices[i]->turn_Device();
		}
    }
	//else					
	cout << "û���ҵ�����豸" << endl;
}
void User::displayConnectedDevices() {
    std::cout << "���ӵ��豸��:" << std::endl;
    for (int i = 0;i<Devices.size();i++) {
        //std::cout << it->get_name() << std::endl;
        //cout<<*it;
		Devices[i]->display_DeviceInfo();
    }
}

std::ostream& operator<<(std::ostream& os,const User& u) {

	os<<u.name<<'\n';
	os<<u.hash<<'\n';
	os<<u.salt<<'\n';
	os<<u.Devices.size()<<'\n';
	for (int j = 0; j<u.Devices.size();j++) {
		Device *p = u.Devices[j];
		if (typeid(*p)==typeid(refeigerator)) {
			refeigerator *d = dynamic_cast<refeigerator*>(p);
			os<<(*d);
		} else if (typeid(*p)==typeid(washer)) {
			washer *d = dynamic_cast<washer*>(p);
			os<<(*d);
		} else if (typeid(*p)==typeid(air)) {
			air *d = dynamic_cast<air*>(p);
			os<<(*d);
		} else if (typeid(*p)==typeid(rice_cooker)) {
			rice_cooker *d = dynamic_cast<rice_cooker*>(p);
			os<<(*d);
		} else if (typeid(*p)==typeid(Device)) {
			Device *d = u.Devices[j];
			os<<(*d);
		}
	}
	return os;
}
std::istream& operator>>(std::istream& is,User& u) {
	is>>u.name;
	is>>u.hash;
	is>>u.salt;
	int DeviceNum;
	is>>DeviceNum;
	cout<<u.name <<"has "<<DeviceNum<<"devices\n";
	for (int j = 0; j<DeviceNum;j++) {
		string DeviceType;
		is>>DeviceType;
		if (DeviceType=="refeigerator") {
			refeigerator *d = new refeigerator;
			is>>*d;
			u.connectDevice(*d);
		} else if (DeviceType=="washer") {
			washer *d = new washer;
			is>>*d;
			u.connectDevice(*d);
		} else if (DeviceType=="air") {
			air *d = new air;
			is>>*d;
			u.connectDevice(*d);
		} else if (DeviceType=="rice_cooker") {
			rice_cooker *d = new rice_cooker;
			is>>*d;
			u.connectDevice(*d);
		} else if (DeviceType=="Device") {
			Device *d = new Device;
			is>>*d;
			u.connectDevice(*d);
		} else {
			std::cerr<<"UnKnow Device\n";
			return is;
		}
	}
	return is;
}







class UserDB {
	private:
		std::vector<User> db;
	public:
		int size();
		void Add(User&);
		User* Find2(string);
		int Find(string,User*);
		User* at2(int);
		int at(int,User*);
		void saveToFile();	
		void loadFromFile();
};

int UserDB::size() {
	return db.size();
}
void UserDB::Add(User &u) {
	User uu;
	for(auto it : db) {
		if (it.CheckName(u.name)) {
			if (!(it==u)) 
				cout << "���ݿ��ͻ\n";
			return;
		}
	}
	db.push_back(u);
	//cout<<db.back();
	cout<<"AddOK\n";
}
User* UserDB::Find2(string n) {
	for(int i=0;i<db.size();i++) {
		if (db[i].CheckName(n)) {
			//cout<<db[i];
			//cout<<"Find2!\n";
			return &(db[i]);
		}
	}
	return nullptr;
}
int UserDB::Find(string n,User *u) {
	int i=0;
	for(i=0;i<db.size();i++) {
		if (db[i].CheckName(n)) {
			u = &(db[i]);
			cout<<(*u);
			cout<<"Find!\n";
			return i;
		}
	}
	u = nullptr;
	return -1;
}
User* UserDB::at2(int n) {
	if (n<0||n>=db.size())
		return nullptr;
	else return &db[n];
}
int UserDB::at(int n,User *u) {
	if (n<0||n>=db.size()) {
		u = nullptr;
		return -1;
	} else {
		u = &db[n];
		return 0;
	}
}

void UserDB::saveToFile() {
	std::ofstream ofile;
	ofile.open("Data.db");//,std::ios::out);//|std::ios::binary);
	User *u;
	//cout<<db.size();
	cout<<"\nSave!\n";
	ofile<<db.size()<<'\n';
	for (int i = 0; i<db.size();i++) {
		u = this->at2(i);
		//cout<<(*u);
		ofile<<(*u)<<'\n';
	}
	ofile.close();
	cin.ignore((std::numeric_limits<std::streamsize>::max)(),'\n');
};
void UserDB::loadFromFile() {
	std::ifstream ifile;
	ifile.open("Data.db");//,std::ios::in);//|std::ios::binary);
	int usernum = -1;
    ifile>>usernum;
    if (usernum==-1) return;
	for (int i = 0; i<usernum;i++) {
		User *u = new User;
		ifile>>(*u);
		Add(*u);
	}
    ifile.close();
}




string GetPwFlow() {
	char a;
	string t;
	while ((a=getch())!='\r') {
		if (a!='\b') {
			t.push_back(a);
			putchar('*');
			}
		else {
			t.pop_back();
			putchar('\b');
			putchar(' ');
			putchar('\b');
		}
	}
	cout<<"\n";
	return t;
}





class UserSystem {
	private:
		UserDB udb;
		bool IsLoggedIn;
		User *LoggedUser;
	private:
		void Regist();
		void Login();
		void Logout();
		void ChangePassword();
		void AddDevice();
		void ChangeDevice();
		void connectDevice();
		void displayConnectedDevices();
		template<class Type>
		void CreateNewDevice();
	public:
		UserSystem() : IsLoggedIn{false} {};
		void Init();
		int SystemMenu();
		int UserMenu();
		int Menu();
};
void UserSystem::Init() {
	IsLoggedIn = false;
	udb.loadFromFile();
}

void UserSystem::Login() {
	cout<<"====================================\n";
	cout<<"=============== ��½ ===============\n";
	cout<<"====================================\n";
	cout << endl;
	string name,pw;
	cout<<"���������û��� :\n";
	cin >> name;
	cout<<"������������: \n";
	pw = GetPwFlow();
	
	User *uu = udb.Find2(name);
	//if (uu!=nullptr)cout<<(*uu);
	if (uu!=nullptr) {
/*	int n;
	n=udb.Find(name,uu);
	cout<<(*uu);
	cout<<"Her";
	if (n!=-1) {
*/		if (uu->CheckPassword(pw)) {
			cout<<"��½�ɹ� ��\n";
			IsLoggedIn = true;
			LoggedUser = uu;
		}
	}
	else {
		cout<<"��½ʧ�� ��\n";
	}
}
void UserSystem::Logout() {
	IsLoggedIn = false;
	User u;
	LoggedUser = nullptr;
}
void UserSystem::Regist() {
	cout<<"====================================\n";
	cout<<"================ ע�� ==============\n";
	cout<<"====================================\n";
	cout << endl;
	string name,pw,pwr;
	int n=0,m=0;
	while (n!=-1) {
		cout<<"���������û��� :\n";
		cin >> name;
		User *u;
		n=udb.Find(name,u);
		if (n!=-1) cout<<"���û�����ռ�ã�����������\n";
	}
	while (m==0) {
		cout<<"������������: \n";
		pw = GetPwFlow();
		cout<<"�ظ���������: \n";
		pwr = GetPwFlow();
		if (pw==pwr) m=1;
		else cout << "�������벻һ�£�����������\n";
	}
	User *u = new User(name,pw);
	//cout<<u;
	udb.Add(*u);
	udb.saveToFile();
	cout<<"ע��ɹ�\n";
}
template<class Type>
void UserSystem::CreateNewDevice() {
	cout<<"�������豸����\n";
	string name;
	cin>>name;
	Type *d = new Type(name);
	LoggedUser->connectDevice(*d);
}
void UserSystem::AddDevice() {
	cout<<"======================================\n";
	cout<<"=============== ����豸 =============\n";
	cout<<"======================================\n";
	
	cout<<"������ʾѡ����Ҫ�������豸\n";
	cout<<"1. ����\n";
	cout<<"2. �յ�\n";
	cout<<"3. ϴ�»�\n";
	cout<<"4. �緹��\n";
	int s;
	cin>>s;
	switch (s) {
		case 1:
			CreateNewDevice<refeigerator>();
			break;
		case 2:
			CreateNewDevice<air>();
			break;
		case 3:
			CreateNewDevice<washer>();
			break;
		case 4:
			CreateNewDevice<rice_cooker>();
			break;
		default:
			break;
	}
	udb.saveToFile();
}
void UserSystem::ChangeDevice() {
	LoggedUser->displayConnectedDevices();
	cout << "��ѡ�������޸ĵ��豸����" << endl;
	string s2;
	cin >> s2;
	LoggedUser->ChangeDevice(s2);
	udb.saveToFile();									
}
int UserSystem::Menu() {
	int aaa=0;
	while (aaa == 0) {
		if (!IsLoggedIn)
			aaa = SystemMenu();
		else
			aaa = UserMenu();
	}
	return aaa;
}
int UserSystem::SystemMenu() {
	cout<<"====================================\n";
	cout<<"================ ��ӭ ==============\n";
	cout<<"====================================\n";
	cout<<endl;
	cout<<"������ʾѡ����Ҫ���еĲ���\n";
	cout<<"0. �˳�\n";
	int s;
	cout<<"1. ��½\n";
	cout<<"2. ע��\n";
	cin >>s;
	switch (s) {
		case 1:	
			Login();		 	
			break;
		case 2:
			Regist();
			break;
		case 0:
			return 1;
			break;
		default:
			return 1;
			break;
	}
	return 0;
}
int UserSystem::UserMenu() {
	cout << "==============�𾴵��û�����ӭ��ʹ�����ܼҾӹ���ϵͳ==============" << endl << endl;
	cout << "====================��ѡ������Ҫ�Ĺ���==============="  << endl;
	cout << "1. �ǳ�\n";
	cout << "2. ��ʾ�����еļҾ�" << endl;
	cout << "3. ��ӼҾ�" << endl;		
	cout << "4. �޸ļҾߵĵ�״̬" << endl;
	int s;
	cin >>s;
	switch (s) {
		case 1:
			Logout();			 	
			break;
		case 2:
			LoggedUser->displayConnectedDevices();
			break;
		case 3 :
			AddDevice();   
			break;
		case 4 :
			ChangeDevice();
			break;	
		case 0:
			return 1;
			break;
		default:
			return 1;
			break;
	}
	return 0;
}
