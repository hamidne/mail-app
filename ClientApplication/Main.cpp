#include "stdafx.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_thread.h>
#include <SDL_mutex.h>
#include <string>
#include <time.h>
#include <string.h>
#include "Button.h"
#include "Client.h"
#include "font.h"

using namespace std;

Client creatClient(80);

SDL_Window *screen;
SDL_Renderer *renderer;
SDL_Rect r;

string usernametagTemp;

int arrLocation[13] = { -400, 165, 204, 242, 317, 356, 394, 431, 469, 507, 545, 583, 619 };
int locSelect = 1;
int sizeBoxes[3];

int MainMenu();
int LoginMenu();

int SendMenu()
{
	Button LoadBackground(renderer, "Send Menu/Load.png");
	LoadBackground.setButton();
	SDL_RenderPresent(renderer);

	Button Background(renderer, "Send Menu/Background.png");
	Button send(renderer, "Send Menu/Send.png", "Send Menu/Send1.png");
	Button Delete(renderer, "Send Menu/Delete.png", "Send Menu/Delete1.png");
	Button font(renderer, "Send Menu/Font.png", "Send Menu/Font1.png", "Send Menu/Font2.png");
	Button Icon(renderer, "Send Menu/Icon.png", "Send Menu/Icon1.png", "Send Menu/Icon2.png",
		"Send Menu/Icon3.png", "Send Menu/Icon4.png");
	Button Back(renderer, "Send Menu/Back.png", "Send Menu/Back1.png");
	Button FontBackgrount(renderer, "Send Menu/FontBackgrount.png", "Send Menu/FontBackgrount1.png");
	Button FontBackgrountD(renderer, "Send Menu/FontBackgrountD.png", "Send Menu/FontBackgrountD1.png");

	SDL_StartTextInput();

	string recipient;
	string subject;
	string context;

	Font font1(screen, renderer, "Font/Roboto-Light.ttf", 17);
	font1.setColor(100, 100, 100, 0);
	font1.setRectCoordinate(182, 107);

	Font font2(screen, renderer, "Font/Roboto-Light.ttf", 17);
	font2.setColor(100, 100, 100, 0);
	font2.setRectCoordinate(218, 144);

	Font font3(screen, renderer, "Font/Roboto-Light.ttf", 20);
	font3.setColor(100, 100, 100, 0);
	font3.setRectCoordinate(155, 212);

	bool inputRecipient = false;
	bool inputSubject = false;
	bool inputContext = false;

	SDL_Event ev;
	while (SDL_WaitEvent(&ev))
	{
		if (ev.type == SDL_QUIT){
			SDL_Quit();
		}

		else if (ev.type == SDL_MOUSEBUTTONDOWN)
		{
			if (ev.button.x > 811 && ev.button.x < 838 && ev.button.y > 81 && ev.button.y < 107)					//Back Button
				return 0;

			else if (ev.button.x > 841 && ev.button.x < 862 && ev.button.y > 618 && ev.button.y < 644)				//Delete Button
			{
				recipient = "";
				subject = "";
				context = "";

				LoadBackground.setButton();
				SDL_RenderPresent(renderer);
			}

			else if (ev.button.x > 800 && ev.button.x < 850 && ev.button.y > 156 && ev.button.y < 205)				//Send Button
			{
				string sendStr;
				sendStr = "send#" + recipient + "#" + subject + "#" + context;
				creatClient.sendMessage(sendStr.c_str());

				if (creatClient.buffer[0] == '0')
				{
					return 0;
				}
				else if (creatClient.buffer[0] == '1')
				{
					return 0;
				}
			}

			else if (ev.button.x > 176 && ev.button.x < 500 && ev.button.y > 103 && ev.button.y < 133)				//Input Recipient
			{
				inputRecipient = true;
				inputSubject = false;
				inputContext = false;

				font.setButton1();

				FontBackgrount.setButton();
				font1.setCharTextShaded(recipient.c_str(), 214, 214, 214);

				FontBackgrountD.setButton1();
				font2.setCharText(subject.c_str());

				SDL_RenderPresent(renderer);
			}

			else if (ev.button.x > 217 && ev.button.x < 500 && ev.button.y > 142 && ev.button.y < 170)				//Input Subject
			{
				inputRecipient = false;
				inputSubject = true;
				inputContext = false;

				font.setButton2();

				FontBackgrount.setButton1();
				font2.setCharTextShaded(subject.c_str(), 214, 214, 214);

				FontBackgrountD.setButton();
				font1.setCharText(recipient.c_str());

				SDL_RenderPresent(renderer);
			}

			else if (ev.button.x > 145 && ev.button.x < 864 && ev.button.y > 215 && ev.button.y < 587)				//Input Context
			{
				inputRecipient = false;
				inputSubject = false;
				inputContext = true;

				font.setButton();

				FontBackgrountD.setButton1();
				font2.setCharText(subject.c_str());

				FontBackgrountD.setButton();
				font1.setCharText(recipient.c_str());

				SDL_RenderPresent(renderer);
			}
			else
			{
				font.setButton();

				FontBackgrountD.setButton();
				font1.setCharText(recipient.c_str());

				FontBackgrountD.setButton1();
				font2.setCharText(subject.c_str());

				SDL_RenderPresent(renderer);
			}

		}

		else if (ev.type == SDL_TEXTINPUT || ev.type == SDL_KEYDOWN)											//SDL TEXT INPUT
		{
			system("cls");

			if (inputRecipient)
			{
				if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_BACKSPACE && recipient.length() > 0)
				{
					recipient = recipient.substr(0, recipient.length() - 1);
					FontBackgrount.setButton();
					SDL_RenderPresent(renderer);
				}

				else if (ev.type == SDL_TEXTINPUT)
					recipient += ev.text.text;

				font1.setCharTextShaded(recipient.c_str(), 214, 214, 214);

				SDL_RenderPresent(renderer);
			}

			else if (inputSubject)
			{
				if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_BACKSPACE && subject.length() > 0)
				{
					subject = subject.substr(0, subject.length() - 1);
					FontBackgrount.setButton1();
					SDL_RenderPresent(renderer);
				}

				else if (ev.type == SDL_TEXTINPUT)
					subject += ev.text.text;

				font2.setCharTextShaded(subject.c_str(), 214, 214, 214);

				SDL_RenderPresent(renderer);
			}

			else if (inputContext)
			{
				if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_BACKSPACE && context.length() > 0)
					context = context.substr(0, context.length() - 1);

				else if (ev.type == SDL_TEXTINPUT)
					context += ev.text.text;

				else if (ev.type == SDL_KEYDOWN && (ev.key.keysym.sym == SDLK_RETURN ||
					ev.key.keysym.sym == SDLK_RETURN2) && context.length() > 0)
					context = context.append("\n");

				SDL_SetRenderDrawColor(renderer, 235, 235, 235, 0);
				r.h = 300;	r.w = 710;	r.x = 148;	r.y = 215;
				SDL_RenderFillRect(renderer, &r);
				SDL_RenderPresent(renderer);

				font3.setCharTextWrapped(context.c_str(), 680);

				SDL_RenderPresent(renderer);
			}
		}

		if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_TAB)
		{
			if (inputRecipient)
			{
				inputRecipient = false;
				inputSubject = true;

				font.setButton2();
				FontBackgrount.setButton1();
				font2.setCharTextShaded(subject.c_str(), 214, 214, 214);

				FontBackgrountD.setButton();
				font1.setCharText(recipient.c_str());

				SDL_RenderPresent(renderer);
			}

			else if (inputSubject)
			{
				inputRecipient = true;
				inputSubject = false;

				font.setButton1();
				FontBackgrount.setButton();
				font1.setCharTextShaded(recipient.c_str(), 214, 214, 214);

				FontBackgrountD.setButton1();
				font2.setCharText(subject.c_str());

				SDL_RenderPresent(renderer);
			}
		}

		else if (ev.type == SDL_MOUSEMOTION)
		{
			if (ev.button.x > 800 && ev.button.x < 850 && ev.button.y > 156 && ev.button.y < 205)
			{
				send.setButton1();
				SDL_RenderPresent(renderer);
			}
			else if (ev.button.x > 841 && ev.button.x < 862 && ev.button.y > 618 && ev.button.y < 644)
			{
				Delete.setButton1();
				SDL_RenderPresent(renderer);
			}

			else if (ev.button.x > 132 && ev.button.x < 158 && ev.button.y > 617 && ev.button.y < 641)
			{
				Icon.setButton1();
				SDL_RenderPresent(renderer);
			}
			else if (ev.button.x > 185 && ev.button.x < 212 && ev.button.y > 619 && ev.button.y < 637)
			{
				Icon.setButton2();
				SDL_RenderPresent(renderer);
			}
			else if (ev.button.x > 227 && ev.button.x < 256 && ev.button.y > 619 && ev.button.y < 637)
			{
				Icon.setButton3();
				SDL_RenderPresent(renderer);
			}
			else if (ev.button.x > 273 && ev.button.x < 298 && ev.button.y > 616 && ev.button.y < 639)
			{
				Icon.setButton4();
				SDL_RenderPresent(renderer);
			}

			else if (ev.button.x > 811 && ev.button.x < 838 && ev.button.y > 81 && ev.button.y < 107)
			{
				Back.setButton1();
				SDL_RenderPresent(renderer);
			}

			else
			{
				send.setButton();
				Delete.setButton();
				Icon.setButton();
				Back.setButton();

				SDL_RenderPresent(renderer);
			}
		}
	}
	return 0;
}

