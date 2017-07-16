#include "ParticleBatch2D.h"

namespace Guiengine {
	ParticleBatch2D::ParticleBatch2D()
	{
		///Empty
	}

	Particle2D::Particle2D() {}
	Particle2D::~Particle2D() {}


	ParticleBatch2D::~ParticleBatch2D()
	{
		delete[] m_particles;
	}

	///Init the particleEngine
	void ParticleBatch2D::init(int maxParticles, float decayRate, GLTexture texture, std::function<void(Particle2D&, float)> updateFunc /*= updateParticle*/) {
		m_decayRate = decayRate;
		m_maxParticles = maxParticles;
		m_particles = new Particle2D[m_maxParticles];
		m_texture = texture;
		m_updateFunc = updateFunc;
	}

	///Update all particles
	void ParticleBatch2D::update(float deltaTime) {
		for (int i = 0; i < m_maxParticles; i++) {
			//Check if is active
			if (m_particles[i].life > 0.0f) {
				m_updateFunc(m_particles[i],deltaTime);
				m_particles[i].life -= m_decayRate* deltaTime;///<Subtract life
			}
		}
	}

	///Draw all particles
	void ParticleBatch2D::draw(SpriteBatch* spriteBatch) {
		glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
		for (int i = 0; i < m_maxParticles; i++) {
			//Check if is active
			if (m_particles[i].life > 0.0f) {
				glm::vec4 destRect = glm::vec4(m_particles[i].position.x, m_particles[i].position.y, m_particles[i].size, m_particles[i].size);
				spriteBatch->draw(destRect, uvRect, m_texture.id, 0.0f, m_particles[i].color);
			}
		}
	}

	///Loop for particles looking the first position which is inactive
	int ParticleBatch2D::findFreeParticle() {
		for (unsigned short i = m_lastFree; i < m_maxParticles; i++) {
			if (m_particles[i].life <= 0.0f) {
				m_lastFree = i;
				return i;
			}
		}
		for (unsigned short i = 0; i < m_lastFree; i++) {
			if (m_particles[i].life <= 0.0f) {
				m_lastFree = i;
				return i;
			}
		}
		//No particles are free override the first particle
		return 0;
	}

	void ParticleBatch2D::addParticle(glm::vec2 position,
		const ColorRGBA& color,
		glm::vec2 speed, float width) {
		int particleindex = findFreeParticle();
		m_particles[particleindex].life = 1.0f;
		m_particles[particleindex].position = position;
		m_particles[particleindex].color = color;
		m_particles[particleindex].speed = speed;
		m_particles[particleindex].size = width;
	}	
}


