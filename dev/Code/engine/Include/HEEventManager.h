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
		size_t size;
		char* eventData;

	public:
		EventData(const size_t sizeInBytes, const char* data);
		EventData(const EventData& other);

		virtual ~EventData() { size = 0; SAFE_DELETE_ARRAY(eventData); }

		size_t GetSize() const { return size; }

		const char operator[](unsigned int index) const { return eventData[index]; }

	private:
		void Init(const size_t sizeInBytes) { size = sizeInBytes; eventData = new char[size]; }
		EventData& operator=(const EventData&);
	};

	// inherit this class before registering as an event listener
	class iEventListener
	{
	public:
		virtual void OnEvent(const eEventType eventType, const EventData& eventData) = 0;
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

		void FireEvent(const eEventType eventType, const EventData& eventData);

	private:
		EventManager() {}
	};


	// SAMPLE USAGE CLASS
	class EventUser : public iEventListener
	{
	public:
		virtual void OnEvent(const eEventType eventType, const EventData& eventData) override;
	};
}