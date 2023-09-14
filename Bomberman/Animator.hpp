#pragma once

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "AssetManager.hpp"

#include <vector>
#include <list>
#include <string>

class Animator {
public:
	struct Animation
	{
		std::string name;
		std::string textureName;
		std::vector<sf::IntRect> framesVector;
		sf::Time duration;
		bool looping;

		Animation(std::string const& name, std::string const& textureName, sf::Time const& duration, bool looping) :
			name(name), textureName(textureName), duration(duration), looping(looping) {}

		void AddFrames(sf::Vector2i const& starFrom, sf::Vector2i const& frameSize, unsigned int frames) {
			sf::Vector2i current = starFrom;

			for (unsigned int i = 0; i < frames; i++) {
				//Adiciona o frame atual passando a posição e o tamanho
				framesVector.push_back(sf::IntRect(current.x, current.y, frameSize.x, frameSize.y));

				//Avança o proximo frame
				current.x += frameSize.x;
			}
		}
	};

	Animator(sf::Sprite& sprite);

	Animator::Animation& CreateAnimation(std::string const& name, std::string const& textureName,
		sf::Time const& duration, bool looping);

	void Update(sf::Time const& deltaTime);

	//Retorna se a troca de animações foi bem sucedida
	bool SwitchAnimation(std::string const& name);

	//Acessor
	std::string GetCurrentAnimationName() const;

private:
	sf::Sprite& sprite;
	sf::Time currentTime;
	std::list<Animator::Animation> animations;
	Animator::Animation* currentAnimation;

	//Retorna a animação do nome passado por parametro
	//Retorna nulo se a animação nao for encontrada
	Animator::Animation* FindAnimation(std::string const& name);

	void SwitchAnimation(Animator::Animation* animation);

};