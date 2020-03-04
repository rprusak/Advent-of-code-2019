#ifndef DAY11_ROBOTINTERFACE_H
#define DAY11_ROBOTINTERFACE_H

class RobotInterface {
public:
    virtual void setX(long x) = 0;
    virtual void setY(long y) = 0;
    virtual void setTileId(long id) = 0;
    virtual void draw() = 0;
    virtual long getInput() = 0;
};


#endif //DAY11_ROBOTINTERFACE_H
