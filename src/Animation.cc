#include "Animation.h"

Animation::Animation() {}

Animation::Animation(unsigned f_index, unsigned f_numFrames, unsigned f_animationSpeed) :
    index(f_index), numFrames(f_numFrames), animationSpeed(f_animationSpeed) {}
