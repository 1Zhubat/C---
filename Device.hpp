#ifndef __DEVICE__
#define __DEVICE__

#include<iostream>
#include<stdexcept>
#include<cmath>
#include<string>
#include<iomanip>

using std::cin;
using std::cout;
using std::string;
using std::setfill;
using std::setw;
using std::cout;
using std::endl;
using std::ostream;
using std::istream;


class Device {
protected:
	//品牌
	string Device_name;
	bool Device_status;
	double pow;         //功率


	static int count;        //描述派生类对象的数目

public:
	Device() = default;
	Device(string name, double w = 0, bool status = false);
	virtual ~Device() = default;

	virtual void display_DeviceInfo() const;     //展示设备信息
	friend ostream& operator<< (ostream& out, const Device& d);
	friend istream& operator>> (istream& in, Device& d);

	virtual bool get_Device_status() const { return Device_status == true; }     //查看设备是否开启
	virtual void turn_Device();
	virtual string get_name() const { return Device_name; }
	
	/////////////////////////////////////
	const string type = "Device";

};

int Device::count = 0;   //初始化设备数量为0； 

ostream& operator<< (ostream& out, const Device& d) {
	out << d.type << endl;
	out << d.Device_name << endl;
	out << d.Device_status << endl;
	out << d.pow << endl;
	return out;
}
istream& operator >> (istream& in, Device& d) {

	in >> d.Device_name;
	in >> d.Device_status;
	in >> d.pow;
	return in;
}


class refeigerator :public Device {
public:
	//冰箱类构造函数
	refeigerator() = default;
	refeigerator(Device device, double in_, double fr_);

	~refeigerator() override { count--; }

	double get_in_temp() const { return in_temp; }
	double get_fr_temp() const { return fr_temp; }
	string get_name() const { return Device_name; }

	bool get_Device_status() const override; //获取设备状态

	void display_DeviceInfo() const override; //显示设备参数


	void chan_in_temp();    //调解工作温度
	void chan_fr_temp();

	friend ostream& operator<< (ostream& out, const refeigerator& d);
	friend istream& operator>> (istream& in, refeigerator& d);

	void turn_Device() override;  //改变工作状态 

	const string type = "refeigerator";

private:
	double in_temp;   //保鲜温度 4---8摄氏度之间
	double fr_temp;   //冷冻温度 -18-10摄氏度之间



};
ostream& operator<< (ostream& out, const refeigerator& d) {
	out << d.type << endl;
	out << d.Device_name << endl;
	out << d.Device_status << endl;
	out << d.pow << endl;
	out << d.in_temp << endl;
	out << d.fr_temp << endl;
	return out;
}
istream& operator>> (istream& in, refeigerator& d) {
	in >> d.Device_name;
	in >> d.Device_status;
	in >> d.pow;
	in >> d.in_temp;
	in >> d.fr_temp;
	return in;

}

//洗衣机
class washer : public Device {
public:
	washer() = default;
	washer(Device device, string wa_mod, int water_mod);
	~washer() override { count--; }

	void display_DeviceInfo() const override; //显示设备的各项状态

	bool get_Device_status() const override;
	string get_name() const { return Device_name; }

	void turn_Device() override;  //改变工作状态
	void turn_water_mod();       //调节洗衣机水量模式

	friend ostream& operator<< (ostream& out, const washer& d);
	friend istream& operator>> (istream& in, washer& d);

	const string type = "washer";

private:
	string wa_mode;		//洗衣机的模式
	int water_mode;     //水量模式



};

ostream& operator<< (ostream& out, const washer& d) {
	out << d.type << endl;
	out << d.Device_name << endl;
	out << d.Device_status << endl;
	out << d.pow << endl;
	out << d.wa_mode << endl;
	out << d.water_mode << endl;
	return out;
}

istream& operator>> (istream& in, washer& d) {
	in >> d.Device_name;
	in >> d.Device_status;
	in >> d.pow;
	in >> d.wa_mode;
	in >> d.water_mode;
	return in;

}

//空调
class air : public Device {
public:
	air() = default;
	air(Device device, string mod, double temp);
	~air() override { count--; }

	void display_DeviceInfo() const override; //显示设备的各项状态


	void turn_Device() override;  //改变工作状态

	double get_air_temp() { return air_temp; }
	string get_air_mod() { return air_mod; }
	string get_name() const { return Device_name; }

	friend ostream& operator<< (ostream& out, const air& d);
	friend istream& operator>> (istream& in, air& d);

	const string type= "air";

private:

