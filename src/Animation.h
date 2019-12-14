#ifndef ANIMATION_H
#define ANIMATION_H

class Animation {
  public:
    unsigned index;
    unsigned numFrames;
    unsigned animationSpeed;

    Animation();
    Animation(unsigned f_index, unsigned f_numFrames, unsigned f_animationSpeed);
};

#endif
