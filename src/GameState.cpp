#include "Input.h"
#include "BaseState.h"
#include "Title.h"
#include "Play.h"
#include "GameState.h"

GameState::GameState(StateType type)
{
    switch (type)
    {
    case StateType::TITLE:
        state_ = new Title;
        break;
    case StateType::PLAY:
        state_ = new Play;
        break;
    }
    state_->enterState();
}

GameState::~GameState()
{
    if (state_)
    {
        delete state_;
        state_ = nullptr;
    }
}

void GameState::update()
{
    BaseState* nextState = nullptr;
    nextState = state_->update();

    if (nextState)
    {
        state_->exitState();
        delete state_;
        input()->reset(); 
        state_ = nextState;
        state_->enterState();
    }
}