void SelectFunction(Button &SlideBar, Button &Select, Button &SlideBarFonts, int y, bool &slider, bool &slideSelect)
{
	SlideBar.setButton1();
	Select.setPosition(20, y - 3);
	Select.setButton();
	SlideBarFonts.setButton();

	SDL_RenderPresent(renderer);

	slider = false;
	slideSelect = true;
}

void MotionSelectFunction(Button &SlideBar, Button &MotionSelect, Button &SlideBarFonts, Button &Select, int y)
{
	SlideBar.setButton1();
	MotionSelect.setPosition(25, y);
	MotionSelect.setButton();
	Select.setPosition(20, arrLocation[locSelect] - 3);
	Select.setButton1();
	SlideBarFonts.setButton();

	SDL_RenderPresent(renderer);
}

int ExitButton()
{
	Button Exit(renderer, "Main Menu/Button/Exit.png", "Main Menu/Button/Exit1.png", "Main Menu/Button/Exit2.png", "Main Menu/Button/Exit3.png", "Main Menu/Button/Exit4.png");
	Exit.setButton();
	SDL_RenderPresent(renderer);

	SDL_Event ev;

	while (SDL_WaitEvent(&ev))
	{
		if (ev.type == SDL_QUIT){
			SDL_Quit();
		}

		else if (ev.type == SDL_MOUSEBUTTONDOWN)
		{
			if (ev.button.x > 319 && ev.button.x < 421 && ev.button.y > 379 && ev.button.y < 416)				//NO
			{
				MainMenu();
			}

			else if (ev.button.x > 449 && ev.button.x < 579 && ev.button.y > 379 && ev.button.y < 416)			//Sign Out
			{
				LoginMenu();
			}

			else if (ev.button.x > 579 && ev.button.x < 681 && ev.button.y > 379 && ev.button.y < 416)			//Yes
				SDL_Quit();

		}

		else if (ev.type == SDL_MOUSEMOTION)
		{
			if (ev.button.x > 319 && ev.button.x < 421 && ev.button.y > 379 && ev.button.y < 416)				//NO
			{
				Exit.setButton1();
				SDL_RenderPresent(renderer);
			}

			else if (ev.button.x > 449 && ev.button.x < 579 && ev.button.y > 379 && ev.button.y < 416)			//Sign Out
			{
				Exit.setButton2();
				SDL_RenderPresent(renderer);
			}

			else if (ev.button.x > 579 && ev.button.x < 681 && ev.button.y > 379 && ev.button.y < 416)			//Yes
			{
				Exit.setButton3();
				SDL_RenderPresent(renderer);
			}

			else
			{
				Exit.setButton4();
				SDL_RenderPresent(renderer);
			}
		}
	}

	return 0;
}

