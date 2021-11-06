#include <Servo.h>

class lock {
    private:
        Servo bolt;
        bool lockState;
        const int LOCKED_ANGLE = 90;
        const int UNLOCKED_ANGLE = 0;

    public:
        bool getLockState() {
            return lockState;
        }

        void lockDoor() {
            bolt.write(LOCKED_ANGLE);
        }
        void unlockDoor() {
            bolt.write(UNLOCKED_ANGLE);
        }
};