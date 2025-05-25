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
void User::connectDevice(Type &device) {//添加设备，连接设备
    this->Devices.push_back(&device); 
    std::cout << "连接设备成功 ！" << std::endl;
}
void User::ChangeDevice(string DeviceName) {
    for (int i = 0;i<Devices.size();i++) {
		if (Devices[i]->get_name() == DeviceName) {
			Devices[i]->turn_Device();
		}
    }
	//else					
	cout << "没有找到这个设备" << endl;
}
void User::displayConnectedDevices() {
    std::cout << "连接的设备有:" << std::endl;
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
				cout << "数据库冲突\n";
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
	cout<<"=============== 登陆 ===============\n";
	cout<<"====================================\n";
	cout << endl;
	string name,pw;
	cout<<"输入您的用户名 :\n";
	cin >> name;
	cout<<"输入您的密码: \n";
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
			cout<<"登陆成功 ！\n";
			IsLoggedIn = true;
			LoggedUser = uu;
		}
	}
	else {
		cout<<"登陆失败 ！\n";
	}
}
void UserSystem::Logout() {
	IsLoggedIn = false;
	User u;
	LoggedUser = nullptr;
}
void UserSystem::Regist() {
	cout<<"====================================\n";
	cout<<"================ 注册 ==============\n";
	cout<<"====================================\n";
	cout << endl;
	string name,pw,pwr;
	int n=0,m=0;
	while (n!=-1) {
		cout<<"输入您的用户名 :\n";
		cin >> name;
		User *u;
		n=udb.Find(name,u);
		if (n!=-1) cout<<"该用户名已占用，请重新输入\n";
	}
	while (m==0) {
		cout<<"输入您的密码: \n";
		pw = GetPwFlow();
		cout<<"重复您的密码: \n";
		pwr = GetPwFlow();
		if (pw==pwr) m=1;
		else cout << "两次密码不一致，请重新输入\n";
	}
	User *u = new User(name,pw);
	//cout<<u;
	udb.Add(*u);
	udb.saveToFile();
	cout<<"注册成功\n";
}
template<class Type>
void UserSystem::CreateNewDevice() {
	cout<<"请输入设备名称\n";
	string name;
	cin>>name;
	Type *d = new Type(name);
	LoggedUser->connectDevice(*d);
}
void UserSystem::AddDevice() {
	cout<<"======================================\n";
	cout<<"=============== 添加设备 =============\n";
	cout<<"======================================\n";
	
	cout<<"根据提示选择所要创建的设备\n";
	cout<<"1. 冰箱\n";
	cout<<"2. 空调\n";
	cout<<"3. 洗衣机\n";
	cout<<"4. 电饭锅\n";
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
	cout << "请选择您想修改的设备名：" << endl;
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
	cout<<"================ 欢迎 ==============\n";
	cout<<"====================================\n";
	cout<<endl;
	cout<<"根据提示选择所要进行的操作\n";
	cout<<"0. 退出\n";
	int s;
	cout<<"1. 登陆\n";
	cout<<"2. 注册\n";
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
	cout << "==============尊敬的用户，欢迎您使用智能家居管理系统==============" << endl << endl;
	cout << "====================请选择你需要的功能==============="  << endl;
	cout << "1. 登出\n";
	cout << "2. 显示您现有的家具" << endl;
	cout << "3. 添加家具" << endl;		
	cout << "4. 修改家具的的状态" << endl;
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