void LoadAllMail(int slideID)
{
	Button Avatar1(renderer, "Avatar/1.png", "Avatar/2.png", "Avatar/3.png", "Avatar/4.png", "Avatar/5.png", 47, 47);
	Button Avatar2(renderer, "Avatar/6.png", "Avatar/7.png", "Avatar/8.png", "Avatar/9.png", "Avatar/10.png", 47, 47);
	Button Read(renderer, "Main Menu/Button/Read.png", "Main Menu/Button/Read1.png", 33, 33);

	srand(time(0));

	//>>>>>>>>>>>>>>>>>>>>>>>>>>> Load Font <<<<<<<<<<<<<<<<<<<<<<<

	Font F_Username(screen, renderer, "Font/Roboto-Medium.ttf", 15);
	F_Username.setColor(60, 60, 60, 0);

	Font F_Mail(screen, renderer, "Font/Roboto-Regular.ttf", 13);
	F_Mail.setColor(150, 150, 150, 0);

	Font F_Subject(screen, renderer, "Font/Roboto-Medium.ttf", 15);
	F_Subject.setColor(60, 60, 60, 0);

	Font F_Context(screen, renderer, "Font/Roboto-Regular.ttf", 15);
	F_Context.setColor(150, 150, 150, 0);

	Font F_Date(screen, renderer, "Font/Roboto-Regular.ttf", 15);
	F_Date.setColor(60, 60, 60, 0);

	Font F_Avatar(screen, renderer, "Font/Roboto-Regular.ttf", 20);
	F_Avatar.setColor(255, 255, 255, 0);

	Font F_Button(screen, renderer, "Font/Roboto-Medium.ttf", 60);
	F_Button.setColor(0, 0, 0, 0);

	//>>>>>>>>>>>>>>>>>>>>>>>>>> Recv Mail <<<<<<<<<<<<<<<<<<<<<<<

	string sendStr;
	char mailAd[3];
	int size, randAvatar;
	memset(mailAd, 0, 3);

	string sendID[3] = { "loadinbox#", "loadoutbox#", "loadtrashbox#" };

	switch (slideID)
	{
	case 0:
		creatClient.sendMessage("getSizeReciveMail#");
		sendStr = creatClient.buffer;
		size = stoi(sendStr);
		sizeBoxes[0] = size;
		break;
	case 1:
		creatClient.sendMessage("getSizeSendMail#");
		sendStr = creatClient.buffer;
		size = stoi(sendStr);
		sizeBoxes[1] = size;
		break;
	case 2:
		creatClient.sendMessage("getSizetrashMail#");
		sendStr = creatClient.buffer;
		size = stoi(sendStr);
		sizeBoxes[2] = size;
		break;
	default:
		break;
	}


	for (int i = size - 1; i >= 0 && i > size - 7; i--)
	{
		Avatar1.setPosition(100, 195 + ((size - i - 1) * 70));
		Avatar2.setPosition(100, 195 + ((size - i - 1) * 70));

		randAvatar = rand() % 10;
		switch (randAvatar)
		{
		case 0:
			Avatar1.setButton();
			break;
		case 1:
			Avatar1.setButton1();
			break;
		case 2:
			Avatar1.setButton2();
			break;
		case 3:
			Avatar1.setButton3();
			break;
		case 4:
			Avatar1.setButton4();
			break;
		case 5:
			Avatar2.setButton();
			break;
		case 6:
			Avatar2.setButton1();
			break;
		case 7:
			Avatar2.setButton2();
			break;
		case 8:
			Avatar2.setButton3();
			break;
		case 9:
			Avatar2.setButton4();
			break;
		default:
			break;
		}

		sendStr = sendID[slideID] + to_string(i) + "#1";											//Username
		creatClient.sendMessage(sendStr.c_str());
		F_Username.setRectCoordinate(165, 200 + ((size - i - 1) * 70));
		F_Username.setCharText(creatClient.buffer);

		F_Avatar.setRectCoordinate(117, 205 + ((size - i - 1) * 70));								//Avatar Name
		sendStr = creatClient.buffer;
		mailAd[0] = sendStr[0] - 32;
		F_Avatar.setCharText(mailAd);


		F_Mail.setRectCoordinate(165, 220 + ((size - i - 1) * 70));									//Mail Adress
		sendStr = creatClient.buffer;
		sendStr += "@gmail.com";
		F_Mail.setCharText(sendStr.c_str());


		sendStr = sendID[slideID] + to_string(i) + "#2";											//Subject
		creatClient.sendMessage(sendStr.c_str());
		F_Subject.setRectCoordinate(350, 210 + ((size - i - 1) * 70));
		F_Subject.setCharText(creatClient.buffer);


		sendStr = sendID[slideID] + to_string(i) + "#3";											//Context
		creatClient.sendMessage(sendStr.c_str());
		F_Context.setRectCoordinate(460, 210 + ((size - i - 1) * 70));

		if (creatClient.buffer[45] != '\0')
		{
			creatClient.buffer[45] = ' ';
			creatClient.buffer[46] = '.';
			creatClient.buffer[47] = '.';
			creatClient.buffer[48] = '.';
			creatClient.buffer[49] = '.';
			creatClient.buffer[49] = '\0';
		}
		F_Context.setCharText(creatClient.buffer);


		sendStr = sendID[slideID] + to_string(i) + "#4";											//Date
		creatClient.sendMessage(sendStr.c_str());
		F_Date.setRectCoordinate(830, 210 + ((size - i - 1) * 70));
		F_Date.setCharText(creatClient.buffer);

		/*if (slideID == 0)
		{
		sendStr = sendID[slideID] + to_string(i) + "#5";
		creatClient.sendMessage(sendStr.c_str());
		Read.setPosition(40, 210 + ((size - i - 1) * 70));

		if (creatClient.buffer[0] == 48)
		Read.setButton();
		else
		Read.setButton1();
		}*/

		SDL_SetRenderDrawColor(renderer, 200, 200, 200, 0);
		SDL_RenderDrawLine(renderer, 150, 255 + (((size - i - 1)) * 70), 900, 255 + (((size - i - 1)) * 70));
	}

	SDL_RenderPresent(renderer);
}

