#ifndef __GameDev2D__GamePadLeftThumbStickEvent__
#define __GameDev2D__GamePadLeftThumbStickEvent__

#include "Event.h"
#include "../Input/GamePad.h"
#include "../Math/Vector2.h"


namespace GameDev2D
{
    class GamePadLeftThumbStickEvent : public Event
    {
    public:
        GamePadLeftThumbStickEvent(GamePad* gamePad, Vector2 value);

        //Returns the GamePad that was just connected
        GamePad* GetGamePad();

        //Returns the left thumb stick's value
        Vector2 GetValue();

    protected:
        void LogEvent();

    private:
        GamePad* m_GamePad;
        Vector2 m_Value;
    };
}

#endif
