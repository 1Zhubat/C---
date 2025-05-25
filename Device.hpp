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
	//Ʒ��
	string Device_name;
	bool Device_status;
	double pow;         //����


	static int count;        //����������������Ŀ

public:
	Device() = default;
	Device(string name, double w = 0, bool status = false);
	virtual ~Device() = default;

	virtual void display_DeviceInfo() const;     //չʾ�豸��Ϣ
	friend ostream& operator<< (ostream& out, const Device& d);
	friend istream& operator>> (istream& in, Device& d);

	virtual bool get_Device_status() const { return Device_status == true; }     //�鿴�豸�Ƿ���
	virtual void turn_Device();
	virtual string get_name() const { return Device_name; }
	
	/////////////////////////////////////
	const string type = "Device";

};

int Device::count = 0;   //��ʼ���豸����Ϊ0�� 

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
	//�����๹�캯��
	refeigerator() = default;
	refeigerator(Device device, double in_, double fr_);

	~refeigerator() override { count--; }

	double get_in_temp() const { return in_temp; }
	double get_fr_temp() const { return fr_temp; }
	string get_name() const { return Device_name; }

	bool get_Device_status() const override; //��ȡ�豸״̬

	void display_DeviceInfo() const override; //��ʾ�豸����


	void chan_in_temp();    //���⹤���¶�
	void chan_fr_temp();

	friend ostream& operator<< (ostream& out, const refeigerator& d);
	friend istream& operator>> (istream& in, refeigerator& d);

	void turn_Device() override;  //�ı乤��״̬ 

	const string type = "refeigerator";

private:
	double in_temp;   //�����¶� 4---8���϶�֮��
	double fr_temp;   //�䶳�¶� -18-10���϶�֮��



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

//ϴ�»�
class washer : public Device {
public:
	washer() = default;
	washer(Device device, string wa_mod, int water_mod);
	~washer() override { count--; }

	void display_DeviceInfo() const override; //��ʾ�豸�ĸ���״̬

	bool get_Device_status() const override;
	string get_name() const { return Device_name; }

	void turn_Device() override;  //�ı乤��״̬
	void turn_water_mod();       //����ϴ�»�ˮ��ģʽ

	friend ostream& operator<< (ostream& out, const washer& d);
	friend istream& operator>> (istream& in, washer& d);

	const string type = "washer";

private:
	string wa_mode;		//ϴ�»���ģʽ
	int water_mode;     //ˮ��ģʽ



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

//�յ�
class air : public Device {
public:
	air() = default;
	air(Device device, string mod, double temp);
	~air() override { count--; }

	void display_DeviceInfo() const override; //��ʾ�豸�ĸ���״̬


	void turn_Device() override;  //�ı乤��״̬

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





//�緹��
class rice_cooker : public Device {
public:
	rice_cooker() = default;
	rice_cooker(Device device, string mod);
	~rice_cooker() override { count--; }

	void display_DeviceInfo() const override; //��ʾ�豸�ĸ���״̬

	void turn_Device() override;  //�ı乤��״̬
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
	cout << "=============" << "��ʾ�豸��Ϣ" << "============" << endl;

	cout << "�豸��" << Device_name << endl;

	cout << "���ʣ�" << pow << endl;