	string air_mod;
	double air_temp;



};


ostream& operator<< (ostream& out, const air& d) {
	out << d.type << endl;
	out << d.Device_name << endl;
	out << d.Device_status << endl;
	out << d.pow << endl;
	out << d.air_mod << endl;
	out << d.air_temp << endl;
	return out;
}

istream& operator>> (istream& in, air& d) {
	in >> d.Device_name;
	in >> d.Device_status;
	in >> d.pow;
	in >> d.air_mod;
	in >> d.air_temp;
	return in;

}





//电饭锅
class rice_cooker : public Device {
public:
	rice_cooker() = default;
	rice_cooker(Device device, string mod);
	~rice_cooker() override { count--; }

	void display_DeviceInfo() const override; //显示设备的各项状态

	void turn_Device() override;  //改变工作状态
	string get_name() const { return Device_name; }

	friend ostream& operator<< (ostream& out, const rice_cooker& d);
	friend istream& operator>> (istream& in, rice_cooker& d);

	const string type= "rice_cooker";


private:
	string cooker_mod;
};



ostream& operator<< (ostream& out, const rice_cooker& d) {
	out << d.type << endl;
	out << d.Device_name << endl;
	out << d.Device_status << endl;
	out << d.pow << endl;
	out << d.cooker_mod << endl;

	return out;
}

istream& operator>> (istream& in, rice_cooker& d) {
	in >> d.Device_name;
	in >> d.Device_status;
	in >> d.pow;
	in >> d.cooker_mod;

	return in;

}



Device::Device(string name, double w, bool status) : Device_name{ name }, pow{ w }, Device_status{ status }
{

	if (Device_status == false) pow = 0;
}



void Device::display_DeviceInfo() const {
	cout << "=============" << "显示设备信息" << "============" << endl;

	cout << "设备：" << Device_name << endl;

	cout << "功率：" << pow << endl;

	cout << "============== =================" << endl;
}





void Device::turn_Device() {
	Device_status = !Device_status;
}

//冰箱类
refeigerator::refeigerator(Device device, double in_ = 8, double fr_ = -10) : Device{ device }, in_temp{ in_ }, fr_temp{ fr_ } {

	count++;
}

bool refeigerator::get_Device_status() const
{
	return (Device_status == true);
}           //获取设备状态

void refeigerator::display_DeviceInfo() const {    //显示设备各项参数
	cout << "=============" << "显示设备信息" << "============" << endl;
	cout << "设备：" << Device_name << endl;
	cout << "功率：" << pow << "w" << endl;
	cout << "工作状态：" << get_Device_status() << endl;
	if (Device_status == true) {
		cout << "设备开启" << endl;
		cout << "保鲜模式温度：" << get_in_temp() << endl;
		cout << "冷冻模式温度：" << get_fr_temp() << endl;
		return;
	}
	else {
		cout << "设备关闭" << endl;
		return;
	}
	cout << "============== =================" << endl;
}



//当输入正确数据时，完成修改
void refeigerator::chan_in_temp() {    //调解工作温度
	while (get_Device_status()) {
		try {
			cout << "请输入保鲜室想调节的温度 在（4~8℃之间）:";
			double t;
			cin >> t;

			if (t < 4 || t > 8) {
				throw std::out_of_range("温度超出范围，请输入4~8之间的温度。");
			}

			in_temp = t;
			break;
		}
		catch (const std::exception& e) {
			std::cerr << "异常: " << e.what() << std::endl;

		}
	}
}
void refeigerator::chan_fr_temp() {
	while (get_Device_status()) {
		try {
			cout << "请输入冷冻室想调节的温度 在-18~-10℃之间:" << endl;
			double t;
			cin >> t;

			if (t < -18 || t > -10) {
				throw std::out_of_range("温度超出范围，请输入-18~-10之间的温度：");
			}

			in_temp = t;
			break;
		}
		catch (const std::exception& e) {
			std::cerr << "异常: " << e.what() << std::endl;

		}
	}
}



