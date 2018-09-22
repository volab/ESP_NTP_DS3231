#ifndef ERRLED_H
#define ERRLED_H




class ErrLED{
    public:
        void begin();
        void error();
        void ok();
        void warning();
        ErrLED(int r, int g, int b){ _redPin= r; _greenPin = g; _bleuPin = b; _status = 0 ;};
        void on();
        void off();
        void test();
        
    private:
        int _redPin;
        int _greenPin;
        int _bleuPin;
        int _status;
};
#endif