class Button
{
public:
	Button(SDL_Renderer *, char *, int, int, int, int);
	Button(SDL_Renderer *, char *, char *, int, int, int, int);
	Button(SDL_Renderer *, char *, char *, char *, int, int, int, int);
	Button(SDL_Renderer *, char *, char *, char *, char *, int, int, int, int);
	Button(SDL_Renderer *, char *, char *, char *, char *, char *, int, int, int, int);
	Button(SDL_Renderer *, char *, char *, char *, char *, char *, char *, int, int, int, int);
	void setPosition();
	void setPosition(int, int);
	void setPosition(int, int, int, int);
	void setButton();
	void setButton1();
	void setButton2();
	void setButton3();
	void setButton4();
	void setButton5();

private:
	SDL_Rect rect;
	SDL_Texture *button;
	SDL_Texture *button1;
	SDL_Texture *button2;
	SDL_Texture *button3;
	SDL_Texture *button4;
	SDL_Texture *button5;
	SDL_Renderer *renderer;
	int height;
	int width;
	int x;
	int y;

};

Button::Button(SDL_Renderer *renderer, char *button,
	int height = 700, int width = 1000, int x = 0, int y = 0)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->renderer = renderer;

	setPosition();

	this->button = IMG_LoadTexture(renderer, button);
}

Button::Button(SDL_Renderer *renderer, char *button, char *button1,
	int height = 700, int width = 1000, int x = 0, int y = 0)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->renderer = renderer;

	setPosition();

	this->button = IMG_LoadTexture(renderer, button);
	this->button1 = IMG_LoadTexture(renderer, button1);
}

Button::Button(SDL_Renderer *renderer, char *button, char *button1, char *button2,
	int height = 700, int width = 1000, int x = 0, int y = 0)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->renderer = renderer;

	setPosition();

	this->button = IMG_LoadTexture(renderer, button);
	this->button1 = IMG_LoadTexture(renderer, button1);
	this->button2 = IMG_LoadTexture(renderer, button2);
}

Button::Button(SDL_Renderer *renderer, char *button, char *button1, char *button2, char *button3,
	int height = 700, int width = 1000, int x = 0, int y = 0)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->renderer = renderer;

	setPosition();

	this->button = IMG_LoadTexture(renderer, button);
	this->button1 = IMG_LoadTexture(renderer, button1);
	this->button2 = IMG_LoadTexture(renderer, button2);
	this->button3 = IMG_LoadTexture(renderer, button3);
}

Button::Button(SDL_Renderer *renderer, char *button, char *button1, char *button2, char *button3, char *button4,
	int height = 700, int width = 1000, int x = 0, int y = 0)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->renderer = renderer;

	setPosition();

	this->button = IMG_LoadTexture(renderer, button);
	this->button1 = IMG_LoadTexture(renderer, button1);
	this->button2 = IMG_LoadTexture(renderer, button2);
	this->button3 = IMG_LoadTexture(renderer, button3);
	this->button4 = IMG_LoadTexture(renderer, button4);
}

Button::Button(SDL_Renderer *renderer, char *button, char *button1, char *button2, char *button3, char *button4, char *button5,
	int height = 700, int width = 1000, int x = 0, int y = 0)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->renderer = renderer;

	setPosition();

	this->button = IMG_LoadTexture(renderer, button);
	this->button1 = IMG_LoadTexture(renderer, button1);
	this->button2 = IMG_LoadTexture(renderer, button2);
	this->button3 = IMG_LoadTexture(renderer, button3);
	this->button4 = IMG_LoadTexture(renderer, button4);
	this->button5 = IMG_LoadTexture(renderer, button5);
}

void Button::setPosition()
{
	rect.h = height;	rect.w = width;
	rect.x = x;			rect.y = y;
}

void Button::setPosition(int x, int y)
{
	rect.x = x;			rect.y = y;
}

void Button::setPosition(int height, int width, int x, int y)
{
	rect.h = height;	rect.w = width;
	rect.x = x;			rect.y = y;
}

void Button::setButton()
{
	SDL_RenderCopy(renderer, button, 0, &rect);
}

void Button::setButton1()
{
	SDL_RenderCopy(renderer, button1, 0, &rect);
}

void Button::setButton2()
{
	SDL_RenderCopy(renderer, button2, 0, &rect);
}

void Button::setButton3()
{
	SDL_RenderCopy(renderer, button3, 0, &rect);
}

void Button::setButton4()
{
	SDL_RenderCopy(renderer, button4, 0, &rect);
}

void Button::setButton5()
{
	SDL_RenderCopy(renderer, button5, 0, &rect);
}