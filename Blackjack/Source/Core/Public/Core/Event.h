#pragma once

#include <SDL2/SDL.h>
#include <functional>

namespace Core
{
	class Event
	{
	public:
		Event(SDL_Event& sdlEvent) : Ev(sdlEvent), bHandled(false) {}

		SDL_Event& Ev;
		bool bHandled;
	};


	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{}

		bool Dispatch(Uint32 sdlEventType, const std::function<bool(Event&)>& func)
		{
			if (m_Event.Ev.type == sdlEventType)
			{
				m_Event.bHandled |= func(m_Event);
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};
}