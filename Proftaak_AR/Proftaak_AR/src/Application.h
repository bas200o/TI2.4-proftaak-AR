#pragma once

#include <memory>
#include <thread>
#include <cmath>

#include <GL/glew.h>

#include "OpenGL/windowhandling/Window.h"
#include "OpenGL/windowhandling/Events.h"
#include "OpenGL/windowhandling/EventHandler.h"
#include "OpenGL/Renderer/ui/text/Font.h"
#include "OpenGL/Renderer/ui/text/Text.h"
#include "OpenGL/Renderer/Renderer.h"
#include "OpenGL/Renderer/RawModel.h"
#include "OpenGL/Renderer/Camera.h"
#include "OpenGL/utility/modelloader/OBJModelLoader.h"

#include "gamelogic/gameobjects/Kart.h"
#include "gamelogic/gameobjects/Track.h"

#include "Vision/VisionCamera.h"

namespace GameLogic
{
	class Time
	{
	public:
		unsigned int hours;
		unsigned int minutes;
		unsigned int seconds;

		float secondsCounter;

		Time(unsigned int hours, unsigned int minutes, unsigned int seconds)
			: hours(hours), minutes(minutes), seconds(seconds), secondsCounter(0.0f) {}
		Time()
			: hours(0), minutes(0), seconds(0), secondsCounter(0.0f) {}

		void reset()
		{
			this->hours = 0;
			this->minutes = 0;
			this->seconds = 0;
			this->secondsCounter = 0.0f;
		}

		void addSeconds(const float seconds)
		{
			this->secondsCounter += seconds;
			if (this->secondsCounter >= 1.0f)
			{
				float secondsCounterModulo = fmod(this->secondsCounter, 1.0f);
				unsigned int secondsAmmount = (this->secondsCounter - secondsCounterModulo);
				this->seconds += secondsAmmount;
				this->secondsCounter = secondsCounterModulo;
				if (this->seconds >= 60)
				{
					unsigned int secondsModulo = (this->seconds % 60);
					unsigned int minutesAmmount = ((secondsAmmount - secondsModulo) / 60);
					this->minutes += minutesAmmount + 1;
					this->seconds = secondsModulo;
					if (this->minutes >= 60)
					{
						unsigned int minutesModulo = (this->minutes % 60);
						unsigned int hoursAmmount = ((minutesAmmount - (minutesAmmount % 60)) / 60);
						this->hours += hoursAmmount + 1;
						this->minutes = minutesModulo;
						if (this->hours >= 24)
						{
							unsigned int hoursModulo = (this->hours % 24);
							this->hours = hoursModulo;
						}
					}
				}
			}
		}

		std::string getString()
		{
			std::stringstream stringStream;
			stringStream << std::to_string(this->hours) << ":" << std::to_string(this->minutes) << ":" << std::to_string(this->seconds);
			return stringStream.str();
		}
	};

	class Application : public OpenGL::EventHandler, public Vision::VisionCameraCallbackHandler
	{
	private:
		OpenGL::Window window;
		OpenGL::Camera camera;

		std::unique_ptr<GameLogic::Kart> kart;
		std::unique_ptr<OpenGL::Text> timeText;
		std::unique_ptr<OpenGL::Text> speedText;
		Vision::VisionCamera visionCamera;

		Time time;

	public:
		Application();

		bool run();

		virtual void handleEvent(OpenGL::Event& event) override;
		virtual void setAngle(float angle) override;
	};
}