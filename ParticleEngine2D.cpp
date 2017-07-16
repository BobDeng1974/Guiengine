#include "ParticleEngine2D.h"


namespace Guiengine {
	ParticleEngine2D::ParticleEngine2D() {
		///Empty
	}

	ParticleEngine2D::~ParticleEngine2D(){
		for (unsigned short i = 0; i < m_batches.size(); i++) {
			delete (m_batches[i]);
		}
		m_batches.clear();
	}

	void ParticleEngine2D::addParticleBatch(ParticleBatch2D* particleBatch) {
		m_batches.push_back(particleBatch);
	}

	void ParticleEngine2D::update(float deltaTime) {
		for (unsigned short i = 0; i < m_batches.size(); i++) {
			m_batches[i]->update(deltaTime);
		}
	}

	void ParticleEngine2D::draw(SpriteBatch* spriteBatch) {
		for (unsigned short i = 0; i < m_batches.size();i++) {
			spriteBatch->begin();
			m_batches[i]->draw(spriteBatch);
			spriteBatch->end();
			spriteBatch->renderBatch();
		}
		
	}

}