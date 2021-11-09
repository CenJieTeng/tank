#include "cstring"
#include "SDL2/SDL.h"
#include "Input.h"

bool Input::inputs[Input::InputKey::INPUT_END];
bool Input::inputs2[Input::InputKey::INPUT_END];

Input* input()
{
    static Input input;
    return &input;
}

void Input::update()
{
	SDL_Event event;
    std::memset(&inputs2, 0, sizeof(inputs2));
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_KEYDOWN:
			{
				switch (event.key.keysym.sym)
				{
					case SDL_KeyCode::SDLK_w:
                        inputs[InputKey::INPUT_W] = 1;
                        inputs2[InputKey::INPUT_W] = 1;
                        break;
					case SDL_KeyCode::SDLK_a:
                        inputs[InputKey::INPUT_A] = 1;
                        inputs2[InputKey::INPUT_A] = 1;
                        break;
					case SDL_KeyCode::SDLK_s:
                        inputs[InputKey::INPUT_S] = 1;
                        inputs2[InputKey::INPUT_S] = 1;
                        break;
					case SDL_KeyCode::SDLK_d:
						inputs[InputKey::INPUT_D] = 1;
                        inputs2[InputKey::INPUT_D] = 1;
                        break;
                    case SDL_KeyCode::SDLK_SPACE:
                        inputs[InputKey::INPUT_SPACE] = 1;
                        inputs2[InputKey::INPUT_SPACE] = 1;
                    break;
				}
			}break;
			case SDL_KEYUP:
			{
				switch (event.key.keysym.sym)
				{
					case SDL_KeyCode::SDLK_w:
                        inputs[InputKey::INPUT_W] = 0;
                        break;
					case SDL_KeyCode::SDLK_a:
                        inputs[InputKey::INPUT_A] = 0;
                        break;
					case SDL_KeyCode::SDLK_s:
                        inputs[InputKey::INPUT_S] = 0;
                        break;
					case SDL_KeyCode::SDLK_d:
                        inputs[InputKey::INPUT_D] = 0;
                        break;
                    case SDL_KeyCode::SDLK_SPACE:
                        inputs[InputKey::INPUT_SPACE] = 0;
                        break;
				}
			}break;
		}
	}
}

bool Input::isOn(InputKey key)
{
    if (key < 0 || key >= InputKey::INPUT_END)
        return false;
    return inputs[key];
}

bool Input::isTrigger(InputKey key)
{
    if (key < 0 || key >= InputKey::INPUT_END)
        return false;
    return inputs2[key];
}

void Input::reset()
{
    memset(&inputs, 0, sizeof(bool) * InputKey::INPUT_END);
    memset(&inputs2, 0, sizeof(bool) * InputKey::INPUT_END);
}