#pragma once

namespace OpenGL
{
	class Event
	{
	public:
		enum EventType
		{
			WindowResizeEvent,
			MouseScrollEvent,
			MouseMovedEvent,
			MouseButtonPressedEvent,
			MouseButtonReleasedEvent,
			KeyPressedEvent,
			KeyReleasedEvent,
			KeyDownEvent
		};

	protected:
		EventType eventType;

	public:
		inline EventType getEventType() { return this->eventType; }
	};

	//WindowEvents
	class WindowResizeEvent : public Event
	{
	private:
		const int width;
		const int height;

	public:
		WindowResizeEvent(const float width, const float height)
			: width(width), height(height)
		{
			this->eventType = EventType::WindowResizeEvent;
		}
		~WindowResizeEvent() {}

		inline const float getWidth() { return this->width; }
		inline const float getHeight() { return this->height; }
	};

	//MouseEvents
	class MouseScrollEvent : public Event
	{
	private:
		const float yOffset;

	public:
		MouseScrollEvent(const float yOffset)
			: yOffset(yOffset)
		{
			this->eventType = EventType::MouseScrollEvent;
		}
		~MouseScrollEvent() {}

		inline const float getYOffset() { return this->yOffset; }
	};

	class MouseMovedEvent : public Event
	{
	private:
		const float xOffset;
		const float yOffset;

	public:
		MouseMovedEvent(const float xOffset, const float yOffset)
			: xOffset(xOffset), yOffset(yOffset)
		{
			this->eventType = EventType::MouseMovedEvent;
		}
		~MouseMovedEvent() {}

		inline const float getXOffset() { return this->xOffset; }
		inline const float getYOffset() { return this->yOffset; }
	};

	class MouseButtonPressedEvent : public Event
	{
	private:
		const int button;

	public:
		MouseButtonPressedEvent(const int button)
			: button(button)
		{
			this->eventType = EventType::MouseButtonPressedEvent;
		}
		~MouseButtonPressedEvent() {}

		inline const int getButton() { return this->button; }
	};

	class MouseButtonReleasedEvent : public Event
	{
	private:
		const int button;

	public:
		MouseButtonReleasedEvent(const int button)
			: button(button)
		{
			this->eventType = EventType::MouseButtonReleasedEvent;
		}
		~MouseButtonReleasedEvent() {}

		inline const int getButton() { return this->button; }
	};

	class KeyPressedEvent : public Event
	{
	private:
		const int key;

	public:
		KeyPressedEvent(const int key)
			: key(key)
		{
			this->eventType = EventType::KeyPressedEvent;
		}
		~KeyPressedEvent() {}

		inline const int getKey() { return this->key; }
	};

	class KeyReleasedEvent : public Event
	{
	private:
		const int key;

	public:
		KeyReleasedEvent(const int key)
			: key(key)
		{
			this->eventType = EventType::KeyReleasedEvent;
		}
		~KeyReleasedEvent() {}

		inline const int getKey() { return this->key; }
	};
}