void LoadMail(int slideID, int mail_ID)
{
	Button LoadBackground(renderer, "Show Email/Load.png");
	LoadBackground.setButton();
	SDL_RenderPresent(renderer);

	Button Avatar1(renderer, "Avatar/1.png", "Avatar/2.png", "Avatar/3.png", "Avatar/4.png", "Avatar/5.png", 47, 47);
	Button Avatar2(renderer, "Avatar/6.png", "Avatar/7.png", "Avatar/8.png", "Avatar/9.png", "Avatar/10.png", 47, 47);

	srand(time(0));

	Font Subject1(screen, renderer, "Font/Roboto-Light.ttf", 16);
	Subject1.setColor(130, 130, 130, 0);
	Subject1.setRectCoordinate(115, 173);
	Subject1.setCharText("Subject :");

	Font Subject2(screen, renderer, "Font/Roboto-Light.ttf", 21);
	Subject2.setColor(50, 50, 50, 0);
	Subject2.setRectCoordinate(185, 170);

	Font Username1(screen, renderer, "Font/Roboto-Light.ttf", 25);
	Username1.setColor(50, 50, 50, 0);
	Username1.setRectCoordinate(160, 115);

	Font Username2(screen, renderer, "Font/Roboto-Light.ttf", 15);
	Username2.setColor(100, 100, 100, 0);
	Username2.setRectCoordinate(245, 120);

	Font time(screen, renderer, "Font/Roboto-Light.ttf", 17);
	time.setColor(100, 100, 100, 0);
	time.setRectCoordinate(839, 175);

	Font Context(screen, renderer, "Font/Roboto-Light.ttf", 18);
	Context.setColor(100, 100, 100, 0);
	Context.setRectCoordinate(111, 243);

	Font F_Avatar(screen, renderer, "Font/Roboto-Regular.ttf", 20);
	F_Avatar.setColor(255, 255, 255, 0);

	Avatar1.setPosition(100, 108);
	Avatar2.setPosition(100, 108);

	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	string sendStr;
	char mailAd[3];
	int randAvatar;
	memset(mailAd, 0, 3);

	string sendID[3] = { "loadinbox#", "loadoutbox#", "loadtrashbox#" };

	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	randAvatar = rand() % 10;
	switch (randAvatar)
	{
	case 0:
		Avatar1.setButton();
		break;
	case 1:
		Avatar1.setButton1();
		break;
	case 2:
		Avatar1.setButton2();
		break;
	case 3:
		Avatar1.setButton3();
		break;
	case 4:
		Avatar1.setButton4();
		break;
	case 5:
		Avatar2.setButton();
		break;
	case 6:
		Avatar2.setButton1();
		break;
	case 7:
		Avatar2.setButton2();
		break;
	case 8:
		Avatar2.setButton3();
		break;
	case 9:
		Avatar2.setButton4();
		break;
	default:
		break;
	}

	sendStr = sendID[slideID] + to_string(mail_ID) + "#1";											//Username
	creatClient.sendMessage(sendStr.c_str());
	Username1.setCharText(creatClient.buffer);

	F_Avatar.setRectCoordinate(117, 117);															//Avatar Name
	sendStr = creatClient.buffer;
	mailAd[0] = sendStr[0] - 32;
	F_Avatar.setCharText(mailAd);


	sendStr = creatClient.buffer;																	//Mail Adress
	sendStr = "<" + sendStr + "@gmail.com>";
	Username2.setCharText(sendStr.c_str());


	sendStr = sendID[slideID] + to_string(mail_ID) + "#2";											//Subject
	creatClient.sendMessage(sendStr.c_str());
	Subject2.setCharText(creatClient.buffer);


	sendStr = sendID[slideID] + to_string(mail_ID) + "#3";											//Context
	creatClient.sendMessage(sendStr.c_str());
	Context.setCharText(creatClient.buffer);


	sendStr = sendID[slideID] + to_string(mail_ID) + "#5";											//Date
	creatClient.sendMessage(sendStr.c_str());
	time.setCharText(creatClient.buffer);

	SDL_RenderPresent(renderer);

	Button Back(renderer, "Show Email/Back.png", "Show Email/Back1.png");
	Button Icon(renderer, "Show Email/Icon.png", "Show Email/Icon1.png", "Show Email/Icon2.png", "Show Email/Icon3.png", "Show Email/Icon4.png", "Show Email/Icon5.png");

	SDL_Event ev;
	while (SDL_WaitEvent(&ev))
	{
		if (ev.type == SDL_QUIT){
			SDL_Quit();
		}

		else if (ev.type == SDL_MOUSEBUTTONDOWN)
		{
			if (ev.button.x > 33 && ev.button.x < 63 && ev.button.y > 52 && ev.button.y < 81)					//Back Button
			{
				break;
			}
			else if (ev.button.x > 770 && ev.button.x < 793 && ev.button.y > 111 && ev.button.y < 139)				//Delete Icon
			{
				sendStr = "delete#" + to_string(mail_ID);
				creatClient.sendMessage(sendStr.c_str());
				break;
			}
		}

		else if (ev.type == SDL_MOUSEMOTION)
		{
			if (ev.button.x > 33 && ev.button.x < 60 && ev.button.y > 54 && ev.button.y < 81)					//Back Button
			{
				Back.setButton1();
			}

			else if (ev.button.x > 651 && ev.button.x < 680 && ev.button.y > 113 && ev.button.y < 138)				//Icon1
			{
				Icon.setButton1();
			}

			else if (ev.button.x > 711 && ev.button.x < 739 && ev.button.y > 109 && ev.button.y < 139)				//Icon2
			{
				Icon.setButton2();
			}

			else if (ev.button.x > 770 && ev.button.x < 793 && ev.button.y > 111 && ev.button.y < 139)				//Icon3
			{
				Icon.setButton3();
			}

			else if (ev.button.x > 826 && ev.button.x < 855 && ev.button.y > 113 && ev.button.y < 137)				//Icon4
			{
				Icon.setButton4();
			}

			else if (ev.button.x > 892 && ev.button.x < 902 && ev.button.y > 112 && ev.button.y < 137)				//Icon5
			{
				Icon.setButton5();
			}

			else
			{
				Icon.setButton();
				Back.setButton();
			}

			SDL_RenderPresent(renderer);
		}
	}
}

