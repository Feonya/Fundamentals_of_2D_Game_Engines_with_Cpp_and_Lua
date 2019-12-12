#ifndef ANIMATION_H
#define ANIMATION_H

class Animation {
  public:
    unsigned m_index;
    unsigned m_numFrames;
    unsigned m_animationSpeed;

    Animation();
    Animation(unsigned f_index, unsigned f_numFrames, unsigned f_animationSpeed);
};

#endif
