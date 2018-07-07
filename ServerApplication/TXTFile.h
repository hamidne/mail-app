#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct User_Pass
{
	int ID;
	string username;
	string password;
};

struct Send_Mail
{
	char Mail_ID[3];
	char ExistMail[2];
	char ReadOrNo[2];
	char sender[16];
	char recipient[16];
	char subject[28];
	char date[16];
	char time[16];
	char context[512];
};

User_Pass username_pass[50];
Send_Mail mail_send[50];
Send_Mail mail_recv[50];
Send_Mail mail_send_box[33];
Send_Mail mail_recv_box[33];
Send_Mail mail_trash_box[33];


class TXT_File
{
public:
	TXT_File();
	~TXT_File();
	void Load_Account();
	void Load_SendMail(int);
	void Load_ReciveMail(int);
	void Load_ReciveBox();
	void Load_TrashMail();
	void Save_Account();
	void Save_Send_Recv_Mail(Send_Mail &, int, int);
	void Save_SendMail(Send_Mail &, int);
	void Save_AllReciveMail(int);
	void Save_ReciveMail(Send_Mail &, int);
	void Save_TrashMail();
	int getSizeAccount();
	int getSizeSendMail();
	int getSizeReciveMail();
	int getSizeTrashMail();

private:
	int sizeAccount;
	int sizeSendMail;
	int sizeReciveMail;
	int sizeReciveBox;
	int sizeTrashBox;
	int ID_Account;

};

TXT_File::TXT_File()
{
}

TXT_File::~TXT_File()
{
}

void TXT_File::Load_Account(){
	fstream Account;
	Account.open("Accounts.txt", ios::in);
	if (Account)
	{
		int i = 0;
		while (!Account.eof())
		{
			Account >> username_pass[i].ID >> username_pass[i].username >> username_pass[i].password;
			i++;
		}
		sizeAccount = i;
	}
	Account.close();
}

void TXT_File::Load_SendMail(int ID_Account){
	fstream SendMail;
	SendMail.open(to_string(ID_Account) + "_SendMail.txt", ios::in);
	if (SendMail)
	{
		int i = 0;
		char ExistMail;
		char trash[100];
		while (!SendMail.eof())
		{
			SendMail >> ExistMail;

			if (ExistMail == '1')
			{
				SendMail >> mail_send_box[i].recipient;
				SendMail.ignore();
				SendMail.getline(mail_send_box[i].subject, 27, '#');
				SendMail >> mail_send_box[i].date >> mail_send_box[i].time;
				SendMail.ignore();
				SendMail.getline(mail_send_box[i].context, 511, '#');
				SendMail.ignore(2);

				i++;
			}
			else
			{
				SendMail >> trash;
				SendMail.ignore();
				SendMail.getline(trash, 27, '#');
				SendMail >> trash;
				SendMail >> trash >> trash;
				SendMail.ignore();
				SendMail.getline(trash, 511, '#');
				SendMail.ignore(2);
			}
		}
		sizeSendMail = i;
	}
	SendMail.close();
}

void TXT_File::Load_ReciveMail(int ID_Account){
	fstream ReciveMail;
	ReciveMail.open(to_string(ID_Account) + "_ReciveMail.txt", ios::in);
	if (ReciveMail)
	{
		int i = 0;
		while (!ReciveMail.eof())
		{
			ReciveMail >> mail_recv[i].ExistMail;
			ReciveMail >> mail_recv[i].ReadOrNo;
			ReciveMail >> mail_recv[i].sender;
			ReciveMail.ignore();
			ReciveMail.getline(mail_recv[i].subject, 27, '#');
			ReciveMail >> mail_recv[i].date >> mail_recv[i].time;
			ReciveMail.ignore();
			ReciveMail.getline(mail_recv[i].context, 511, '#');
			ReciveMail.ignore(2);

			i++;
		}
		sizeReciveMail = i;
	}
	ReciveMail.close();

	Load_ReciveBox();
	Load_TrashMail();
}

void TXT_File::Load_ReciveBox(){
	int mailCount = 0;
	char ExistMail;
	string temp;
	for (int i = 0; i < sizeReciveMail; i++)
	{
		ExistMail = mail_recv[i].ExistMail[0];
		if (ExistMail == '1')
		{
			temp = to_string(i);
			strcpy(mail_recv_box[mailCount].Mail_ID, temp.c_str());
			strcpy(mail_recv_box[mailCount].ReadOrNo, mail_recv[i].ReadOrNo);
			strcpy(mail_recv_box[mailCount].sender, mail_recv[i].sender);
			strcpy(mail_recv_box[mailCount].subject, mail_recv[i].subject);
			strcpy(mail_recv_box[mailCount].date, mail_recv[i].date);
			strcpy(mail_recv_box[mailCount].time, mail_recv[i].time);
			strcpy(mail_recv_box[mailCount].context, mail_recv[i].context);

			mailCount++;
		}
	}

	sizeReciveBox = mailCount;
}