int MainMenu()
{
	Button LoadBackground(renderer, "Main Menu/Button/Load.png");
	LoadBackground.setButton();

	Font slideTag(screen, renderer, "Font/Roboto-Light.ttf", 30);
	slideTag.setColor(235, 235, 235, 0);
	slideTag.setRectCoordinate(160, 70);
	slideTag.setCharText("| Inbox");

	Font UsernameTag(screen, renderer, "Font/Roboto-Regular.ttf", 17);
	UsernameTag.setColor(235, 235, 235, 0);
	UsernameTag.setRectCoordinate(54, 111);

	Font EmailAddTag(screen, renderer, "Font/Roboto-Regular.ttf", 12);
	EmailAddTag.setColor(235, 235, 235, 0);
	EmailAddTag.setRectCoordinate(54, 130);

	SDL_RenderPresent(renderer);

	LoadAllMail(0);

	Button Background(renderer, "Main Menu/Button/Background.png");
	Button Send(renderer, "Main Menu/Button/Send.png", "Main Menu/Button/Send1.png");
	Button Search(renderer, "Main Menu/Button/Search.png", "Main Menu/Button/Search1.png");
	Button Logo(renderer, "Main Menu/Button/Logo.png");
	Button Slide_Tag_B(renderer, "Main Menu/Button/Slide Tag-B.png");
	Button Slide(renderer, "Main Menu/Button/Slide.png", "Main Menu/Button/Slide1.png");
	Button Icon(renderer, "Main Menu/Button/Icon.png", "Main Menu/Button/Icon1.png", "Main Menu/Button/Icon2.png");
	Button SlideBar(renderer, "Main Menu/Button/Slide Bar.png", "Main Menu/Button/Slide Bar1.png");
	Button SlideBarFonts(renderer, "Main Menu/Button/Font Slide.png");
	Button Select(renderer, "Main Menu/Button/Select.png", "Main Menu/Button/Select1.png", 47, 260);
	Button MotionSelect(renderer, "Main Menu/Button/Motion Select.png", 37, 250);
	Button Back(renderer, "Main Menu/Button/Back1.png", "Main Menu/Button/Back.png");
	Button Motion(renderer, "Main Menu/Button/Motion.png", 24, 9);

	bool slideActive = false;
	bool slideSelect = false;
	bool backMotion = false;
	bool SearchSelect = false;
	string usernameTemp;

	string SlideTagStr[12] = { "|  Inbox    ", "|  Outbox   ", "|  Trash    ",
		"|  Starred  ", "|   Important", "|  Sent     ", "|  Outbox   ",
		"|  Draft    ", "|  All mail  ", "|  Spam     ", "|  Trash    ",
		"|  Help     " };

	SDL_Event ev;

	while (SDL_WaitEvent(&ev)) {

		if (ev.type == SDL_QUIT){
			SDL_Quit();
		}

		else if (ev.type == SDL_MOUSEBUTTONDOWN)
		{
			if (ev.button.x > 60 && ev.button.x < 87 && ev.button.y > 79 && ev.button.y < 100 && !slideActive)				//Slide Bar
			{
				SDL_Delay(100);
				SlideBar.setButton();
				Select.setPosition(20, arrLocation[locSelect] - 3);
				Select.setButton();
				SlideBarFonts.setButton();

				usernameTemp = usernametagTemp + "@gmail.com";
				EmailAddTag.setCharText(usernameTemp.c_str());

				usernametagTemp[0] -= 32;
				UsernameTag.setCharText(usernametagTemp.c_str());
				usernametagTemp[0] += 32;

				slideActive = true;

				SDL_RenderPresent(renderer);
			}

			else if (ev.button.x > 669 && ev.button.x < 866 && ev.button.y > 45 && ev.button.y < 80)						//Search Button
			{
				if (SearchSelect)
				{
					Search.setButton();
					SearchSelect = false;
				}
				else
				{
					Search.setButton1();
					SearchSelect = true;
				}


				SDL_RenderPresent(renderer);
			}

			else if (ev.button.x > 925 && ev.button.x < 949 && ev.button.y > 48 && ev.button.y < 75)						//Exit
			{
				Icon.setButton();

				ExitButton();
			}

			else if (ev.button.x > 877 && ev.button.x < 926 && ev.button.y > 132 && ev.button.y < 181)						//Send Button
			{
				SendMenu();

				LoadBackground.setButton();
				slideTag.setCharTextShaded(SlideTagStr[locSelect - 1].c_str(), 54, 55, 60);
				SDL_RenderPresent(renderer);

				LoadAllMail(locSelect - 1);
			}

			else if (ev.button.x > 70 && ev.button.x < 940 && !slideActive)
			{
				if (ev.button.y > 185 && ev.button.y < 255 && sizeBoxes[locSelect - 1] >= 1)								//Email 1
				{
					LoadMail(locSelect - 1, sizeBoxes[locSelect - 1] - 1);

					LoadBackground.setButton();
					slideTag.setCharTextShaded(SlideTagStr[locSelect - 1].c_str(), 54, 55, 60);
					SDL_RenderPresent(renderer);

					LoadAllMail(locSelect - 1);
				}
				else if (ev.button.y > 255 && ev.button.y < 325 && sizeBoxes[locSelect - 1] >= 2)							//Email 2
				{
					LoadMail(locSelect - 1, sizeBoxes[locSelect - 1] - 2);

					LoadBackground.setButton();
					slideTag.setCharTextShaded(SlideTagStr[locSelect - 1].c_str(), 54, 55, 60);
					SDL_RenderPresent(renderer);

					LoadAllMail(locSelect - 1);
				}
				else if (ev.button.y > 325 && ev.button.y < 395 && sizeBoxes[locSelect - 1] >= 3)							//Email 3
				{
					LoadMail(locSelect - 1, sizeBoxes[locSelect - 1] - 3);

					LoadBackground.setButton();
					slideTag.setCharTextShaded(SlideTagStr[locSelect - 1].c_str(), 54, 55, 60);
					SDL_RenderPresent(renderer);

					LoadAllMail(locSelect - 1);
				}
				else if (ev.button.y > 395 && ev.button.y < 465 && sizeBoxes[locSelect - 1] >= 4)							//Email 4
				{
					LoadMail(locSelect - 1, sizeBoxes[locSelect - 1] - 4);

					LoadBackground.setButton();
					slideTag.setCharTextShaded(SlideTagStr[locSelect - 1].c_str(), 54, 55, 60);
					SDL_RenderPresent(renderer);

					LoadAllMail(locSelect - 1);
				}
				else if (ev.button.y > 465 && ev.button.y < 535 && sizeBoxes[locSelect - 1] >= 5)							//Email 5
				{
					LoadMail(locSelect - 1, sizeBoxes[locSelect - 1] - 5);

					LoadBackground.setButton();
					slideTag.setCharTextShaded(SlideTagStr[locSelect - 1].c_str(), 54, 55, 60);
					SDL_RenderPresent(renderer);

					LoadAllMail(locSelect - 1);
				}
				else if (ev.button.y > 535 && ev.button.y < 605 && sizeBoxes[locSelect - 1] >= 6)							//Email 5
				{
					LoadMail(locSelect - 1, sizeBoxes[locSelect - 1] - 6);

					LoadBackground.setButton();
					slideTag.setCharTextShaded(SlideTagStr[locSelect - 1].c_str(), 54, 55, 60);
					SDL_RenderPresent(renderer);

					LoadAllMail(locSelect - 1);
				}
			}

			else if (ev.button.x > 227 && ev.button.x < 259 && ev.button.y > 52 && ev.button.y < 78 && slideActive)			//Slide Back
			{
				LoadBackground.setButton();
				LoadAllMail(locSelect - 1);
				slideTag.setCharTextShaded(SlideTagStr[locSelect - 1].c_str(), 54, 55, 60);

				slideActive = false;
				SDL_RenderPresent(renderer);
			}

			else if (ev.button.x > 25 && ev.button.x < 275 && slideActive)													//Select
			{
				if (ev.button.y > 165 && ev.button.y < 202)
				{
					SelectFunction(SlideBar, Select, SlideBarFonts, 165, slideActive, slideSelect);
					locSelect = 1;
				}

				else if (ev.button.y > 204 && ev.button.y < 241)
				{
					SelectFunction(SlideBar, Select, SlideBarFonts, 204, slideActive, slideSelect);
					locSelect = 2;
				}

				else if (ev.button.y > 242 && ev.button.y < 279)
				{
					SelectFunction(SlideBar, Select, SlideBarFonts, 242, slideActive, slideSelect);
					locSelect = 3;
				}

				else if (ev.button.y > 317 && ev.button.y < 354)
				{
					SelectFunction(SlideBar, Select, SlideBarFonts, 317, slideActive, slideSelect);
					locSelect = 4;
				}

				else if (ev.button.y > 356 && ev.button.y < 393)
				{
					SelectFunction(SlideBar, Select, SlideBarFonts, 356, slideActive, slideSelect);
					locSelect = 5;
				}

				else if (ev.button.y > 394 && ev.button.y < 431)
				{
					SelectFunction(SlideBar, Select, SlideBarFonts, 394, slideActive, slideSelect);
					locSelect = 6;
				}

				else if (ev.button.y > 431 && ev.button.y < 468)
				{
					SelectFunction(SlideBar, Select, SlideBarFonts, 431, slideActive, slideSelect);
					locSelect = 7;
				}

				else if (ev.button.y > 469 && ev.button.y < 506)
				{
					SelectFunction(SlideBar, Select, SlideBarFonts, 469, slideActive, slideSelect);
					locSelect = 8;
				}

				else if (ev.button.y > 507 && ev.button.y < 544)
				{
					SelectFunction(SlideBar, Select, SlideBarFonts, 507, slideActive, slideSelect);
					locSelect = 9;
				}

				else if (ev.button.y > 545 && ev.button.y < 582)
				{
					SelectFunction(SlideBar, Select, SlideBarFonts, 545, slideActive, slideSelect);
					locSelect = 10;
				}

				else if (ev.button.y > 583 && ev.button.y < 618)
				{
					SelectFunction(SlideBar, Select, SlideBarFonts, 583, slideActive, slideSelect);
					locSelect = 11;
				}

				else if (ev.button.y > 619 && ev.button.y < 655)
				{
					SelectFunction(SlideBar, Select, SlideBarFonts, 619, slideActive, slideSelect);
					locSelect = 12;
				}

				if (slideSelect)
				{
					slideSelect = false;

					LoadBackground.setButton();

					if (locSelect < 4)
						LoadAllMail(locSelect - 1);



					slideTag.setCharTextShaded(SlideTagStr[locSelect - 1].c_str(), 54, 55, 60);

					SDL_RenderPresent(renderer);
				}
			}

			else if (ev.button.x > 275 && slideActive)
			{
				LoadBackground.setButton();
				LoadAllMail(locSelect - 1);
				slideTag.setCharTextShaded(SlideTagStr[locSelect - 1].c_str(), 54, 55, 60);

				slideActive = false;
				SDL_RenderPresent(renderer);
			}
			else
			{
				Search.setButton();
			}



		}

		//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> SDL MOUSEMOTION <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		else if (ev.type == SDL_MOUSEMOTION)
		{
			if (ev.button.x > 25 && ev.button.x < 275 && slideActive)														//Motion Select
			{
				if (ev.button.y > 165 && ev.button.y < 202)
					MotionSelectFunction(SlideBar, MotionSelect, SlideBarFonts, Select, 165);

				else if (ev.button.y > 204 && ev.button.y < 241)
					MotionSelectFunction(SlideBar, MotionSelect, SlideBarFonts, Select, 204);

				else if (ev.button.y > 242 && ev.button.y < 279)
					MotionSelectFunction(SlideBar, MotionSelect, SlideBarFonts, Select, 242);

				else if (ev.button.y > 317 && ev.button.y < 354)
					MotionSelectFunction(SlideBar, MotionSelect, SlideBarFonts, Select, 317);

				else if (ev.button.y > 356 && ev.button.y < 393)
					MotionSelectFunction(SlideBar, MotionSelect, SlideBarFonts, Select, 356);

				else if (ev.button.y > 394 && ev.button.y < 431)
					MotionSelectFunction(SlideBar, MotionSelect, SlideBarFonts, Select, 394);

				else if (ev.button.y > 431 && ev.button.y < 468)
					MotionSelectFunction(SlideBar, MotionSelect, SlideBarFonts, Select, 431);

				else if (ev.button.y > 469 && ev.button.y < 506)
					MotionSelectFunction(SlideBar, MotionSelect, SlideBarFonts, Select, 469);

				else if (ev.button.y > 507 && ev.button.y < 544)
					MotionSelectFunction(SlideBar, MotionSelect, SlideBarFonts, Select, 507);

				else if (ev.button.y > 545 && ev.button.y < 582)
					MotionSelectFunction(SlideBar, MotionSelect, SlideBarFonts, Select, 545);

				else if (ev.button.y > 583 && ev.button.y < 618)
					MotionSelectFunction(SlideBar, MotionSelect, SlideBarFonts, Select, 583);

				else if (ev.button.y > 619 && ev.button.y < 655)
					MotionSelectFunction(SlideBar, MotionSelect, SlideBarFonts, Select, 619);
				else
					MotionSelectFunction(SlideBar, MotionSelect, SlideBarFonts, Select, -400);
			}
			else if (ev.button.x > 275 && slideActive)
				MotionSelectFunction(SlideBar, MotionSelect, SlideBarFonts, Select, -400);

			if (ev.button.x > 227 && ev.button.x < 259 && ev.button.y > 52 && ev.button.y < 78 && slideActive)
			{
				Back.setButton();
				backMotion = true;

				SDL_RenderPresent(renderer);
			}
			else if (slideActive && backMotion)
			{
				Back.setButton1();
				backMotion = false;

				SDL_RenderPresent(renderer);
			}

			if (ev.button.x > 925 && ev.button.x < 949 && ev.button.y > 48 && ev.button.y < 75)								//Exit Button
			{
				Icon.setButton2();

				SDL_RenderPresent(renderer);
			}
			else if (ev.button.x > 884 && ev.button.x < 914 && ev.button.y > 45 && ev.button.y < 75)						//Settting Button
			{
				Icon.setButton1();

				SDL_RenderPresent(renderer);
			}
			else if (ev.button.x > 877 && ev.button.x < 926 && ev.button.y > 132 && ev.button.y < 181)						//Send Button
			{
				Send.setButton1();

				SDL_RenderPresent(renderer);
			}
			else if (ev.button.x > 669 && ev.button.x < 866 && ev.button.y > 45 && ev.button.y < 80 && !SearchSelect)		//Search Button
			{
				Search.setButton1();

				SDL_RenderPresent(renderer);
			}
			else if (ev.button.x > 60 && ev.button.x < 87 && ev.button.y > 79 && ev.button.y < 100 && !slideActive)
			{
				Slide.setButton1();

				SDL_RenderPresent(renderer);
			}
			else if (ev.button.x > 70 && ev.button.x < 940 && ev.button.y > 185 && ev.button.y < 605 && !slideActive)
			{
				r.h = 460;	r.w = 20;	r.x = 35;	r.y = 190;
				SDL_SetRenderDrawColor(renderer, 235, 235, 235, 0);
				SDL_RenderFillRect(renderer, &r);

				if (ev.button.y > 185 && ev.button.y < 255 && sizeBoxes[locSelect - 1] >= 1)								//Email 1
				{
					Motion.setPosition(40, 200);
					Motion.setButton();
				}
				else if (ev.button.y > 255 && ev.button.y < 325 && sizeBoxes[locSelect - 1] >= 2)							//Email 2
				{
					Motion.setPosition(40, 270);
					Motion.setButton();
				}
				else if (ev.button.y > 325 && ev.button.y < 395 && sizeBoxes[locSelect - 1] >= 3)							//Email 3
				{
					Motion.setPosition(40, 340);
					Motion.setButton();
				}
				else if (ev.button.y > 395 && ev.button.y < 465 && sizeBoxes[locSelect - 1] >= 4)							//Email 4
				{
					Motion.setPosition(40, 410);
					Motion.setButton();
				}
				else if (ev.button.y > 465 && ev.button.y < 535 && sizeBoxes[locSelect - 1] >= 5)							//Email 5
				{
					Motion.setPosition(40, 480);
					Motion.setButton();
				}
				else if (ev.button.y > 535 && ev.button.y < 605 && sizeBoxes[locSelect - 1] >= 6)							//Email 5
				{
					Motion.setPosition(40, 550);
					Motion.setButton();
				}

				Icon.setButton();
				Send.setButton();

				if (!SearchSelect)
					Search.setButton();

				SDL_RenderPresent(renderer);
			}
			else
			{
				if (!slideActive)
				{
					r.h = 460;	r.w = 20;	r.x = 35;	r.y = 190;
					SDL_SetRenderDrawColor(renderer, 235, 235, 235, 0);
					SDL_RenderFillRect(renderer, &r);
				}

				Icon.setButton();
				Send.setButton();

				if (!slideActive)
					Slide.setButton();

				if (!SearchSelect)
					Search.setButton();


				SDL_RenderPresent(renderer);
			}



		}
	}
	return 0;
}

