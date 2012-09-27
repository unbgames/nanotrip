#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "observer.hpp"

#include "GameObject.hpp"

class Button : public GameObject {
SUBJECT
public:
	enum {
		CLICKED = 0,
		
		// don't change this
		LASTEVENT
	};
private:
	int clip_y;
	bool clicked;
	bool enabled;
public:
	Button(Sprite* sprite);
	~Button();
	
	void update();
	void render();
	
	void enable(bool enable);
private:
	void handleMouseDownLeft(const observer::Event& event, bool& stop);
	void handleMouseUpLeft(const observer::Event& event, bool& stop);
};

#endif
