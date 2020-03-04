#ifndef DAY11_ROBOTINTERFACE_H
#define DAY11_ROBOTINTERFACE_H

class RobotInterface {
public:
    virtual long getCurrentColor() = 0;
    virtual void colorCurrentPanel(long color) = 0;
    virtual void move(long direction) = 0;
};


#endif //DAY11_ROBOTINTERFACE_H