void Animation2()
{
	SDL_Texture *frames[50];
	SDL_Rect r;
	r.h = 700;	r.w = 1000;	r.x = 0;	r.y = 0;
	string add;

	for (int i = 0; i < 50; i++)
	{
		add = "Animation2/Zoom-in_" + to_string(i + 1) + ".png";
		frames[i] = IMG_LoadTexture(renderer, add.c_str());
		SDL_RenderCopy(renderer, frames[i], 0, &r);
		SDL_RenderPresent(renderer);
		SDL_Delay(1);
	}
}

int LoginMenu()
{

	//>>>>>>>>>>>>>>>>> Load Button <<<<<<<<<<<<<<<<<<

	Button LoadPage(renderer, "Login Menu/Button/Load.png");
	LoadPage.setButton();
	SDL_RenderPresent(renderer);

	Button Logo(renderer,
		"Login Menu/Button/Logo.png");

	Button RememberText(renderer,
		"Login Menu/Button/RememberText.png");

	Button login(renderer,
		"Login Menu/Button/Login.png", "Login Menu/Button/Login1.png",
		"Login Menu/Button/Login2.png");

	Button Email(renderer,
		"Login Menu/Button/Email.png", "Login Menu/Button/Email1.png",
		"Login Menu/Button/Email2.png");

	Button Singup(renderer,
		"Login Menu/Button/Sing up.png", "Login Menu/Button/Sing up1.png",
		"Login Menu/Button/Sing up2.png");

	Button Remember(renderer,
		"Login Menu/Button/Remember.png", "Login Menu/Button/Remember1.png",
		"Login Menu/Button/Remember2.png");

	Button Password(renderer,
		"Login Menu/Button/Password.png", "Login Menu/Button/Password1.png",
		"Login Menu/Button/Password2.png", "Login Menu/Button/Password3.png");

	//>>>>>>>>>>>> Set Font  & TextInput <<<<<<<<<<<<<

	SDL_StartTextInput();
	string t = "";
	string textEmail = "";
	string textPassword = "";

	Font font1(screen, renderer, "Font/Roboto-Light.ttf", 22);
	font1.setColor(70, 70, 70, 0);
	font1.setRectCoordinate(343, 335);

	Font font2(screen, renderer, "Font/Roboto-Light.ttf", 25);
	font2.setColor(70, 70, 70, 0);
	font2.setRectCoordinate(343, 408);

	bool inputEmail = false;
	bool inputPassword = false;
	bool RememberButton = false;
	bool showPassword = false;

	//>>>>>>>>>>>>>>>>>>> Events <<<<<<<<<<<<<<<<<<<<

	SDL_Event ev;

	while (SDL_WaitEvent(&ev)) {

		if (ev.type == SDL_QUIT){
			SDL_Quit();
		}

		//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> SDL_MOUSEBUTTONDOWN <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		else if (ev.type == SDL_MOUSEBUTTONDOWN)
		{
			if (ev.button.x > 325 && ev.button.x < 675 && ev.button.y > 325 && ev.button.y < 375)			//Email
			{
				Email.setButton1();
				font1.setCharText(textEmail.c_str());

				if (textPassword.size() == 0)
					Password.setButton();

				else
				{
					Password.setButton2();
					t = textPassword;
					t.replace(0, t.size(), t.size(), '*');
					font2.setCharText(t.c_str());
				}

				inputEmail = true;
				inputPassword = false;

				SDL_RenderPresent(renderer);
			}

			else if (ev.button.x > 325 && ev.button.x < 675 && ev.button.y > 395 && ev.button.y < 445)		//Password
			{
				if (ev.button.x > 636 && ev.button.x < 664 && ev.button.y > 403 && ev.button.y < 437)
				{
					Password.setButton3();
					textPassword;
					font2.setSize(22);
					font2.setCharText(textPassword.c_str());

					SDL_RenderPresent(renderer);
					SDL_Delay(1000);
					font2.setSize(25);
				}

				Password.setButton1();
				t = textPassword;
				t.replace(0, t.size(), t.size(), '*');
				font2.setCharText(t.c_str());

				if (textEmail.size() == 0)
					Email.setButton();

				else
				{
					Email.setButton2();
					font1.setCharText(textEmail.c_str());
				}

				inputEmail = false;
				inputPassword = true;

				SDL_RenderPresent(renderer);
			}

			else if (ev.button.x > 325 && ev.button.x < 675 && ev.button.y > 465 && ev.button.y < 515)		//login
			{

				string User_Pass = "login#" + textEmail + "#" + textPassword;

				char *strMessage = new char[User_Pass.length() + 1];
				strcpy(strMessage, User_Pass.c_str());

				creatClient.sendMessage(strMessage);

				if (creatClient.buffer[0] == '0')
				{
					textEmail = "";
					textPassword = "";

					Email.setButton();
					Password.setButton();
					login.setButton2();
					SDL_RenderPresent(renderer);
					SDL_Delay(2500);

					login.setButton();
					SDL_RenderPresent(renderer);
				}
				else if (creatClient.buffer[0] == '1')
				{
					Animation2();
					usernametagTemp = textEmail;
					textEmail = "";
					textPassword = "";
					locSelect = 1;


					MainMenu();

					break;
				}
			}

			else if (ev.button.x > 325 && ev.button.x < 355 && ev.button.y > 535 && ev.button.y < 565)		//Remember
			{
				if (RememberButton)
				{
					Remember.setButton();
					RememberButton = false;
				}
				else
				{
					Remember.setButton2();
					RememberButton = true;
				}

				if (textPassword.size() == 0)
					Password.setButton();

				else
				{
					Password.setButton2();
					t = textPassword;
					t.replace(0, t.size(), t.size(), '*');
					font2.setCharText(t.c_str());
				}

				if (textEmail.size() == 0)
					Email.setButton();

				else
				{
					Email.setButton2();
					font1.setCharText(textEmail.c_str());
				}
				inputEmail = false;
				inputPassword = false;

				SDL_RenderPresent(renderer);
			}

			else
			{
				if (textEmail.size() == 0)
					Email.setButton();

				else
				{
					Email.setButton2();
					font1.setCharText(textEmail.c_str());
				}

				if (textPassword.size() == 0)
					Password.setButton();

				else
				{
					Password.setButton2();
					t = textPassword;
					t.replace(0, t.size(), t.size(), '*');
					font2.setCharText(t.c_str());
				}

				inputEmail = false;
				inputPassword = false;

				SDL_RenderPresent(renderer);
			}
		}

		//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> SDL_TEXTINPUT <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		else if (ev.type == SDL_TEXTINPUT || ev.type == SDL_KEYDOWN)
		{
			system("cls");

			if (inputEmail)
			{
				if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_BACKSPACE && textEmail.length() > 0)
					textEmail = textEmail.substr(0, textEmail.length() - 1);
				else if (ev.type == SDL_TEXTINPUT)
					textEmail += ev.text.text;

				Email.setButton1();

				if (textPassword.size() == 0)
					Password.setButton();

				else
				{
					Password.setButton2();
					t = textPassword;
					t.replace(0, t.size(), t.size(), '*');
					font2.setCharText(t.c_str());
				}

				font1.setCharText(textEmail.c_str());

				SDL_RenderPresent(renderer);
			}

			else if (inputPassword)
			{
				if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_BACKSPACE && textPassword.length() > 0)
					textPassword = textPassword.substr(0, textPassword.length() - 1);
				else if (ev.type == SDL_TEXTINPUT)
					textPassword += ev.text.text;

				Password.setButton1();

				if (textEmail.size() == 0)
					Email.setButton();

				else
				{
					Email.setButton2();
					font1.setCharText(textEmail.c_str());
				}

				t = textPassword;
				t.replace(0, t.size(), t.size(), '*');
				font2.setCharText(t.c_str());

				SDL_RenderPresent(renderer);
			}

			if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_TAB)
			{
				if (inputEmail)
				{
					inputEmail = false;
					inputPassword = true;

					if (textEmail.size() == 0)
						Email.setButton();
					else
					{
						Email.setButton2();
						font1.setCharText(textEmail.c_str());
					}

					Password.setButton1();
					t = textPassword;
					t.replace(0, t.size(), t.size(), '*');
					font2.setCharText(t.c_str());

					SDL_RenderPresent(renderer);
				}

				else if (inputPassword)
				{
					inputEmail = true;
					inputPassword = false;

					if (textPassword.size() == 0)
						Password.setButton();
					else
					{
						Password.setButton2();
						t = textPassword;
						t.replace(0, t.size(), t.size(), '*');
						font2.setCharText(t.c_str());
					}

					Email.setButton1();
					font1.setCharText(textEmail.c_str());

					SDL_RenderPresent(renderer);
				}
			}

			else if (ev.type == SDL_KEYDOWN)
			{
				if (ev.key.keysym.sym == SDLK_RETURN || ev.key.keysym.sym == SDLK_KP_ENTER)
				{
					string User_Pass = "login#" + textEmail + "#" + textPassword;

					char *strMessage = new char[User_Pass.length() + 1];
					strcpy(strMessage, User_Pass.c_str());

					creatClient.sendMessage(strMessage);

					if (creatClient.buffer[0] == '0')
					{
						textEmail = "";
						textPassword = "";

						Email.setButton();
						Password.setButton();
						login.setButton2();
						SDL_RenderPresent(renderer);
						SDL_Delay(2500);

						login.setButton();
						SDL_RenderPresent(renderer);
					}
					else if (creatClient.buffer[0] == '1')
					{
						Animation2();
						usernametagTemp = textEmail;
						textEmail = "";
						textPassword = "";
						locSelect = 1;

						MainMenu();

						break;
					}
				}
			}
		}

		//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> SDL_MOUSEMOTION <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		else if (ev.type == SDL_MOUSEMOTION)
		{
			if (ev.button.x > 325 && ev.button.x < 675 && ev.button.y > 465 && ev.button.y < 515)
			{
				login.setButton1();
				SDL_RenderPresent(renderer);
				SDL_Delay(200);
			}
			else if (ev.button.x > 325 && ev.button.x < 355 && ev.button.y > 535 && ev.button.y < 565)
			{
				if (!RememberButton)
				{
					Remember.setButton1();
					SDL_RenderPresent(renderer);
					SDL_Delay(200);
				}
			}
			else if (ev.button.x > 494 && ev.button.x < 548 && ev.button.y > 541 && ev.button.y < 559)
			{
				Singup.setButton1();
				SDL_RenderPresent(renderer);
				SDL_Delay(100);
			}
			else if (ev.button.x > 556 && ev.button.x < 667 && ev.button.y > 541 && ev.button.y < 559)
			{
				Singup.setButton2();
				SDL_RenderPresent(renderer);
				SDL_Delay(100);
			}
			else
			{
				login.setButton();
				Singup.setButton();
				if (!RememberButton)
					Remember.setButton();

				SDL_RenderPresent(renderer);
			}
		}
	}

	SDL_StopTextInput();
	return 0;
}

