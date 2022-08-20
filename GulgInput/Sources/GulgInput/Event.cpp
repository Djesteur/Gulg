#include "GulgInput/Event.hpp"

namespace Gg {

namespace Input {


bool operator==(const Event &firstEvent, const Event &secondEvent) { 

	return firstEvent.handledInput == secondEvent.handledInput 
	&&     firstEvent.eventType == secondEvent.eventType; 
}


sf::Keyboard::Key getSFMLFromGulgKey(const HandledInput &handledInput) {

	switch(handledInput) {

		case HandledInput::Unknown:
			return sf::Keyboard::Unknown;

		case HandledInput::A:
			return sf::Keyboard::A;

		case HandledInput::B:
			return sf::Keyboard::B;

		case HandledInput::C:
			return sf::Keyboard::C;

		case HandledInput::D:
			return sf::Keyboard::D;

		case HandledInput::E:
			return sf::Keyboard::E;

		case HandledInput::F:
			return sf::Keyboard::F;

		case HandledInput::G:
			return sf::Keyboard::G;

		case HandledInput::H:
			return sf::Keyboard::H;

		case HandledInput::I:
			return sf::Keyboard::I;

		case HandledInput::J:
			return sf::Keyboard::J;

		case HandledInput::K:
			return sf::Keyboard::K;

		case HandledInput::L:
			return sf::Keyboard::L;

		case HandledInput::M:
			return sf::Keyboard::M;

		case HandledInput::N:
			return sf::Keyboard::N;

		case HandledInput::O:
			return sf::Keyboard::O;

		case HandledInput::P:
			return sf::Keyboard::P;

		case HandledInput::Q:
			return sf::Keyboard::Q;

		case HandledInput::R:
			return sf::Keyboard::R;

		case HandledInput::S:
			return sf::Keyboard::S;

		case HandledInput::T:
			return sf::Keyboard::T;

		case HandledInput::U:
			return sf::Keyboard::U;

		case HandledInput::V:
			return sf::Keyboard::V;

		case HandledInput::W:
			return sf::Keyboard::W;

		case HandledInput::X:
			return sf::Keyboard::X;

		case HandledInput::Y:
			return sf::Keyboard::Y;

		case HandledInput::Z:
			return sf::Keyboard::Z;

		case HandledInput::Num0:
			return sf::Keyboard::Num0;

		case HandledInput::Num1:
			return sf::Keyboard::Num1;

		case HandledInput::Num2:
			return sf::Keyboard::Num2;

		case HandledInput::Num3:
			return sf::Keyboard::Num3;

		case HandledInput::Num4:
			return sf::Keyboard::Num4;

		case HandledInput::Num5:
			return sf::Keyboard::Num5;

		case HandledInput::Num6:
			return sf::Keyboard::Num6;

		case HandledInput::Num7:
			return sf::Keyboard::Num7;

		case HandledInput::Num8:
			return sf::Keyboard::Num8;

		case HandledInput::Num9:
			return sf::Keyboard::Num9;

		case HandledInput::Escape:
			return sf::Keyboard::Escape;

		case HandledInput::LeftControl:
			return sf::Keyboard::LControl;

		case HandledInput::LeftShift:
			return sf::Keyboard::LShift;

		case HandledInput::LeftAlt:
			return sf::Keyboard::LAlt;

		case HandledInput::LeftSystem:
			return sf::Keyboard::LSystem;

		case HandledInput::RightControl:
			return sf::Keyboard::RControl;

		case HandledInput::RightShift:
			return sf::Keyboard::RShift;

		case HandledInput::RightAlt:
			return sf::Keyboard::RAlt;

		case HandledInput::RightSystem:
			return sf::Keyboard::RSystem;

		case HandledInput::Menu:
			return sf::Keyboard::Menu;

		case HandledInput::LeftBracket:
			return sf::Keyboard::LBracket;

		case HandledInput::RightBracket:
			return sf::Keyboard::RBracket;

		case HandledInput::Semicolon:
			return sf::Keyboard::Semicolon;

		case HandledInput::Comma:
			return sf::Keyboard::Comma;

		case HandledInput::Period:
			return sf::Keyboard::Period;

		case HandledInput::Quote:
			return sf::Keyboard::Quote;

		case HandledInput::Slash:
			return sf::Keyboard::Slash;

		case HandledInput::Backslash:
			return sf::Keyboard::Backslash;

		case HandledInput::Tilde:
			return sf::Keyboard::Tilde;

		case HandledInput::Equal:
			return sf::Keyboard::Equal;

		case HandledInput::Hyphen:
			return sf::Keyboard::Hyphen;

		case HandledInput::Space:
			return sf::Keyboard::Space;

		case HandledInput::Enter:
			return sf::Keyboard::Enter;

		case HandledInput::Backspace:
			return sf::Keyboard::Backspace;

		case HandledInput::Tab:
			return sf::Keyboard::Tab;

		case HandledInput::PageUp:
			return sf::Keyboard::PageUp;

		case HandledInput::PageDown:
			return sf::Keyboard::PageDown;

		case HandledInput::End:
			return sf::Keyboard::End;

		case HandledInput::Home:
			return sf::Keyboard::Home;

		case HandledInput::Insert:
			return sf::Keyboard::Insert;

		case HandledInput::Delete:
			return sf::Keyboard::Delete;

		case HandledInput::Add:
			return sf::Keyboard::Add;

		case HandledInput::Subtract:
			return sf::Keyboard::Subtract;

		case HandledInput::Multiply:
			return sf::Keyboard::Multiply;

		case HandledInput::Divide:
			return sf::Keyboard::Divide;

		case HandledInput::Left:
			return sf::Keyboard::Left;

		case HandledInput::Right:
			return sf::Keyboard::Right;

		case HandledInput::Up:
			return sf::Keyboard::Up;

		case HandledInput::Down:
			return sf::Keyboard::Down;

		case HandledInput::Numpad0:
			return sf::Keyboard::Numpad0;

		case HandledInput::Numpad1:
			return sf::Keyboard::Numpad1;

		case HandledInput::Numpad2:
			return sf::Keyboard::Numpad2;

		case HandledInput::Numpad3:
			return sf::Keyboard::Numpad3;

		case HandledInput::Numpad4:
			return sf::Keyboard::Numpad4;

		case HandledInput::Numpad5:
			return sf::Keyboard::Numpad5;

		case HandledInput::Numpad6:
			return sf::Keyboard::Numpad6;

		case HandledInput::Numpad7:
			return sf::Keyboard::Numpad7;

		case HandledInput::Numpad8:
			return sf::Keyboard::Numpad8;

		case HandledInput::Numpad9:
			return sf::Keyboard::Numpad9;

		case HandledInput::F1:
			return sf::Keyboard::F1;

		case HandledInput::F2:
			return sf::Keyboard::F2;

		case HandledInput::F3:
			return sf::Keyboard::F3;

		case HandledInput::F4:
			return sf::Keyboard::F4;

		case HandledInput::F5:
			return sf::Keyboard::F5;

		case HandledInput::F6:
			return sf::Keyboard::F6;

		case HandledInput::F7:
			return sf::Keyboard::F7;

		case HandledInput::F8:
			return sf::Keyboard::F8;

		case HandledInput::F9:
			return sf::Keyboard::F9;

		case HandledInput::F10:
			return sf::Keyboard::F10;

		case HandledInput::F11:
			return sf::Keyboard::F11;

		case HandledInput::F12:
			return sf::Keyboard::F12;

		case HandledInput::F13:
			return sf::Keyboard::F13;

		case HandledInput::F14:
			return sf::Keyboard::F14;

		case HandledInput::F15 :
			return sf::Keyboard::F15;

		case HandledInput::Pause:
			return sf::Keyboard::Pause;

		default:
			return sf::Keyboard::Unknown;
	}

	return sf::Keyboard::Unknown;
}

HandledInput getGulgFromSFMLKey(const sf::Keyboard::Key &key) {

	switch(key) {

		case sf::Keyboard::Unknown:
			return HandledInput::Unknown;

		case sf::Keyboard::A:
			return HandledInput::A;

		case sf::Keyboard::B:
			return HandledInput::B;

		case sf::Keyboard::C:
			return HandledInput::C;

		case sf::Keyboard::D:
			return HandledInput::D;

		case sf::Keyboard::E:
			return HandledInput::E;

		case sf::Keyboard::F:
			return HandledInput::F;

		case sf::Keyboard::G:
			return HandledInput::G;

		case sf::Keyboard::H:
			return HandledInput::H;

		case sf::Keyboard::I:
			return HandledInput::I;

		case sf::Keyboard::J:
			return HandledInput::J;

		case sf::Keyboard::K:
			return HandledInput::K;

		case sf::Keyboard::L:
			return HandledInput::L;

		case sf::Keyboard::M:
			return HandledInput::M;

		case sf::Keyboard::N:
			return HandledInput::N;

		case sf::Keyboard::O:
			return HandledInput::O;

		case sf::Keyboard::P:
			return HandledInput::P;

		case sf::Keyboard::Q:
			return HandledInput::Q;

		case sf::Keyboard::R:
			return HandledInput::R;

		case sf::Keyboard::S:
			return HandledInput::S;

		case sf::Keyboard::T:
			return HandledInput::T;

		case sf::Keyboard::U:
			return HandledInput::U;

		case sf::Keyboard::V:
			return HandledInput::V;

		case sf::Keyboard::W:
			return HandledInput::W;

		case sf::Keyboard::X:
			return HandledInput::X;

		case sf::Keyboard::Y:
			return HandledInput::Y;

		case sf::Keyboard::Z:
			return HandledInput::Z;

		case sf::Keyboard::Num0:
			return HandledInput::Num0;

		case sf::Keyboard::Num1:
			return HandledInput::Num1;

		case sf::Keyboard::Num2:
			return HandledInput::Num2;

		case sf::Keyboard::Num3:
			return HandledInput::Num3;

		case sf::Keyboard::Num4:
			return HandledInput::Num4;

		case sf::Keyboard::Num5:
			return HandledInput::Num5;

		case sf::Keyboard::Num6:
			return HandledInput::Num6;

		case sf::Keyboard::Num7:
			return HandledInput::Num7;

		case sf::Keyboard::Num8:
			return HandledInput::Num8;

		case sf::Keyboard::Num9:
			return HandledInput::Num9;

		case sf::Keyboard::Escape:
			return HandledInput::Escape;

		case sf::Keyboard::LControl:
			return HandledInput::LeftControl;

		case sf::Keyboard::LShift:
			return HandledInput::LeftShift;

		case sf::Keyboard::LAlt:
			return HandledInput::LeftAlt;

		case sf::Keyboard::LSystem:
			return HandledInput::LeftSystem;

		case sf::Keyboard::RControl:
			return HandledInput::RightControl;

		case sf::Keyboard::RShift:
			return HandledInput::RightShift;

		case sf::Keyboard::RAlt:
			return HandledInput::RightAlt;

		case sf::Keyboard::RSystem:
			return HandledInput::RightSystem;

		case sf::Keyboard::Menu:
			return HandledInput::Menu;

		case sf::Keyboard::LBracket:
			return HandledInput::LeftBracket;

		case sf::Keyboard::RBracket:
			return HandledInput::RightBracket;

		case sf::Keyboard::Semicolon:
			return HandledInput::Semicolon;

		case sf::Keyboard::Comma:
			return HandledInput::Comma;

		case sf::Keyboard::Period:
			return HandledInput::Period;

		case sf::Keyboard::Quote:
			return HandledInput::Quote;

		case sf::Keyboard::Slash:
			return HandledInput::Slash;

		case sf::Keyboard::Backslash:
			return HandledInput::Backslash;

		case sf::Keyboard::Tilde:
			return HandledInput::Tilde;

		case sf::Keyboard::Equal:
			return HandledInput::Equal;

		case sf::Keyboard::Hyphen:
			return HandledInput::Hyphen;

		case sf::Keyboard::Space:
			return HandledInput::Space;

		case sf::Keyboard::Enter:
			return HandledInput::Enter;

		case sf::Keyboard::Backspace:
			return HandledInput::Backspace;

		case sf::Keyboard::Tab:
			return HandledInput::Tab;

		case sf::Keyboard::PageUp:
			return HandledInput::PageUp;

		case sf::Keyboard::PageDown:
			return HandledInput::PageDown;

		case sf::Keyboard::End:
			return HandledInput::End;

		case sf::Keyboard::Home:
			return HandledInput::Home;

		case sf::Keyboard::Insert:
			return HandledInput::Insert;

		case sf::Keyboard::Delete:
			return HandledInput::Delete;

		case sf::Keyboard::Add:
			return HandledInput::Add;

		case sf::Keyboard::Subtract:
			return HandledInput::Subtract;

		case sf::Keyboard::Multiply:
			return HandledInput::Multiply;

		case sf::Keyboard::Divide:
			return HandledInput::Divide;

		case sf::Keyboard::Left:
			return HandledInput::Left;

		case sf::Keyboard::Right:
			return HandledInput::Right;

		case sf::Keyboard::Up:
			return HandledInput::Up;

		case sf::Keyboard::Down:
			return HandledInput::Down;

		case sf::Keyboard::Numpad0:
			return HandledInput::Numpad0;

		case sf::Keyboard::Numpad1:
			return HandledInput::Numpad1;

		case sf::Keyboard::Numpad2:
			return HandledInput::Numpad2;

		case sf::Keyboard::Numpad3:
			return HandledInput::Numpad3;

		case sf::Keyboard::Numpad4:
			return HandledInput::Numpad4;

		case sf::Keyboard::Numpad5:
			return HandledInput::Numpad5;

		case sf::Keyboard::Numpad6:
			return HandledInput::Numpad6;

		case sf::Keyboard::Numpad7:
			return HandledInput::Numpad7;

		case sf::Keyboard::Numpad8:
			return HandledInput::Numpad8;

		case sf::Keyboard::Numpad9:
			return HandledInput::Numpad9;

		case sf::Keyboard::F1:
			return HandledInput::F1;

		case sf::Keyboard::F2:
			return HandledInput::F2;

		case sf::Keyboard::F3:
			return HandledInput::F3;

		case sf::Keyboard::F4:
			return HandledInput::F4;

		case sf::Keyboard::F5:
			return HandledInput::F5;

		case sf::Keyboard::F6:
			return HandledInput::F6;

		case sf::Keyboard::F7:
			return HandledInput::F7;

		case sf::Keyboard::F8:
			return HandledInput::F8;

		case sf::Keyboard::F9:
			return HandledInput::F9;

		case sf::Keyboard::F10:
			return HandledInput::F10;

		case sf::Keyboard::F11:
			return HandledInput::F11;

		case sf::Keyboard::F12:
			return HandledInput::F12;

		case sf::Keyboard::F13:
			return HandledInput::F13;

		case sf::Keyboard::F14:
			return HandledInput::F14;

		case sf::Keyboard::F15 :
			return HandledInput::F15;

		case sf::Keyboard::Pause:
			return HandledInput::Pause;

		default:
			return HandledInput::Unknown;
	}

	return HandledInput::Unknown;

}


}
}