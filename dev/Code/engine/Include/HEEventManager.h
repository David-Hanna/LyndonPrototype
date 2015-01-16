#pragma once
//--------------------------------------------------------------------------------------------------------------------------------------
// EventManager
//
// Game Event System
//--------------------------------------------------------------------------------------------------------------------------------------

#include <assert.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include <list>

#include "..\Utilities\HEMisc.h"

namespace HE
{
	enum eEventType
	{
		eEventType_Generic = 0,
		eEventType_Collision,
		eEventType_ButtonPressed,
		eEventType_ButtonHeld,
		eEventType_ButtonReleased
	};

	// needs to be rewritten to not allow changing the value of the data at eventData.
	class EventData
	{
	protected:
		unsigned int senderID;
		eEventType eventType;
		std::string eventData;

	public:
		EventData(unsigned int id, eEventType type, std::string data);	
		EventData(const EventData& other);
		EventData& operator=(const EventData& otherEventData);

		unsigned int GetSenderID() const { return senderID; }
		eEventType GetType() const { return eventType; }
		std::string GetData() const { return std::string(eventData); }
	};

	// inherit this class before registering as an event listener
	class iEventListener
	{
	public:
		virtual void OnEvent(const EventData& eventData) = 0;
	};

	class EventManager : private Uncopyable
	{
	private:
		std::unordered_map<eEventType, std::list<iEventListener*>> listeners;

	public:
		~EventManager() {}

		static EventManager& instance() { static EventManager* instance = new EventManager; return *instance; }

		void RegisterForEvent(iEventListener* listener, eEventType eventType) { listeners[eventType].push_back(listener); }
		void UnregisterForEvent(iEventListener* listener, eEventType eventType) { listeners[eventType].remove(listener); }

		void FireEvent(const EventData& eventData);

	private:
		EventManager() {}
	};


	// SAMPLE USAGE CLASS
	class EventUser : public iEventListener
	{
	public:
		virtual void OnEvent(const EventData& eventData) override;
	};
}