//改变工作状态
void refeigerator::turn_Device() {
	int choice;

	while (get_Device_status()) {
		cout << "当前设备状态：" << endl;
		display_DeviceInfo();
		cout << "根据提示修改当前设备状态：" << endl;
		cout << "按下1，修改设备的保鲜温度" << endl;
		cout << "按下2，修改设备的冷冻温度" << endl;
		cout << "按下3，开启/关闭设备" << endl;
		cout << "按下0，退出修改" << endl;

		cin >> choice;

		switch (choice) {
		case 1:
			chan_in_temp();  // 调用修改保鲜温度的函数
			cout << "状态修改成功，当前状态：" << endl;
			this->pow = abs(fr_temp) + abs(in_temp) * 1;
			display_DeviceInfo();
			break;
		case 2:
			chan_fr_temp();  // 调用修改冷冻温度的函数
			cout << "状态修改成功，当前状态：" << endl;
			//功率计算
			this->pow = abs(fr_temp) + (in_temp) * 1;

			display_DeviceInfo();
			break;
		case 3:
			Device_status = !Device_status;
			cout << "状态修改成功，当前状态：" << endl;
			if (this->Device_status == 0)
				this->pow = 0;
			else
				this->pow = abs(fr_temp) + abs(in_temp) * 1;
			display_DeviceInfo();
			break;
		case 0:
			return;  // 退出循环和函数
		default:
			cout << "无效的选择，请重新输入。" << endl;
		}
	}
}




//洗衣机类
washer::washer(Device device, string wa_mod = "一般模式", int water_mod = 1) : Device{ device }, wa_mode{ wa_mod }, water_mode{ water_mod } { count++; }

bool washer::get_Device_status() const
{
	if (Device_status == true) {
		cout << "设备开启" << endl;
		return true;
	}
	else {
		cout << "设备关闭" << endl;
		return false;
	}

}
void washer::display_DeviceInfo() const {//显示设备的各项参数
	cout << "=============" << "显示设备信息" << "============" << endl;

	cout << "设备：" << Device_name << endl;
	cout << "功率：" << pow << "w" << endl;
	cout << "工作状态：" << get_Device_status() << endl;
	if (Device_status == true) {
		cout << "设备开启" << endl;
		return;
	}
	else {
		cout << "设备关闭" << endl;
		return;
	}
	cout << "============== =================" << endl;
}




void washer::turn_water_mod() {      //调节洗衣机水量模式
	int choice;
	while (Device_status == true) {
		cout << " 当前水量模式为" << water_mode << endl;
		cout << "\n请选择你要调节的水量模式：" << endl;
		cout << "输入1，调节水量模式为1，少数水量模式" << endl;
		cout << "输入2，调节水量模式为2，中等水量模式" << endl;
		cout << "输入3，调节水量模式为3，多数水量模式" << endl;
		cout << "输入0，退出水量模式" << endl;

		cin >> choice;

		switch (choice) {
		case(1):
			water_mode = 1;
			cout << "状态修改成功" << endl;
			break;
		case(2):
			water_mode = 2;
			cout << "状态修改成功" << endl;
			break;
		case(3):
			water_mode = 3;
			cout << "状态修改成功" << endl;
			break;
		case(0):
			cout << "已退出水量模式" << endl;
			return;
		default:
			cout << "无效的选择，请重新输入。" << endl;
		}
	}
}

void washer::turn_Device() {         //调节洗衣机模式
	int choice;

	while (get_Device_status()) {
		cout << "当前设备状态：" << endl;
		display_DeviceInfo();
		cout << "\n根据提示修改当前设备状态：" << endl;
		cout << "按下1，洗涤模式为干洗模式" << endl;
		cout << "按下2，洗涤模式为一般模式" << endl;
		cout << "按下3，开启/关闭设备" << endl;
		cout << "按下0，退出修改" << endl;

		cin >> choice;

		switch (choice) {
		case 1:
			wa_mode = "干洗模式";  // 调用修改保鲜温度的函数
			cout << "状态修改成功，当前状态：" << endl;
			this->pow = 30;
			display_DeviceInfo();
			break;
		case 2:
			wa_mode = "一般模式";  // 调用修改冷冻温度的函数
			cout << "状态修改成功，当前状态：" << endl;
			//功率计算
			this->pow = 20;

			display_DeviceInfo();
			break;
		case 3:
			Device_status = !Device_status;
			cout << "状态修改成功，当前状态：" << endl;
			if (this->Device_status == 0)
				this->pow = 0;
			else
				this->pow = 0;
			display_DeviceInfo();
			break;
		case 0:
			return;  // 退出循环和函数
		default:
			cout << "无效的选择，请重新输入。" << endl;
		}
	}
}


//空调类
air::air(Device device, string mod = "制冷模式", double temp = 30.0)
	: Device{ device }, air_mod{ mod }, air_temp{ temp }

{
	count++;
}

