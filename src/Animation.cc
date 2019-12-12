#include "Animation.h"

Animation::Animation() {}

Animation::Animation(unsigned f_index, unsigned f_numFrames, unsigned f_animationSpeed) :
    m_index(f_index), m_numFrames(f_numFrames), m_animationSpeed(f_animationSpeed) {}
