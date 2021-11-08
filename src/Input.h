#ifndef _INPUT_H_
#define _INPUT_H_

class Input
{
public:
    enum InputKey
    {
        INPUT_W,
        INPUT_A,
        INPUT_S,
        INPUT_D,
        INPUT_SPACE,

        INPUT_END
    };

    static void update();
    static bool isOn(InputKey key);
    static bool isTrigger(InputKey key);
    static void reset();

private:
    static bool inputs[InputKey::INPUT_END];
    static bool inputs2[InputKey::INPUT_END];
};

Input* input();

#endif