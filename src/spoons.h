#ifndef SPOONS_H
#define SPOONS_H

class Spoons {
    public:
        Spoons(int num_players);
        void takeSpoon();
        bool takeUserSpoon();
        int getNumSpoons();
        
    
    private:
        int number;
        int taken;
};

#endif