void Animation1()
{
	SDL_Texture *frames[40];
	SDL_Rect r;
	r.h = 700;	r.w = 1000;	r.x = 0;	r.y = 0;
	string add;

	for (int i = 0; i < 40; i++)
	{
		add = "Animation1/frame_" + to_string(i + 1) + ".png";
		frames[i] = IMG_LoadTexture(renderer, add.c_str());
		SDL_RenderCopy(renderer, frames[i], 0, &r);
		SDL_RenderPresent(renderer);
		SDL_Delay(10);
	}
}

int SDL_Inits()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cerr << "SDL_Init error: " << SDL_GetError() << endl;
		return 1;
	}

	int imgFlags = IMG_INIT_PNG;

	if (!(IMG_Init(imgFlags) && imgFlags))
		cout << "Error: " << IMG_GetError() << endl;

	if (TTF_Init() < 0)
		cout << "Error: " << TTF_GetError << endl;
}

int main(int argc, char *argv[])
{
	SDL_Inits();

	screen = SDL_CreateWindow("Mail App", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 700, 0);
	renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);

	r.h = 700;	r.w = 1000;
	r.x = 0;	r.y = 0;

	Animation1();
	LoginMenu();
	//MainMenu();
	//SendMenu();

	SDL_DestroyWindow(screen);
	SDL_DestroyRenderer(renderer);

	IMG_Quit();
	SDL_Quit();
	TTF_Quit();

	return 0;
}