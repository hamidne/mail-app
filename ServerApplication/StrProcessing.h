#include <iostream>
#include <winsock2.h>
#include <string>
#include <regex>

using namespace std;
class Server;

class StrProcessing
{
public:
	StrProcessing(SOCKET, TXT_File &);
	~StrProcessing();
	void inputprocessing(char[]);
	void findUser();
	void loginProcessing();
	void sendProcessing();
	void deleteProcessing();
	void loadInBox(int);
	void loadOutBox(int);
	void loadTrashBox(int);
	void loadMailIn(int);
	void loadMailOut(int);

private:
	Time timeClass;
	TXT_File file;
	SOCKET Client;
	char *recvBuff;
	string receivChar;
	int sizeAccount;
	int sizeSendMail;
	int sizeRecvMail;
	int ID_Account;
	string username;
	string password;
	char recipient[16];
	char subject[16];
	char context[512];

};

StrProcessing::StrProcessing(SOCKET Client, TXT_File &file)
{
	this->Client = Client;
	this->file = file;
}

StrProcessing::~StrProcessing()
{
}

void StrProcessing::inputprocessing(char recvBuff[])
{
	receivChar = recvBuff;

	if (receivChar.find("send#") != -1)
	{
		sendProcessing();
	}
	else if (receivChar.find("NICK") != -1) {
		findUser();
	}
	else if (receivChar.find("login#") != -1)
	{
		loginProcessing();
	}
	else if (receivChar.find("loadinbox#") != -1)
	{
		loadInBox(ID_Account);
	}
	else if (receivChar.find("loadoutbox#") != -1)
	{
		loadOutBox(ID_Account);
	}
	else if (receivChar.find("loadtrashbox#") != -1)
	{
		loadTrashBox(ID_Account);
	}
	else if (receivChar.find("del#") != -1)
	{
		char *sendStr = "Mail Tarsh deletetd ...";
		send(Client, sendStr, strlen(sendStr), 0);
	}
	else if (receivChar.find("delete#") != -1)
	{
		deleteProcessing();
	}
	else if (receivChar.find("getSizeReciveMail#") != -1)
	{
		int size = file.getSizeReciveMail();
		string temp = to_string(size);
		send(Client, temp.c_str(), temp.size(), 0);
	}
	else if (receivChar.find("getSizeSendMail#") != -1)
	{
		int size = file.getSizeSendMail();
		string temp = to_string(size);
		send(Client, temp.c_str(), temp.size(), 0);
	}
	else if (receivChar.find("getSizetrashMail#") != -1)
	{
		int size = file.getSizeTrashMail();
		string temp = to_string(size);
		send(Client, temp.c_str(), temp.size(), 0);
	}
	else
	{
		char *sendStr = "Your Massage Is Not...";
		send(Client, sendStr, strlen(sendStr), 0);
	}
}

void StrProcessing::findUser()
{
	// NICK username
	sizeAccount = file.getSizeAccount();

	string subject = recvBuff;
	string username = "";
	regex re("NICK (\w*)");
	smatch match;

	if (regex_search(subject, match, re) && match.size() > 1)
		username = match.str(1);

	bool existPass = false, existUser = false;

	int i;
	for (i = 0; i < sizeAccount && !existUser; i++)
	{
		if (username == username_pass[i].username)
		{
			existUser = true;
		}
	}

	if (existUser)
	{
		char *sendStr = "100";
		send(Client, sendStr, strlen(sendStr), 0);
		ID_Account = i - 1;
		file.Load_ReciveMail(ID_Account);
		file.Load_SendMail(ID_Account);
	}
	else
	{
		char *sendStr = "202";
		send(Client, sendStr, strlen(sendStr), 0);
	}
}

void StrProcessing::loginProcessing()
{
	sizeAccount = file.getSizeAccount();

	regex rgx("login#(.+)#(.+)");
	smatch matches;
	regex_search(receivChar, matches, rgx);

	username = matches[1].str();
	password = matches[2].str();

	bool existPass = false, existUser = false;

	for (int i = 0; i < sizeAccount; i++)
		if (username == username_pass[i].username)
			if (password == username_pass[i].password)
			{
				existUser = true;
				existPass = true;
				ID_Account = i - 1;
				break;
			}

	if (existUser && existPass)
	{
		char *sendStr = "1";
		send(Client, sendStr, strlen(sendStr), 0);
		file.Load_ReciveMail(ID_Account);
		file.Load_SendMail(ID_Account);
	}
	else
	{
		char *sendStr = "0";
		send(Client, sendStr, strlen(sendStr), 0);
	}
}

