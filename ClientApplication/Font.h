using namespace std;

class Font
{
public:
	Font(SDL_Window *, SDL_Renderer *);
	Font(SDL_Window *, SDL_Renderer *, char *, int);
	~Font();
	void setRectCoordinate(int, int);
	void setColor(int, int, int, int);
	void setFont(char *, int);
	void setSize(int);
	void setCharText(const char *);
	void setCharTextGlyph(const Uint16);
	void setCharTextShaded(const char *, int, int, int);
	void setCharTextWrapped(const char *, int);

private:
	SDL_Window *window;
	SDL_Renderer *renderTarget;
	TTF_Font *font;
	SDL_Color color;
	SDL_Color color2;
	SDL_Surface *textSurface;
	SDL_Texture *text;
	SDL_Rect textRect;
	char *fontName;

};

Font::Font(SDL_Window *window, SDL_Renderer *renderTarget)
{
	this->window = window;
	this->renderTarget = renderTarget;
}

Font::Font(SDL_Window *window, SDL_Renderer *renderTarget, char *fontName, int size)
{
	this->window = window;
	this->renderTarget = renderTarget;

	setFont(fontName, size);
}

Font::~Font()
{
}

void Font::setColor(int red = 255, int green = 255, int blue = 255, int alfa = 0)
{
	color = { red, green, blue, alfa };
}

void Font::setRectCoordinate(int x = 0, int y = 0)
{
	textRect.x = x;
	textRect.y = y;
}

void Font::setFont(char *fontName, int size)
{
	this->fontName = fontName;
	font = TTF_OpenFont(fontName, size);
}

void Font::setSize(int size)
{
	font = TTF_OpenFont(fontName, size);
}

void Font::setCharText(const char *charText)
{
	textSurface = TTF_RenderText_Blended(font, charText, color);

	text = SDL_CreateTextureFromSurface(renderTarget, textSurface);
	SDL_QueryTexture(text, NULL, NULL, &textRect.w, &textRect.h);
	SDL_FreeSurface(textSurface);
	SDL_RenderCopy(renderTarget, text, NULL, &textRect);
}

void Font::setCharTextGlyph(const Uint16 charText)
{
	//textSurface = TTF_RenderText_Blended(font, charText, color);
	//textSurface = TTF_RenderUTF8_Blended(font, charText, color);
	//textSurface = TTF_RenderUNICODE_Blended(font, charText, color);
	textSurface = TTF_RenderGlyph_Blended(font, charText, color);

	text = SDL_CreateTextureFromSurface(renderTarget, textSurface);
	SDL_QueryTexture(text, NULL, NULL, &textRect.w, &textRect.h);
	SDL_FreeSurface(textSurface);
	SDL_RenderCopy(renderTarget, text, NULL, &textRect);
}

void Font::setCharTextShaded(const char *charText, int R, int G, int B)
{
	textSurface = TTF_RenderText_Shaded(font, charText, color, { R, G, B, 0 });

	text = SDL_CreateTextureFromSurface(renderTarget, textSurface);
	SDL_QueryTexture(text, NULL, NULL, &textRect.w, &textRect.h);
	SDL_FreeSurface(textSurface);
	SDL_RenderCopy(renderTarget, text, NULL, &textRect);
}

void Font::setCharTextWrapped(const char *charText, int wrapLength)
{
	textSurface = TTF_RenderText_Blended_Wrapped(font, charText, color, wrapLength);

	text = SDL_CreateTextureFromSurface(renderTarget, textSurface);
	SDL_QueryTexture(text, NULL, NULL, &textRect.w, &textRect.h);
	SDL_FreeSurface(textSurface);
	SDL_RenderCopy(renderTarget, text, NULL, &textRect);
}