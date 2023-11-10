#ifndef GantryControl_H
#define GantryControl_H

class GantryControl{
    private:

    public:
        float X_Max = 0.0;

        void XMove(float Distance);
        void Home();
};

#endif