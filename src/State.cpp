#include "State.hpp"

#include "common.hpp"

#include "InputManager.hpp"

using namespace common;

using std::string;
using std::list;

// =============================================================================
// State::ArgsBase Class
// =============================================================================

State::ArgsBase::ArgsBase() {}
State::ArgsBase::~ArgsBase() {}

// =============================================================================
// State::Args Class
// =============================================================================

State::Change::Change(const string& state, ArgsBase* args) : state_(state), args_(args) {}
const string& State::Change::state() const { return state_; }
State::ArgsBase* State::Change::args() const { return args_; }

// =============================================================================
// State::StackUp Class
// =============================================================================

State::StackUp::StackUp(const string& state, ArgsBase* args) : Change(state, args) {}

// =============================================================================
// State::Unstack Class
// =============================================================================

State::Unstack::Unstack(ArgsBase* args) : Change("", args) {}

// =============================================================================
// State Class
// =============================================================================

// Static vars
std::map<string, State* (*)(State::ArgsBase* args)> State::builders;
list<State*> State::states;

State::State() : frozen_(false), bg(0) {
	// all sprites
	Sprite::all.push_back(&sprites);
	
	// all game objects
	GameObject::all.push_back(&game_objects);
	
	// all game objects interactions
	Interaction::all.push_back(&interactions);
	
	// quit event
	InputManager::instance()->connect(InputManager::QUIT, this, &State::handleQuit);
}

State::~State() {
	// all sprites
	while (sprites.size())
		delete sprites.back();
	Sprite::all.pop_back();
	
	// all game objects
	while (game_objects.size())
		delete game_objects.back();
	GameObject::all.pop_back();
	
	// all game objects interactions
	while (interactions.size())
		delete interactions.back();
	Interaction::all.pop_back();
	
	// quit event
	InputManager::instance()->disconnect(this);
}

State* State::build(const string& name, ArgsBase* args) {
	// for unknown game states
	if (builders.find(name) == builders.end())
		throw mexception("Trying to load unknown game state");
	return (*builders[name])(args);
}

void State::handleUnstack(ArgsBase* args) {}

bool State::frozen() const { return frozen_; }

void State::externUpdate() {
	// all sprites
	Sprite::updateAll();
	
	// game objects interactions
	Interaction::interactAll();
	
	// all game objects
	GameObject::updateAll();
	
	// specific game state
	update();
}

void State::externRender() {
	// background
	if (bg)
		bg->render();
	
	// all game objects
	GameObject::renderAll();
	
	// specific game state
	render();
}

void State::update() {}
void State::render() {}

void State::handleQuit(const observer::Event& event, bool& stop) {
	throw Quit();
}