void air::display_DeviceInfo() const { //显示设备的各项状态
	cout << "=============" << "显示设备信息" << "============" << endl;

	cout << "设备：" << Device_name << endl;
	cout << "功率：" << pow << "w" << endl;
	cout << "工作状态：" << endl;
	if (Device_status == true) {
		cout << "设备开启" << endl;
		cout << "工作模式：" << endl;
		cout << air_mod << endl;
		cout << "工作温度：" << endl;
		cout << air_temp << endl;
		return;
	}
	else {
		cout << "设备关闭" << endl;
		return;
	}
	cout << "============== =================" << endl;
}



void air::turn_Device() { //改变工作状态
	cout << "当前设备状态：" << endl;
	display_DeviceInfo();
	int choice;
	while (Device_status == true) {
		cout << "\n根据提示修改当前设备状态：" << endl;
		cout << "按下1，调节为制暖模式" << endl;
		cout << "按下2，调节为制冷模式" << endl;
		cout << "按下3，调节温度" << endl;
		cout << "按下4，开启/关闭设备" << endl;
		cout << "按下0，退出修改" << endl;

		cin >> choice;

		switch (choice) {
		case 1:
			air_mod = "制暖模式";  // 调用修改保鲜温度的函数
			cout << "状态修改成功，当前状态：" << endl;
			this->pow = air_temp * 3;
			display_DeviceInfo();
			break;
		case 2:
			air_mod = "制冷模式";  // 调用修改冷冻温度的函数
			cout << "状态修改成功，当前状态：" << endl;
			//功率计算
			this->pow = air_temp * 3;

			display_DeviceInfo();
			break;
		case 3:
			double t;
			cin >> t;
			air_temp = t;
			cout << "状态修改成功，当前状态：" << endl;
			this->pow = air_temp * 3;
			display_DeviceInfo();
			break;
		case 4:
			Device_status = !Device_status;
			cout << "状态修改成功，当前状态：" << endl;
			if (this->Device_status == 0)
				this->pow = 0;
			else
				this->pow = air_temp * 3;
			display_DeviceInfo();
			break;
		case 0:
			return;  // 退出循环和函数
		default:
			cout << "无效的选择，请重新输入。" << endl;
		}
	}
}

//double air::get_air_temp() {
//
//}
//string air::get_air_mod() {
//
//}

//电饭锅类
rice_cooker::rice_cooker(Device device, string mod = "煮饭模式") : Device{ device }, cooker_mod{ mod } { count++; }
void rice_cooker::display_DeviceInfo() const {  //显示设备的各项状态
	cout << "=============" << "显示设备信息" << "============" << endl;

	cout << "设备：" << Device_name << endl;
	cout << "功率：" << pow << "w" << endl;
	cout << "工作状态：" << endl;
	if (Device_status == true) {
		cout << "设备开启" << endl;
		cout << "工作模式：" << endl;
		cout << cooker_mod << endl;
		return;
	}
	else {
		cout << "设备关闭" << endl;
		return;
	}
	cout << "============== =================" << endl;

}


//改变工作状态
void rice_cooker::turn_Device() {
	cout << "当前设备状态：" << endl;
	display_DeviceInfo();
	int choice;
	while (Device_status == true) {
		cout << "\n根据提示修改当前设备状态：" << endl;
		cout << "按下1，调节为煮粥模式" << endl;
		cout << "按下2，调节为米饭模式" << endl;
		cout << "按下3，调节为煲汤模式" << endl;
		cout << "按下4，开启/关闭设备" << endl;
		cout << "按下0，退出修改" << endl;

		cin >> choice;

		switch (choice) {
		case 1:
			cooker_mod = "煮粥模式";  // 调用修改保鲜温度的函数
			cout << "状态修改成功，当前状态：" << endl;
			this->pow = 20;
			display_DeviceInfo();
			break;
		case 2:
			cooker_mod = "米饭模式";  // 调用修改冷冻温度的函数
			cout << "状态修改成功，当前状态：" << endl;
			//功率计算
			this->pow = 10;

			display_DeviceInfo();
			break;
		case 3:
			double t;
			cin >> t;
			cooker_mod = "煲汤模式";
			cout << "状态修改成功，当前状态：" << endl;
			this->pow = 20;
			display_DeviceInfo();
			break;
		case 4:
			Device_status = !Device_status;
			cout << "状态修改成功，当前状态：" << endl;
			if (this->Device_status == 0)
				this->pow = 0;
			display_DeviceInfo();
			break;
		case 0:
			return;  // 退出循环和函数
		default:
			cout << "无效的选择，请重新输入。" << endl;
		}
	}
}


#endif
