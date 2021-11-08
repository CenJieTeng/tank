#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

class BaseState;

class GameState
{
public:
    enum class StateType
    {
        TITLE,
        PLAY,
        GAMEOVER
    };

    GameState(StateType type);
    ~GameState();
    void update();

private:
    BaseState* state_;
};

#endif