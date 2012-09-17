#include "StateNewGame.hpp"

#include "common.hpp"

using namespace lalge;
using namespace common;

GAMESTATE_DEF(StateNewGame)

StateNewGame::StateNewGame(ArgsBase* args) {
	bg = new Sprite("img/bg_opaco.png");
	
	history = new Button(new Sprite("img/load_button.png"));
	history->getShape()->position = r2vec(640, 100);
	history->connect(Button::CLICKED, this, &StateNewGame::handleHistory);
	
	loadlevel = new Button(new Sprite("img/load_button.png"));
	loadlevel->getShape()->position = r2vec(640, 200);
	loadlevel->connect(Button::CLICKED, this, &StateNewGame::handleLoadLevel);
	
	makelevel = new Button(new Sprite("img/load_button.png"));
	makelevel->getShape()->position = r2vec(640, 300);
	makelevel->connect(Button::CLICKED, this, &StateNewGame::handleMakeLevel);
	
	goback = new Button(new Sprite("img/load_button.png"));
	goback->getShape()->position = r2vec(640, 400);
	goback->connect(Button::CLICKED, this, &StateNewGame::handleGoBack);
}

void StateNewGame::update() {
}

void StateNewGame::render() {
}

void StateNewGame::handleHistory(const observer::Event& event, bool& stop) {
	throw new Change("StateFirstLevel");
}

void StateNewGame::handleLoadLevel(const observer::Event& event, bool& stop) {
	throw new Change("StateLoadLevel");
}

void StateNewGame::handleMakeLevel(const observer::Event& event, bool& stop) {
	SHOW("makelevel");
}

void StateNewGame::handleGoBack(const observer::Event& event, bool& stop) {
	throw Quit();
}
