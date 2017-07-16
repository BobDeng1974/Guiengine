#pragma once

#include "Vertex.h"
#include <vector>

#include "SpriteBatch.h"
#include "ParticleBatch2D.h"

namespace Guiengine {	
	

	class ParticleEngine2D
	{
	public:
		ParticleEngine2D();
		~ParticleEngine2D();

		///Afer adding a particle the engine becomes responsible of deallocate it.
		void addParticleBatch(ParticleBatch2D* particleBatch);

		void update(float deltaTime);

		void draw(SpriteBatch* spriteBatch);
		
	private:
		std::vector <ParticleBatch2D*> m_batches;
	};

}

