#pragma once

#include <functional>
#include <glm\glm.hpp>
#include "SpriteBatch.h"
#include "GLTexture.h"


namespace Guiengine {
	
	class Particle2D {
	public:
		friend class ParticleBatch2D;
		Particle2D();
		~Particle2D();
		glm::vec2 position= glm::vec2(0, 0);
		glm::vec2 speed = glm::vec2(0, 0);
		ColorRGBA color;
		float life = 0.0f;
		float size = 0.0f;
	};
	
	inline void updateParticle(Particle2D& particle, float deltaTime) {
		//Update one particle
		particle.position += particle.speed * deltaTime;
	}

	class ParticleBatch2D
	{
	public:
		ParticleBatch2D();
		~ParticleBatch2D();

		void init(int maxParticles, 
					float decayRate, 
					GLTexture texture,
					std::function<void(Particle2D&, float)> updateFunc = updateParticle);

		void addParticle(glm::vec2 position,
						const ColorRGBA& color,
						glm::vec2 speed, float width);
		
		void update(float deltaTime);

		void draw(SpriteBatch *spriteBatch);

		void changeTexture(GLTexture newTexture) { this->m_texture = newTexture; }

	private:
		int findFreeParticle();

		float m_decayRate = 0.1f;///<Time that particle reduces its life
		Particle2D* m_particles = nullptr;///<Array frendly cache of Particles
		int m_maxParticles = 0;///<Will be our array's sizes
		int m_lastFree = 0;///<The last freee position
		GLTexture m_texture;///<Texture of particles
		std::function<void(Particle2D&, float)> m_updateFunc;///<Pointer to update function
	};
}


