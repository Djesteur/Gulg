#include "Game/Camera.hpp"

Camera::Camera():
	sf::View{sf::Vector2f{0, 0}, sf::Vector2f{1280, 720}},
	m_zoomInFactor{1.25f},
	m_zoomOutFactor{0.8f},
	m_currentZoom{1.f},
	m_zoomNumber{0},
	m_isCurrentlyMoving{false},
	m_holdPosition{sf::Mouse::getPosition()} {}

void Camera::applyEvents(const sf::Event &currentEvent) {

	if(currentEvent.type == sf::Event::MouseWheelScrolled) {

		if(currentEvent.mouseWheelScroll.delta > 0) { 

			zoom(m_zoomOutFactor); 
			m_zoomNumber--;
			m_currentZoom *= m_zoomOutFactor;
		}

		if(currentEvent.mouseWheelScroll.delta < 0) { 

			zoom(m_zoomInFactor); 
			m_zoomNumber++;
			m_currentZoom *= m_zoomInFactor;
		}
	}

	if(currentEvent.type == sf::Event::MouseButtonPressed) {

		if(currentEvent.mouseButton.button == sf::Mouse::Right) { 

			m_isCurrentlyMoving = true; 
			m_holdPosition = sf::Mouse::getPosition(); 
		} 
	}

	if(currentEvent.type == sf::Event::MouseButtonReleased) {

		if(currentEvent.mouseButton.button == sf::Mouse::Right) { m_isCurrentlyMoving = false; } 
	}

	if(m_isCurrentlyMoving) {

		sf::Vector2i newMousePosition{sf::Mouse::getPosition()};
		move((m_holdPosition.x - newMousePosition.x)*m_currentZoom, 
			 (m_holdPosition.y - newMousePosition.y)*m_currentZoom);
		m_holdPosition = newMousePosition;
	}
}

void Camera::resetZoom() {

	while(m_zoomNumber > 0) {

		m_zoomNumber--;
		zoom(m_zoomOutFactor);
		m_currentZoom *= m_zoomOutFactor;
	}

	while(m_zoomNumber < 0) {

		m_zoomNumber++;
		zoom(m_zoomInFactor);
		m_currentZoom *= m_zoomInFactor;
	}
}

void Camera::setZoomFactor(const float zoomFactor) {

	m_zoomInFactor = zoomFactor;
	m_zoomOutFactor = 1.f/m_zoomInFactor;
}

float Camera::getCurrentZoom() const { return m_currentZoom; }