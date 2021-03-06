#include "StatePause.hpp"

#include "InputManager.hpp"
#include "SDLBase.hpp"
#include "StateLevel.hpp"

using namespace lalge;

GAMESTATE_DEF(StatePause)

StatePause::StatePause(ArgsBase* args) {
	bg = new Sprite("img/level/background_pause.png");
	
	shadow = new Sprite("img/level/shadow.png");
	eatles = new Animation("img/level/eatles_wait.png", 0, 20, 1, 18);
	
	retry = new Button(new Sprite("img/level/button_retry.png"));
	menu = new Button(new Sprite("img/level/button_menu.png"));
	resume = new Button(new Sprite("img/level/button_resume.png"));
	
	
	int retry_x, menu_x, resume_x;
	if (args) {
		delete args;
		retry->enable(false);
		
		retry_x = 600 - (retry->sprite->srcW() + menu->sprite->srcW())/2;
		menu_x = 600 - menu->sprite->srcW()/2;
		resume_x = 680 + menu->sprite->srcW()/2;
	}
	else {
		retry_x = 600 - (retry->sprite->srcW() + menu->sprite->srcW())/2;
		menu_x = 640;
		resume_x = 680 + (resume->sprite->srcW() + menu->sprite->srcW())/2;
	}
	
	retry->getShape()->position = r2vec(retry_x, 572);
	retry->connect(Button::CLICKED, this, &StatePause::handleRetry);
	
	menu->getShape()->position = r2vec(menu_x, 572);
	menu->connect(Button::CLICKED, this, &StatePause::handleMenu);
	
	resume->getShape()->position = r2vec(resume_x, 572);
	resume->connect(Button::CLICKED, this, &StatePause::handleResume);
	
	InputManager::instance()->connect(InputManager::KEYDOWN, this, &StatePause::handleKeyDown);
}

StatePause::~StatePause() {
	delete bg;
	
	delete shadow;
	delete eatles;
	
	delete retry->sprite;
	delete retry;
	
	delete menu->sprite;
	delete menu;
	
	delete resume->sprite;
	delete resume;
}

void StatePause::update() {
	eatles->update();
	
	retry->update();
	menu->update();
	resume->update();
}

void StatePause::render() {
	bg->render(640, 360, true);
	
	shadow->render(640, 442, true);
	eatles->render(638, 364, true);
	
	retry->render();
	menu->render();
	resume->render();
}

void StatePause::handleKeyDown(const observer::Event& event, bool& stop) {
	if (inputmanager_event.key.keysym.sym == SDLK_ESCAPE)
		throw new Unstack();
}

void StatePause::handleRetry(const observer::Event& event, bool& stop) {
	throw new Unstack(new StateLevel::UnstackArgs(StateLevel::UnstackArgs::RESET));
}

void StatePause::handleMenu(const observer::Event& event, bool& stop) {
	throw new Unstack(new StateLevel::UnstackArgs(StateLevel::UnstackArgs::MENU));
}

void StatePause::handleResume(const observer::Event& event, bool& stop) {
	throw new Unstack();
}