	cout << "============== =================" << endl;
}





void Device::turn_Device() {
	Device_status = !Device_status;
}

//������
refeigerator::refeigerator(Device device, double in_ = 8, double fr_ = -10) : Device{ device }, in_temp{ in_ }, fr_temp{ fr_ } {

	count++;
}

bool refeigerator::get_Device_status() const
{
	return (Device_status == true);
}           //��ȡ�豸״̬

void refeigerator::display_DeviceInfo() const {    //��ʾ�豸�������
	cout << "=============" << "��ʾ�豸��Ϣ" << "============" << endl;
	cout << "�豸��" << Device_name << endl;
	cout << "���ʣ�" << pow << "w" << endl;
	cout << "����״̬��" << get_Device_status() << endl;
	if (Device_status == true) {
		cout << "�豸����" << endl;
		cout << "����ģʽ�¶ȣ�" << get_in_temp() << endl;
		cout << "�䶳ģʽ�¶ȣ�" << get_fr_temp() << endl;
		return;
	}
	else {
		cout << "�豸�ر�" << endl;
		return;
	}
	cout << "============== =================" << endl;
}



//��������ȷ����ʱ������޸�
void refeigerator::chan_in_temp() {    //���⹤���¶�
	while (get_Device_status()) {
		try {
			cout << "�����뱣��������ڵ��¶� �ڣ�4~8��֮�䣩:";
			double t;
			cin >> t;

			if (t < 4 || t > 8) {
				throw std::out_of_range("�¶ȳ�����Χ��������4~8֮����¶ȡ�");
			}

			in_temp = t;
			break;
		}
		catch (const std::exception& e) {
			std::cerr << "�쳣: " << e.what() << std::endl;

		}
	}
}
void refeigerator::chan_fr_temp() {
	while (get_Device_status()) {
		try {
			cout << "�������䶳������ڵ��¶� ��-18~-10��֮��:" << endl;
			double t;
			cin >> t;

			if (t < -18 || t > -10) {
				throw std::out_of_range("�¶ȳ�����Χ��������-18~-10֮����¶ȣ�");
			}

			in_temp = t;
			break;
		}
		catch (const std::exception& e) {
			std::cerr << "�쳣: " << e.what() << std::endl;

		}
	}
}



//�ı乤��״̬
void refeigerator::turn_Device() {
	int choice;

	while (get_Device_status()) {
		cout << "��ǰ�豸״̬��" << endl;
		display_DeviceInfo();
		cout << "������ʾ�޸ĵ�ǰ�豸״̬��" << endl;
		cout << "����1���޸��豸�ı����¶�" << endl;
		cout << "����2���޸��豸���䶳�¶�" << endl;
		cout << "����3������/�ر��豸" << endl;
		cout << "����0���˳��޸�" << endl;

		cin >> choice;

		switch (choice) {
		case 1:
			chan_in_temp();  // �����޸ı����¶ȵĺ���
			cout << "״̬�޸ĳɹ�����ǰ״̬��" << endl;
			this->pow = abs(fr_temp) + abs(in_temp) * 1;
			display_DeviceInfo();
			break;
		case 2:
			chan_fr_temp();  // �����޸��䶳�¶ȵĺ���
			cout << "״̬�޸ĳɹ�����ǰ״̬��" << endl;
			//���ʼ���
			this->pow = abs(fr_temp) + (in_temp) * 1;

			display_DeviceInfo();
			break;
		case 3:
			Device_status = !Device_status;
			cout << "״̬�޸ĳɹ�����ǰ״̬��" << endl;
			if (this->Device_status == 0)
				this->pow = 0;
			else
				this->pow = abs(fr_temp) + abs(in_temp) * 1;
			display_DeviceInfo();
			break;
		case 0:
			return;  // �˳�ѭ���ͺ���
		default:
			cout << "��Ч��ѡ�����������롣" << endl;
		}
	}
}




//ϴ�»���
washer::washer(Device device, string wa_mod = "һ��ģʽ", int water_mod = 1) : Device{ device }, wa_mode{ wa_mod }, water_mode{ water_mod } { count++; }

bool washer::get_Device_status() const
{
	if (Device_status == true) {
		cout << "�豸����" << endl;
		return true;
	}
	else {
		cout << "�豸�ر�" << endl;
		return false;
	}

}
void washer::display_DeviceInfo() const {//��ʾ�豸�ĸ������
	cout << "=============" << "��ʾ�豸��Ϣ" << "============" << endl;

	cout << "�豸��" << Device_name << endl;
	cout << "���ʣ�" << pow << "w" << endl;
	cout << "����״̬��" << get_Device_status() << endl;
	if (Device_status == true) {
		cout << "�豸����" << endl;
		return;
	}
	else {
		cout << "�豸�ر�" << endl;
		return;
	}
	cout << "============== =================" << endl;
}




void washer::turn_water_mod() {      //����ϴ�»�ˮ��ģʽ
	int choice;
	while (Device_status == true) {
		cout << " ��ǰˮ��ģʽΪ" << water_mode << endl;
		cout << "\n��ѡ����Ҫ���ڵ�ˮ��ģʽ��" << endl;
		cout << "����1������ˮ��ģʽΪ1������ˮ��ģʽ" << endl;
		cout << "����2������ˮ��ģʽΪ2���е�ˮ��ģʽ" << endl;
		cout << "����3������ˮ��ģʽΪ3������ˮ��ģʽ" << endl;
		cout << "����0���˳�ˮ��ģʽ" << endl;

		cin >> choice;

		switch (choice) {
		case(1):
			water_mode = 1;
			cout << "״̬�޸ĳɹ�" << endl;
			break;
		case(2):
			water_mode = 2;
			cout << "״̬�޸ĳɹ�" << endl;
			break;
		case(3):
			water_mode = 3;
			cout << "״̬�޸ĳɹ�" << endl;
			break;
		case(0):
			cout << "���˳�ˮ��ģʽ" << endl;
			return;
		default:
			cout << "��Ч��ѡ�����������롣" << endl;
		}
	}
}

void washer::turn_Device() {         //����ϴ�»�ģʽ
	int choice;

	while (get_Device_status()) {
		cout << "��ǰ�豸״̬��" << endl;
		display_DeviceInfo();
		cout << "\n������ʾ�޸ĵ�ǰ�豸״̬��" << endl;
		cout << "����1��ϴ��ģʽΪ��ϴģʽ" << endl;
		cout << "����2��ϴ��ģʽΪһ��ģʽ" << endl;
		cout << "����3������/�ر��豸" << endl;
		cout << "����0���˳��޸�" << endl;

		cin >> choice;

		switch (choice) {
		case 1:
			wa_mode = "��ϴģʽ";  // �����޸ı����¶ȵĺ���
			cout << "״̬�޸ĳɹ�����ǰ״̬��" << endl;
			this->pow = 30;
			display_DeviceInfo();
			break;
		case 2:
			wa_mode = "һ��ģʽ";  // �����޸��䶳�¶ȵĺ���
			cout << "״̬�޸ĳɹ�����ǰ״̬��" << endl;
			//���ʼ���
			this->pow = 20;

			display_DeviceInfo();
			break;
		case 3:
			Device_status = !Device_status;
			cout << "״̬�޸ĳɹ�����ǰ״̬��" << endl;
			if (this->Device_status == 0)
				this->pow = 0;
			else
				this->pow = 0;
			display_DeviceInfo();
			break;
		case 0:
			return;  // �˳�ѭ���ͺ���
		default:
			cout << "��Ч��ѡ�����������롣" << endl;
		}
	}
}


//�յ���
air::air(Device device, string mod = "����ģʽ", double temp = 30.0)
	: Device{ device }, air_mod{ mod }, air_temp{ temp }

{
	count++;
}

void air::display_DeviceInfo() const { //��ʾ�豸�ĸ���״̬
	cout << "=============" << "��ʾ�豸��Ϣ" << "============" << endl;

	cout << "�豸��" << Device_name << endl;
	cout << "���ʣ�" << pow << "w" << endl;
	cout << "����״̬��" << endl;
	if (Device_status == true) {
		cout << "�豸����" << endl;
		cout << "����ģʽ��" << endl;
		cout << air_mod << endl;
		cout << "�����¶ȣ�" << endl;
		cout << air_temp << endl;
		return;
	}
	else {
		cout << "�豸�ر�" << endl;
		return;
	}
	cout << "============== =================" << endl;
}



void air::turn_Device() { //�ı乤��״̬
	cout << "��ǰ�豸״̬��" << endl;
	display_DeviceInfo();
	int choice;
	while (Device_status == true) {
		cout << "\n������ʾ�޸ĵ�ǰ�豸״̬��" << endl;
		cout << "����1������Ϊ��ůģʽ" << endl;
		cout << "����2������Ϊ����ģʽ" << endl;
		cout << "����3�������¶�" << endl;
		cout << "����4������/�ر��豸" << endl;
		cout << "����0���˳��޸�" << endl;

		cin >> choice;

		switch (choice) {
		case 1:
			air_mod = "��ůģʽ";  // �����޸ı����¶ȵĺ���
			cout << "״̬�޸ĳɹ�����ǰ״̬��" << endl;
			this->pow = air_temp * 3;
			display_DeviceInfo();
			break;
		case 2:
			air_mod = "����ģʽ";  // �����޸��䶳�¶ȵĺ���
			cout << "״̬�޸ĳɹ�����ǰ״̬��" << endl;
			//���ʼ���
			this->pow = air_temp * 3;

			display_DeviceInfo();
			break;
		case 3:
			double t;
			cin >> t;
			air_temp = t;
			cout << "״̬�޸ĳɹ�����ǰ״̬��" << endl;
			this->pow = air_temp * 3;
			display_DeviceInfo();
			break;
		case 4:
			Device_status = !Device_status;
			cout << "״̬�޸ĳɹ�����ǰ״̬��" << endl;
			if (this->Device_status == 0)
				this->pow = 0;
			else
				this->pow = air_temp * 3;
			display_DeviceInfo();
			break;
		case 0:
			return;  // �˳�ѭ���ͺ���
		default:
			cout << "��Ч��ѡ�����������롣" << endl;
		}
	}
}

//double air::get_air_temp() {
//
//}
//string air::get_air_mod() {
//
//}

//�緹����
rice_cooker::rice_cooker(Device device, string mod = "��ģʽ") : Device{ device }, cooker_mod{ mod } { count++; }
void rice_cooker::display_DeviceInfo() const {  //��ʾ�豸�ĸ���״̬
	cout << "=============" << "��ʾ�豸��Ϣ" << "============" << endl;

	cout << "�豸��" << Device_name << endl;
	cout << "���ʣ�" << pow << "w" << endl;
	cout << "����״̬��" << endl;
	if (Device_status == true) {
		cout << "�豸����" << endl;
		cout << "����ģʽ��" << endl;
		cout << cooker_mod << endl;
		return;
	}
	else {
		cout << "�豸�ر�" << endl;
		return;
	}
	cout << "============== =================" << endl;

}


//�ı乤��״̬
void rice_cooker::turn_Device() {
	cout << "��ǰ�豸״̬��" << endl;
	display_DeviceInfo();
	int choice;
	while (Device_status == true) {
		cout << "\n������ʾ�޸ĵ�ǰ�豸״̬��" << endl;
		cout << "����1������Ϊ����ģʽ" << endl;
		cout << "����2������Ϊ�׷�ģʽ" << endl;
		cout << "����3������Ϊ����ģʽ" << endl;
		cout << "����4������/�ر��豸" << endl;
		cout << "����0���˳��޸�" << endl;

		cin >> choice;

		switch (choice) {
		case 1:
			cooker_mod = "����ģʽ";  // �����޸ı����¶ȵĺ���
			cout << "״̬�޸ĳɹ�����ǰ״̬��" << endl;
			this->pow = 20;
			display_DeviceInfo();
			break;
		case 2:
			cooker_mod = "�׷�ģʽ";  // �����޸��䶳�¶ȵĺ���
			cout << "״̬�޸ĳɹ�����ǰ״̬��" << endl;
			//���ʼ���
			this->pow = 10;

			display_DeviceInfo();
			break;
		case 3:
			double t;
			cin >> t;
			cooker_mod = "����ģʽ";
			cout << "״̬�޸ĳɹ�����ǰ״̬��" << endl;
			this->pow = 20;
			display_DeviceInfo();
			break;
		case 4:
			Device_status = !Device_status;
			cout << "״̬�޸ĳɹ�����ǰ״̬��" << endl;
			if (this->Device_status == 0)
				this->pow = 0;
			display_DeviceInfo();
			break;
		case 0:
			return;  // �˳�ѭ���ͺ���
		default:
			cout << "��Ч��ѡ�����������롣" << endl;
		}
	}
}


#endif
