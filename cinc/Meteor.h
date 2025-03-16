#include "Entity.h"

class Meteor : public Entity
{
public:
    Meteor(Vec center, float angle, float turnSpeed, float speed, Color color, bool goingRight, Sprite::Type textureType);

    void render() override;
    void offScreen() override;
    void collisionLogic() override;
    void move() override;

private:
};