void TXT_File::Load_TrashMail(){
	int mailCount = 0;
	char ExistMail;
	string temp;
	for (int i = 0; i < sizeReciveMail; i++)
	{
		ExistMail = mail_recv[i].ExistMail[0];
		if (ExistMail == '0')
		{
			temp = to_string(i);
			strcpy(mail_recv_box[mailCount].Mail_ID, temp.c_str());
			strcpy(mail_trash_box[mailCount].ReadOrNo, mail_recv[i].ReadOrNo);
			strcpy(mail_trash_box[mailCount].sender, mail_recv[i].sender);
			strcpy(mail_trash_box[mailCount].subject, mail_recv[i].subject);
			strcpy(mail_trash_box[mailCount].date, mail_recv[i].date);
			strcpy(mail_trash_box[mailCount].time, mail_recv[i].time);
			strcpy(mail_trash_box[mailCount].context, mail_recv[i].context);

			mailCount++;
		}
	}

	sizeTrashBox = mailCount;
}

//void TXT_File::Load_ReciveMail(int ID_Account){
//	fstream ReciveMail;
//	ReciveMail.open(to_string(ID_Account) + "_ReciveMail.txt", ios::in);
//	if (ReciveMail)
//	{
//		int i = 0;
//		char ExistMail;
//		char trash[100];
//		while (!ReciveMail.eof())
//		{
//			ReciveMail >> ExistMail;
//			if (ExistMail == '1')
//			{
//				ReciveMail >> mail_recv_box[i].ReadOrNo;
//				ReciveMail >> mail_recv_box[i].sender;
//				ReciveMail >> mail_recv_box[i].subject;
//				ReciveMail >> mail_recv_box[i].date >> mail_recv_box[i].time;
//				ReciveMail.ignore();
//				ReciveMail.getline(mail_recv_box[i].context, 511, '#');
//				ReciveMail.ignore(2);
//
//				i++;
//			}
//			else
//			{
//				ReciveMail >> trash >> trash;
//				ReciveMail >> trash;
//				ReciveMail >> trash;
//				ReciveMail >> trash >> trash;
//				ReciveMail.ignore();
//				ReciveMail.getline(trash, 511, '#');
//				ReciveMail.ignore(2);
//			}
//		}
//		sizeReciveMail = i;
//	}
//	ReciveMail.close();
//}

void TXT_File::Save_AllReciveMail(int ID_Account){
	fstream ReciveMail;
	ReciveMail.open(to_string(ID_Account) + "_ReciveMail.txt", ios::out);
	if (ReciveMail)
	{
		for (int i = 0; i < sizeReciveMail; i++)
		{
			if (i != 0)
				ReciveMail << endl << endl;

			ReciveMail << mail_recv[i].ExistMail << " " <<
				mail_recv[i].ReadOrNo << "\t" <<
				mail_recv[i].sender << "\t" <<
				mail_recv[i].subject << "#\t" <<
				mail_recv[i].date << "\t" <<
				mail_recv[i].time << "\n" <<
				mail_recv[i].context << "#";
		}
	}
	ReciveMail.close();
}


void TXT_File::Save_SendMail(Send_Mail &mail_send_box, int ID_Sender){
	fstream SendMail;

	SendMail.open(to_string(ID_Sender) + "_SendMail.txt", ios::out | ios::app);

	if (SendMail)
	{
		SendMail << endl << endl << mail_send_box.ExistMail << " " <<
			mail_send_box.recipient << "\t" <<
			mail_send_box.subject << "#\t" <<
			mail_send_box.date << "\t" <<
			mail_send_box.time << "\n" <<
			mail_send_box.context << "#";
	}
	SendMail.close();
}

void TXT_File::Save_ReciveMail(Send_Mail &mail_send_box, int ID_Riciver){
	fstream ReciveMail;
	ReciveMail.open(to_string(ID_Riciver) + "_ReciveMail.txt", ios::out | ios::app);

	if (ReciveMail)
	{
		ReciveMail << endl << endl << mail_send_box.ExistMail << " " <<
			mail_send_box.ReadOrNo << "\t" <<
			mail_send_box.sender << "\t" <<
			mail_send_box.subject << "#\t" <<
			mail_send_box.date << "\t" <<
			mail_send_box.time << "\n" <<
			mail_send_box.context << "#";
	}
	ReciveMail.close();
}

void TXT_File::Save_Send_Recv_Mail(Send_Mail &mailStruct, int ID_Sender, int ID_Riciver)
{
	fstream Sender;
	fstream Reciver;
	Sender.open(to_string(ID_Sender) + "_SendMail.txt", ios::out | ios::app);
	if (Sender)
	{
		Sender << endl << endl << mailStruct.ExistMail << "\t"
			<< mailStruct.recipient << "\t" << mailStruct.subject << "\t"
			<< mailStruct.date << "\t" << mailStruct.time << endl << mailStruct.context << "#";
	}

	Reciver.open(to_string(ID_Riciver) + "_ReciveMail.txt", ios::out | ios::app);
	if (Reciver)
	{
		Reciver << endl << endl << mailStruct.ExistMail << " "
			<< mailStruct.ReadOrNo << "\t" << mailStruct.subject << "\t"
			<< mailStruct.date << "\t" << mailStruct.time << endl
			<< mailStruct.context << "#";
	}

	Sender.close();
	Reciver.close();
}

int TXT_File::getSizeAccount()
{
	return sizeAccount;
}

int TXT_File::getSizeSendMail()
{
	return sizeSendMail;
}

int TXT_File::getSizeReciveMail()
{
	return sizeReciveBox;
}

int TXT_File::getSizeTrashMail()
{
	return sizeTrashBox;
}