#include "Components/Graphics/AnimationSet.hpp"

namespace Gg {

namespace Component {

bool AnimationSet::loadFromFile(GulgEngine &engine, const std::string path) {

	animations.clear();

	tinyxml2::XMLDocument configFile;
	tinyxml2::XMLError loadError{configFile.LoadFile(path.c_str())};
	if(loadError != 0) { throw std::runtime_error("Animation Set error: missing file \"" + path + "\"."); }

	tinyxml2::XMLElement *root{configFile.FirstChildElement("root")};
	if(root == nullptr) { throw std::runtime_error("Animation Set error: invalid file format \"" + path + "\", missing root."); }

	tinyxml2::XMLElement *setName{root->FirstChildElement("setName")};
	if(setName == nullptr) { throw std::runtime_error("Animation Set error: invalid file format \"" + path + "\", missing set name."); }

	tinyxml2::XMLElement *textureName{root->FirstChildElement("textureName")};
	if(textureName == nullptr) { throw std::runtime_error("Animation Set error: invalid file format \"" + path + "\", missing texture name."); }

	tinyxml2::XMLElement *texturePath{root->FirstChildElement("texturePath")};
	if(texturePath == nullptr) { throw std::runtime_error("Animation Set error: invalid file format \"" + path + "\", missing texture path."); }

	tinyxml2::XMLElement *center{root->FirstChildElement("center")};
	if(center == nullptr) { throw std::runtime_error("Animation Set error: invalid file format \"" + path + "\", missing center of animation."); }

	tinyxml2::XMLElement *centerXNode{center->FirstChildElement("x")};
	if(centerXNode == nullptr) { throw std::runtime_error("Center error: invalid file format \"" + path + "\", missing x."); }

	tinyxml2::XMLElement *centerYNode{center->FirstChildElement("y")};
	if(centerYNode == nullptr) { throw std::runtime_error("Center error: invalid file format \"" + path + "\", missing y."); }

	unsigned int centerX{0}, centerY{0};
	std::istringstream stringConverter{centerXNode->GetText()};

	stringConverter.str(centerXNode->GetText());
	stringConverter >> centerX;
	if(stringConverter.fail()) { throw std::runtime_error("Center error: invalid x format"); }

	stringConverter.clear();
	stringConverter.str(centerYNode->GetText());
	stringConverter >> centerY;
	if(stringConverter.fail()) { throw std::runtime_error("Center error: invalid y format"); }

	if(!engine.loadTexture(textureName->GetText(), texturePath->GetText())) {

		throw std::runtime_error("Animation Set error: can't load texture \"" + std::string{textureName->GetText()} + "\" with path \"" + std::string{texturePath->GetText()} + "\".");
	}

	name = setName->GetText();

	tinyxml2::XMLElement *currentAnimationInFile{root->FirstChildElement("animation")};
	if(currentAnimationInFile == nullptr) {  throw std::runtime_error("Animation Set error: no animation in set \"" + path + "\".");}

	while(currentAnimationInFile != nullptr) {

		animations.emplace_back(loadAnimationFromXML(currentAnimationInFile));
		currentAnimationInFile = currentAnimationInFile->NextSiblingElement("animation");
	}

	currentAnimation = animations.size() - 1;
	timerLimit = animations.back().timer;
	sprite.setTexture(*engine.getTexture(textureName->GetText()));
	sprite.setTextureRect(animations.back().frames[0]);
	sprite.setOrigin(centerX, centerY);

	return true;
}

Animation AnimationSet::loadAnimationFromXML(tinyxml2::XMLElement *currentAnimation) {

	tinyxml2::XMLElement *animationName{currentAnimation->FirstChildElement("animationName")};
	if(animationName == nullptr) { throw std::runtime_error("Animation error: invalid file format, missing animation name."); }

	tinyxml2::XMLElement *animationType{currentAnimation->FirstChildElement("animationType")};
	if(animationType == nullptr) { throw std::runtime_error("Animation error: invalid file format, missing animation type."); }

	tinyxml2::XMLElement *timer{currentAnimation->FirstChildElement("timer")};
	if(timer == nullptr) { throw std::runtime_error("Animation error: invalid file format, missing timer."); }

	tinyxml2::XMLElement *currentFrame{currentAnimation->FirstChildElement("frame")};
	if(currentFrame == nullptr) {  throw std::runtime_error("Animation error: no frame in animation.");}

	Animation newAnimation;

	newAnimation.name = animationName->GetText();
	if(animationType->GetText() == std::string{"Classic"}) { newAnimation.animationType = Animation::Type::Classic; }
	else if(animationType->GetText() == std::string{"NormalRepeat"}) { newAnimation.animationType = Animation::Type::NormalReapeat; }
	else if(animationType->GetText() == std::string{"ReverseRepeat"}) { newAnimation.animationType = Animation::Type::ReverseRepeat; }
	else { throw std::runtime_error("Animation error: invalid animation type."); }

	std::istringstream stringConverter{timer->GetText()};
	stringConverter >> newAnimation.timer;
	if(stringConverter.fail()) { throw std::runtime_error("Animation error: invalid timer format");}

	unsigned int x1{0}, y1{0}, x2{0}, y2{0};

	while(currentFrame != nullptr) {

		tinyxml2::XMLElement *frameX1{currentFrame->FirstChildElement("x1")};
		if(frameX1 == nullptr) { throw std::runtime_error("Frame error: invalid file format, missing x1."); }

		tinyxml2::XMLElement *frameY1{currentFrame->FirstChildElement("y1")};
		if(frameY1 == nullptr) { throw std::runtime_error("Frame error: invalid file format, missing y1."); }
		
		tinyxml2::XMLElement *frameX2{currentFrame->FirstChildElement("x2")};
		if(frameX2 == nullptr) { throw std::runtime_error("Frame error: invalid file format, missing x2."); }

		tinyxml2::XMLElement *frameY2{currentFrame->FirstChildElement("y2")};
		if(frameY2 == nullptr) { throw std::runtime_error("Frame error: invalid file format, missing y2."); }

		stringConverter.clear();
		stringConverter.str(frameX1->GetText());
		stringConverter >> x1;
		if(stringConverter.fail()) { throw std::runtime_error("Frame error: invalid x1 format"); }

		stringConverter.clear();
		stringConverter.str(frameY1->GetText());
		stringConverter >> y1;
		if(stringConverter.fail()) { throw std::runtime_error("Frame error: invalid y1 format"); }

		stringConverter.clear();
		stringConverter.str(frameX2->GetText());
		stringConverter >> x2;
		if(stringConverter.fail()) { throw std::runtime_error("Frame error: invalid x2 format"); }

		stringConverter.clear();
		stringConverter.str(frameY2->GetText());
		stringConverter >> y2;
		if(stringConverter.fail()) { throw std::runtime_error("Frame error: invalid y2 format"); }
	
		newAnimation.frames.emplace_back(x1, y1, x2, y2);
		currentFrame = currentFrame->NextSiblingElement("frame");
	}

	return newAnimation;
}

bool AnimationSet::changeAnimation(const std::string nextAnimation) {

	unsigned int correspondingName{0};
	bool foundName{false};

	for(size_t i{0}; i < animations.size(); i++) {

		if(nextAnimation == animations[i].name) {

			correspondingName = i;
			foundName = true;
		}
	}

	if(foundName) {

		currentAnimation = correspondingName;
		timerLimit = animations[correspondingName].timer;
		timer.reset();

		return true;
	}

	return false; 
}

bool AnimationSet::changeAnimation(const unsigned int nextAnimation) { 

	if(nextAnimation < animations.size()) {

		currentAnimation = nextAnimation;
		timerLimit = animations[nextAnimation].timer;
		timer.reset();

		return true;
	}

	return false; 
}

}}

//std::cout << configFile.ErrorIDToName(loadError) << std::endl;