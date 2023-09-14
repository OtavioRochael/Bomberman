#include "Animator.hpp"

Animator::Animator(sf::Sprite& sprite) :sprite(sprite), currentTime(), currentAnimation(nullptr)
{
}

Animator::Animation& Animator::CreateAnimation(std::string const& name,
	std::string const& textureName, sf::Time const& duration, bool looping)
{
	animations.push_back(Animator::Animation(name, textureName, duration, looping));

	//if we dont have any other animations, use that as current animation
	if (currentAnimation == nullptr)
		SwitchAnimation(&animations.back());

	return animations.back();
}

void Animator::Update(sf::Time const& deltaTime)
{
	if (currentAnimation == nullptr) return;

	currentTime += deltaTime;

	//Obtem o frame da animação atual
	float scaledTime = (currentTime.asSeconds() / currentAnimation->duration.asSeconds());
	int numFrames = currentAnimation->framesVector.size();
	int currentFrame = static_cast<int>(scaledTime * numFrames);

	if (currentAnimation->looping) { //Se for marcada como looping, então calcula o frame correto
		currentFrame %= numFrames;
	}
	else if (currentFrame >= numFrames) {
		currentFrame = numFrames - 1; //Roda uma vez e trava na ultima na animação
	}

	//Seta o retangulo que irá cortar a imagem no frame correto
	sprite.setTextureRect(currentAnimation->framesVector[currentFrame]);
}

bool Animator::SwitchAnimation(std::string const& name)
{
	auto animation = FindAnimation(name);
	if (animation != nullptr) {
		SwitchAnimation(animation);
		return true;
	}

	return false;
}

std::string Animator::GetCurrentAnimationName() const
{
	if (currentAnimation != nullptr) {
		return currentAnimation->name;
	}

	//No animation, empty string.
	return "";
}

Animator::Animation* Animator::FindAnimation(std::string const& name)
{
	for (auto it = animations.begin(); it != animations.end(); ++it) {
		if (it->name == name) {
			return &*it;
		}
	}

	return nullptr;
}

void Animator::SwitchAnimation(Animator::Animation* animation)
{
	//Troca a texture da sprite
	if (animation != nullptr) {
		sprite.setTexture(AssetManager::GetTexture(animation->textureName));
	}

	currentAnimation = animation;
	currentTime = sf::Time::Zero;	//Reset time
}