void StrProcessing::sendProcessing()
{
	Send_Mail mail_Struct;
	sizeAccount = file.getSizeAccount();

	memset(recipient, 0, 15);
	memset(subject, 0, 15);
	memset(context, 0, 511);


	sizeSendMail = file.getSizeSendMail();
	receivChar.erase(0, 5);
	receivChar.copy(recipient, receivChar.find('#'), 0);
	receivChar.erase(0, receivChar.find('#') + 1);
	receivChar.copy(subject, receivChar.find('#'), 0);
	receivChar.erase(0, receivChar.find('#') + 1);
	receivChar.copy(context, receivChar.find('#'), 0);

	bool existRecipient = false;

	int ID_Reciver;
	for (ID_Reciver = 0; ID_Reciver < sizeAccount && !existRecipient; ID_Reciver++)
	{
		if (recipient == username_pass[ID_Reciver].username)
		{
			existRecipient = true;
		}
	}

	if (existRecipient)
	{
		char *sendStr = "1";
		send(Client, sendStr, strlen(sendStr), 0);

		strcpy(mail_Struct.ExistMail, "1");
		strcpy(mail_Struct.ReadOrNo, "0");
		strcpy(mail_Struct.sender, username.c_str());
		strcpy(mail_Struct.recipient, recipient);
		strcpy(mail_Struct.subject, subject);
		strcpy(mail_Struct.date, timeClass.getDate().c_str());
		strcpy(mail_Struct.time, timeClass.getWatch().c_str());
		strcpy(mail_Struct.context, context);

		file.Save_SendMail(mail_Struct, ID_Account);
		file.Save_ReciveMail(mail_Struct, ID_Reciver - 1);
	}
	else
	{
		char *sendStr = "0";
		send(Client, sendStr, strlen(sendStr), 0);
	}
}

void StrProcessing::deleteProcessing()
{
	int ID_mail;
	ID_mail = (int)receivChar[7] - 48;
	string temp = mail_recv_box[ID_mail].Mail_ID;

	strcpy(mail_recv[stoi(temp)].ExistMail, "0");
	file.Save_AllReciveMail(ID_Account);

	char *sendStr = "1";
	send(Client, sendStr, strlen(sendStr), 0);
}

void StrProcessing::loadInBox(int ID_Account)
{
	file.Save_AllReciveMail(ID_Account);
	sizeRecvMail = file.getSizeReciveMail();

	int mailCount = receivChar[10] - 48;

	switch (receivChar[12] - 48)
	{
	case 1:
		send(Client, mail_recv_box[mailCount].sender, strlen(mail_recv_box[mailCount].sender), 0);
		break;
	case 2:
		send(Client, mail_recv_box[mailCount].subject, strlen(mail_recv_box[mailCount].subject), 0);
		break;
	case 3:
		send(Client, mail_recv_box[mailCount].context, strlen(mail_recv_box[mailCount].context), 0);
		break;
	case 4:
		send(Client, mail_recv_box[mailCount].date, strlen(mail_recv_box[mailCount].date), 0);
		break;
	case 5:
		send(Client, mail_recv_box[mailCount].time, strlen(mail_recv_box[mailCount].time), 0);
		break;
	case 6:
		send(Client, mail_recv_box[mailCount].ReadOrNo, strlen(mail_recv_box[mailCount].ReadOrNo), 0);
		break;
	default:
		break;
	}
}

void StrProcessing::loadOutBox(int ID_Account)
{
	file.Load_SendMail(ID_Account);
	sizeSendMail = file.getSizeSendMail();

	int mailCount = receivChar[11] - 48;

	switch (receivChar[13] - 48)
	{
	case 1:
		send(Client, mail_send_box[mailCount].recipient, strlen(mail_send_box[mailCount].recipient), 0);
		break;
	case 2:
		send(Client, mail_send_box[mailCount].subject, strlen(mail_send_box[mailCount].subject), 0);
		break;
	case 3:
		send(Client, mail_send_box[mailCount].context, strlen(mail_send_box[mailCount].context), 0);
		break;
	case 4:
		send(Client, mail_send_box[mailCount].date, strlen(mail_send_box[mailCount].date), 0);
		break;
	case 5:
		send(Client, mail_send_box[mailCount].time, strlen(mail_send_box[mailCount].time), 0);
		break;
	default:
		break;
	}
}

void StrProcessing::loadTrashBox(int ID_Account)
{
	file.Load_ReciveMail(ID_Account);
	sizeRecvMail = file.getSizeReciveMail();

	int mailCount = receivChar[13] - 48;

	switch (receivChar[15] - 48)
	{
	case 1:
		send(Client, mail_trash_box[mailCount].sender, strlen(mail_trash_box[mailCount].sender), 0);
		break;
	case 2:
		send(Client, mail_trash_box[mailCount].subject, strlen(mail_trash_box[mailCount].subject), 0);
		break;
	case 3:
		send(Client, mail_trash_box[mailCount].context, strlen(mail_trash_box[mailCount].context), 0);
		break;
	case 4:
		send(Client, mail_trash_box[mailCount].date, strlen(mail_trash_box[mailCount].date), 0);
		break;
	case 5:
		send(Client, mail_trash_box[mailCount].time, strlen(mail_trash_box[mailCount].time), 0);
		break;
	case 6:
		send(Client, mail_trash_box[mailCount].ReadOrNo, strlen(mail_trash_box[mailCount].ReadOrNo), 0);
		break;
	default:
		break;
	}
}