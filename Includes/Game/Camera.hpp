#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/Graphics.hpp>

class Camera: public sf::View {

	public:

		Camera();

		void applyEvents(const sf::Event &currentEvent);


		void resetZoom();

		void setZoomFactor(const float zoomFactor);
		float getCurrentZoom() const;

	private:

		float m_zoomInFactor, m_zoomOutFactor, m_currentZoom;
		int m_zoomNumber;

		bool m_isCurrentlyMoving;
		sf::Vector2i m_holdPosition;
};

#endif