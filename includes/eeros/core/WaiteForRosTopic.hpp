
#include <string>
#include <ros/ros.h>

namespace eeros {
	namespace core {
		
		class WaitForRosTopicInterface {
		public:
			WaitForRosTopicInterface() {};
			virtual void waitForMessage();
		};
		
		template <typename tRosMsg>
		class WaitForRosTopic : public WaitForRosTopicInterface {
		public:
			WaitForRosTopic(std::string topic) : topic(topic) {};
			void waitForMessage() {
				ros::topic::waitForMessage<tRosMsg>(topic);
			}
			
			
		private:		
			
			std::string topic;
			
		};
		
	};
};