#ifndef ORG_EEROS_SAFETY_SAFETYLEVEL_HPP_
#define ORG_EEROS_SAFETY_SAFETYLEVEL_HPP_

#include <stdint.h>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <eeros/safety/InputAction.hpp>
#include <eeros/safety/OutputAction.hpp>

namespace eeros {
	namespace safety {

		class SafetyContext;
		class SafetySystem;

		enum EventType { kPrivateEvent, kPublicEvent };
		
		class SafetyEvent {
			friend class SafetyLevel;
		public:
			SafetyEvent(std::string description);
			virtual ~SafetyEvent();
			std::string getDescription();
		private:
			std::string description;
			uint32_t id;
		};

		
		class SafetyLevel {
			friend class SafetySystem;
			friend class SafetyProperties;
		public:
			SafetyLevel(std::string description);
			virtual ~SafetyLevel();
			std::string getDescription();
			SafetyLevel* getDestLevelForEvent(SafetyEvent event, bool privateEventOk = false);
			void addEvent(SafetyEvent event, SafetyLevel& nextLevel, EventType type = kPrivateEvent);
			void setInputAction(InputAction* action); // TODO rename to add...
			void setInputActions(std::vector<InputAction*> actionList);
			void setOutputAction(OutputAction* action); // TODO rename to add...
			void setOutputActions(std::vector<OutputAction*> actionList);
			void setLevelAction(std::function<void (SafetyContext* context)> action);
//			SafetyLevel& operator<(const SafetyLevel&);
		private:
			std::function<void (SafetyContext*)> action;
			int32_t id;
			std::string description;
			std::map<uint32_t, std::pair<SafetyLevel*, EventType>> transitions;
			std::vector<InputAction*> inputAction;
			std::vector<OutputAction*> outputAction;
		};

	};
};

#endif // ORG_EEROS_SAFETY_SAFETYLEVEL_HPP_
