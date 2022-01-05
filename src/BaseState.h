#ifndef _BASE_STATE_H_
#define _BASE_STATE_H_

class BaseState
{
public:
    virtual void enterState(){};
    virtual BaseState* update(double elasped) = 0;
    virtual void exitState(){};
    virtual ~BaseState(){}
};

#endif