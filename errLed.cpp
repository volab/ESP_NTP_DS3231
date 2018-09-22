#include <Arduino.h>
#include "errLed.h"


void ErrLED::begin(){
    pinMode( _redPin, OUTPUT );
    digitalWrite( _redPin, LOW );
    pinMode( _greenPin, OUTPUT );
    digitalWrite( _greenPin, LOW );
    pinMode( _bleuPin, OUTPUT );
    digitalWrite( _bleuPin, LOW );
}




void ErrLED::error(){
    _status = 1;
    digitalWrite( _redPin, HIGH );
    digitalWrite( _greenPin, LOW );
    digitalWrite( _bleuPin, LOW ); 
}

void ErrLED::ok(){
    _status = 2;
    digitalWrite( _redPin, LOW );
    digitalWrite( _greenPin, HIGH );
    digitalWrite( _bleuPin, LOW );     
}

void ErrLED::warning(){
    _status = 3;
    digitalWrite( _redPin, LOW );
    digitalWrite( _greenPin, LOW  );
    digitalWrite( _bleuPin, HIGH );    
}

void ErrLED::test(){
    int statSav = _status;
    off();
    delay(500);
    error();
    delay(500);
    warning();
    delay(500);
    ok();
    delay(500);
    switch ( statSav ){
        case 1: error(); break;
        case 2: ok(); break;
        case 3: warning(); break;
    }
}

void ErrLED::off(){
    digitalWrite( _redPin, LOW );
    digitalWrite( _greenPin, LOW  );
    digitalWrite( _bleuPin, LOW );    
}

void ErrLED::on(){
    switch ( _status){
        case 1: error(); break;
        case 2: ok(); break;
        case 3: warning(); break;
    }   
}


