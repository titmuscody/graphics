#ifndef GRAPHIC_H
#define GRAPHIC_H


class Drawable {
    public:
    virtual void render(float) = 0;
};

class NullDrawable : public Drawable {
    public:
    void render(float time) {
    }
};

#endif
