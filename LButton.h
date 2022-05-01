#pragma once
//The mouse button
class LButton
{
public:
	//Initializes internal variables
	LButton();

	//Sets top left position
	void setPosition(int x, int y);

	//Handles mouse event
	void handleEvent(SDL_Event* e);

	//Shows button sprite
	void render();

	void set_gTexture(const string& path, const int& n);

	void setPositionOfTexture();

	void free();

	LButtonSprite getStatus();

private:
	//Top left position
	SDL_Point mPosition;

	//Currently used global sprite
	LButtonSprite mCurrentSprite;

	//Current displayed texture
	SDL_Texture* gTexture[3];

	//Position of texture
	SDL_Rect rect;
};
LButtonSprite LButton::getStatus() {
	return mCurrentSprite;
}
SDL_Texture* loadTexture(string path) {

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	//Create texture from surface pixels
	newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

	//Get rid of old loaded surface
	SDL_FreeSurface(loadedSurface);

	return newTexture;
}

LButton::LButton()
{
	mPosition.x = 0;
	mPosition.y = 0;

	mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;

	for (int i = 0; i < 3; i++) {
		gTexture[i] = NULL;
	}
}

void LButton::setPosition(int x, int y)
{
	mPosition.x = x;
	mPosition.y = y;
}

void LButton::handleEvent(SDL_Event* e)
{
	//If mouse event happened
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN)
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if (x < mPosition.x)
		{
			inside = false;
		}
		//Mouse is right of the button
		else if (x > mPosition.x + BUTTON_WIDTH)
		{
			inside = false;
		}
		//Mouse above the button
		else if (y < mPosition.y)
		{
			inside = false;
		}
		//Mouse below the button
		else if (y > mPosition.y + BUTTON_HEIGHT)
		{
			inside = false;
		}

		//Mouse is outside button
		if (!inside)
		{
			mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
		}
		//Mouse is inside button
		else
		{
			//Set mouse over sprite
			switch (e->type)
			{
			case SDL_MOUSEMOTION:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
				break;

			case SDL_MOUSEBUTTONDOWN:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
				break;

			}
		}
	}
}

void LButton::set_gTexture(const string& path, const int& n) {
	gTexture[n] = loadTexture(path);
	if (gTexture[n] == NULL) {
		cout << "Unable to load png file!" << SDL_GetError() << endl;
	}
}

void LButton::setPositionOfTexture() {
	rect.x = mPosition.x;
	rect.y = mPosition.y;
	rect.w = BUTTON_WIDTH;
	rect.h = BUTTON_HEIGHT;
}

void LButton::render()
{
	//Show current button sprite
	
	switch (mCurrentSprite) {
		case BUTTON_SPRITE_MOUSE_OUT:
		{
			SDL_RenderCopy(gRenderer, gTexture[0], NULL, &rect);
			break;
		}
		case BUTTON_SPRITE_MOUSE_OVER_MOTION:
		{
			SDL_RenderCopy(gRenderer, gTexture[1], NULL, &rect);
			break;
		}
		case BUTTON_SPRITE_MOUSE_DOWN:
		{
			SDL_RenderCopy(gRenderer, gTexture[2], NULL, &rect);
			break;
		}
	}

}

void LButton::free() {
	for (int i = 0; i < 3; i++) {
		gTexture[i] = NULL;
	}
}