#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <string>

#include "rgb_hsv.hpp"

#include "Sprite.hpp"

class Animation : public Sprite
{
private:
	float frame;
	float fps;
	int rows;
	int cols;
	bool matrix;

	//TODO move to different class
	float lastHueShift;
	int hueInterlace;
	static const int hueInterlaceFactor = 4; //change this if the game lags
	std::vector< std::pair<int,int> > tintPixels;
	std::vector< hsv > tintColors;
public:
	int line;
	
	Animation (
		const std::string& filename,
		int frame,
		int fps,
		int rows,
		int cols,
		bool matrix = false,
		int line = 0
	);
	
	void update();
private:
	void update_();
public:
	int frameAmount() const;
	int getFrame() const;
	int getFPS() const;
	int getTimeSize() const;

	virtual void tint(float hueShift);
	
	
	void setFrame(int frame);
	void setFPS(int fps);
};

#endif
