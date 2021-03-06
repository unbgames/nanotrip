
#ifndef STATERANKING_HPP
#define STATERANKING_HPP

#include "State.hpp"
#include "Button.hpp"
#include "Ranking.hpp"

class StateRanking : public State {
GAMESTATE
private:
	Sprite* bg;
	Sprite* ranking;
	
	Ranking ranking_data;
	
	Button* back;
public:
	StateRanking(ArgsBase* args);
	~StateRanking();
	
	void update();
	void render();
private:
	void handleGoBack(const observer::Event& event, bool& stop);
};

#endif
