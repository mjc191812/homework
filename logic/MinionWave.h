#ifndef MINION_WAVE_H
#define MINION_WAVE_H

#include <queue>

namespace tower_defense {
    class MinionWave;
}

#include "../logic/Minion.h"

namespace tower_defense {
	/// class for wave of minions
	class MinionWave {
	public:
		/// creates new wave with given time between minion spawns
		/// minion objects must be allocated with new keyword
		MinionWave(const std::queue<Minion*>& minions, const int timeBetweenMinions);
		MinionWave(const MinionWave& wave);
		~MinionWave();

		/// returns if the last minion was already returned
		bool finished() const;

		/// returns minions in wave
		std::queue<Minion*> getMinions() const;

        /// returns time to next minion
        int getTimeToNextMinion() const;

        /// returns time between minions
		int getTimeBetweenMinions() const;

		/// refreshes wave
		/// returns pointer to BASE of minion that is to be spawned
		/// or nullptr if none
		Minion* refresh();
	private:
		std::queue<Minion*> minions;
		int timeToNext;
		int timeBetweenMinions;
	};
}

#endif