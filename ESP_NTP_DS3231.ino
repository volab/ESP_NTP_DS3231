/**
 @file ESP_NTP_DS3231.ino
 @brief set time on DS3231 from NTP server
 
 */

int timeZone = 2; // Paris heure d'été
// int timeZone = 1; // Paris heure d'hiver
 
#include "ESP_NTP_DS3231.h"
 
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "fr.pool.ntp.org");

// char wifi_ssid[50];
// char wifipass[50];
String wifi_ssid_s;
String wifipass_s;
// bool wifiStatus = false; // replaced by WiFi.isConnected()
int wifi_connection_mode;

RTC_DS3231 rtc;
DateTime NTPTime;

bool errNTPinit = true;
bool errRTCinit = true;

/*
function prototype
*/
bool readWifiCredit();

ErrLED wifiLed(D3, D4, D8), dsLed(D5,D6, D0);
bouton bp;


 
 void setup(){
    DateTime now;
    char buf[255];
    wifiLed.begin();
    dsLed.begin();
    
    DEBUGPORT.begin(9600);
    DEBUGPORT.println();
    DEBUGPORT.println( F("<VoLAB> Sketch start..."));
    
    wifiLed.warning();
    // wifiLed.warning();
    dsLed.off();
    
    
    // pinMode( WIFISELMODEPIN, INPUT_PULLUP );
    // no more pin available.
    // D1, D2 for I2C
    // D0, D3, D4, D5, D6, D8 for 2 RGB LEDs
    // D7 for bp
    // A0 ? can bu used for a BP or switch ? may be
    // wifi_connection_mode = digitalRead( WIFISELMODEPIN );
    wifi_connection_mode = true ;
    if ( wifi_connection_mode ){
        //Verification du mode autoconnect de l'ESP
        DEBUGPORT.print(F("\n<VoLAB> Mode autoconnect :"));
        DEBUGPORT.println( WiFi.getAutoConnect()?"enabled":"disabled");
        DEBUGPORT.println( "<VoLAB> Wifi is connected ? " +  String(WiFi.isConnected()?"Yes":"No") );
        if ( readWifiCredit() ){
            WiFi.mode(WIFI_STA);
            WiFi.begin(wifi_ssid_s.c_str() , wifipass_s.c_str() );
            // WiFi.begin(); // try auto reconnect mode and it works

            while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
            }

            Serial.println("");
            Serial.println("WiFi connected");  
            Serial.print("IP address: ");
            Serial.println(WiFi.localIP()); 
            DEBUGPORT.println( "<VoLAB> Wifi is connected ? " +  String(WiFi.isConnected()?"Yes":"No") );
            DEBUGPORT.println("<VoLAB> SSID = " + WiFi.SSID() );
            wifiLed.ok();
        } 
    } else {
        //use Wifi_manager and its access point
        // TODO - 15/09/18

    }
    // byte error;
    rtc.begin();
    Wire.beginTransmission(DS3231_ADDRESS);
    errRTCinit = Wire.endTransmission();
    // if (error) dsLed.error();
    // if (! rtc.begin()) {
    if ( errRTCinit ) {
        DEBUGPORT.println(F("<VoLAB> ERR : Couldn't find RTC"));
        // while (1);
        // errRTCinit = true;
        dsLed.error();
    } else {
        errRTCinit = false;
        dsLed.warning();
        now = rtc.now();
        sprintf(buf, "<VoLAB> DS3231 Start date : %d/%d/%d %d:%d:%d", 
            now.day(), now.month(), now.year(),
            now.hour(), now.minute(), now.second());
        DEBUGPORT.println( buf);
        DEBUGPORT.println( "<VoLAB : DS3231 valid time ? " + String( rtc.lostPower() ?  "No" : "Yes" ) );
        if ( !rtc.lostPower() ) dsLed.ok();
        // DEBUGPORT.print("<JSO> \tsince midnight 1/1/1970 = ");
        // DEBUGPORT.println(now.unixtime());
    } 
   

    if ( WiFi.isConnected() ){
        timeClient.begin();
        errNTPinit = !timeClient.forceUpdate();
        timeClient.setTimeOffset( timeZone * SECPERHOURS );
        setTime(  timeClient.getEpochTime() );
        NTPTime = DateTime( timeClient.getEpochTime() );
        sprintf(buf, "<VoLAB> NTP full date (RTCLib.h)  : %d/%d/%d %d:%d:%d", 
            NTPTime.day(), NTPTime.month(), NTPTime.year(),
            NTPTime.hour(), NTPTime.minute(), NTPTime.second()); 
        DEBUGPORT.println( buf);            
        sprintf(buf, "<VoLAB> NTP full date (TimeLib.h) : %d/%d/%d %d:%d:%d", 
            day(), month(), year(),
            hour(), minute(), second());       
        DEBUGPORT.println( buf);            
        if (!errNTPinit){
            DEBUGPORT.println( "<VoLAB> NTP time " + timeClient.getFormattedTime() );
            DEBUGPORT.println( "<VoLAB> NTP epoc Time " + (String)timeClient.getEpochTime() );
            if ( !errRTCinit )
            DEBUGPORT.println( "<VoLAB> epoc Time from DS3231 " + (String)rtc.now().unixtime() );
        } else {
            DEBUGPORT.println(F("<JSO> ERR : NTP init error"));
            wifiLed.error();
        }         
    } 
    bp.begin( D7 );
}
 
 void loop(){
    char buf[255];
    DateTime now;
    bp.update();    
    switch ( SerialCommand::process() ){
        case 'S':       // <S> set DS3231 time
            if ( !errNTPinit && !errRTCinit){
                DEBUGPORT.println( F( "<VoLAB DS3231 set date and time from NTP serveur :") );
                errNTPinit = !timeClient.forceUpdate();
                NTPTime = DateTime( timeClient.getEpochTime() );
                rtc.adjust( NTPTime );
                now = rtc.now();
                sprintf(buf, "<VoLAB> DS3231 updated date : %d/%d/%d %d:%d:%d", 
                    now.day(), now.month(), now.year(),
                    now.hour(), now.minute(), now.second());
                DEBUGPORT.println( buf); 
                dsLed.ok();
            } else {
                DEBUGPORT.println( F("<VoLAB> commande impossible erreur DS3231 ou NTP serveur") );
            }
        break;

        case 'D':     // <D> for DS3231  display
            if ( !errRTCinit ){
                now = rtc.now();
                sprintf(buf, "<VoLAB> DS3231 Start date : %d/%d/%d %d:%d:%d", 
                    now.day(), now.month(), now.year(),
                    now.hour(), now.minute(), now.second());
                DEBUGPORT.println( buf);  
                DEBUGPORT.println( "<VoLAB : DS3231 valid time ? " + 
                    String( rtc.lostPower() ?  "No" : "Yes" ) );                
            } else {
                DEBUGPORT.println( F("<VoLAB> commande impossible erreur DS3231") );
            }
        break;
        case 'N':     // <N> for display NTP time
            if ( !errNTPinit ){
                errNTPinit = !timeClient.forceUpdate();
                NTPTime = DateTime( timeClient.getEpochTime() );
                sprintf(buf, "<VoLAB> NTP full date (RTCLib.h)  : %d/%d/%d %d:%d:%d", 
                NTPTime.day(), NTPTime.month(), NTPTime.year(),
                NTPTime.hour(), NTPTime.minute(), NTPTime.second()); 
                INTERFACE.println( buf);
            } else {
                DEBUGPORT.println( F("<VoLAB> commande impossible erreur NTP") ) ;
            }
        break;     
        case '2':     // <2> for 2 display NTP and DS3231 time
            if ( !errNTPinit && !errRTCinit ){
                errNTPinit = !timeClient.forceUpdate();
                NTPTime = DateTime( timeClient.getEpochTime() );
                now = rtc.now();
                sprintf(buf, "<VoLAB> NTP full date : %d/%d/%d %d:%d:%d", 
                NTPTime.day(), NTPTime.month(), NTPTime.year(),
                NTPTime.hour(), NTPTime.minute(), NTPTime.second()); 
                INTERFACE.println( buf);
                sprintf(buf, "<VoLAB> DS3231 date : %d/%d/%d %d:%d:%d", 
                    now.day(), now.month(), now.year(),
                    now.hour(), now.minute(), now.second());
                DEBUGPORT.println( buf); 
            } else {
                DEBUGPORT.println( F("<VoLAB> commande impossible erreur NTP ou DS3231") ) ;
            }
        break; 
        case 'T': //for led test
            wifiLed.test();
            dsLed.test();
        break;
        case 'O':
            wifiLed.off();
            dsLed.off();
        break;
        case 'o':
            wifiLed.on();
            dsLed.on();    
        break;
        case 'V':
            DEBUGPORT.println( "Compiled: " __DATE__ ", " __TIME__ );
        break;
        case 'd': // for EPOC delta time
            if (!errNTPinit && !errRTCinit){
                DEBUGPORT.println( "<VoLAB> NTP epoc Time " + (String)timeClient.getEpochTime() );
                DEBUGPORT.println( "<VoLAB> epoc Time from DS3231 " + (String)rtc.now().unixtime() );
                long delta = timeClient.getEpochTime() - rtc.now().unixtime();
                DEBUGPORT.println( "<VoLAB> Delta time : "+ String(delta) );
                if ( abs( delta ) > 10 ) dsLed.warning(); else dsLed.ok();
            } else {
                DEBUGPORT.println(F("<VoLAB> ERR : commande impossible"));
            }             
        break;
        case 'e': //introduice en 15s error in rtc for debug purpose only of course
        DEBUGPORT.println( F("<VoLAB> introduice 15s delta ") );
            NTPTime = DateTime( timeClient.getEpochTime() +15 ) ;
            rtc.adjust( NTPTime );
        break;
        
    };
    yield();
    if ( bp.clic() ) {
        DEBUGPORT.println(F( "<VoLAB> bouton clic !") );
        bp.acquit();
        dsLed.warning();
        delay(200);
        if ( !errNTPinit && !errRTCinit){
            DEBUGPORT.println( F( "<VoLAB DS3231 set date and time from NTP serveur :") );
            errNTPinit = !timeClient.forceUpdate();
            NTPTime = DateTime( timeClient.getEpochTime() );
            rtc.adjust( NTPTime );
            now = rtc.now();
            sprintf(buf, "<VoLAB> DS3231 updated date : %d/%d/%d %d:%d:%d", 
                now.day(), now.month(), now.year(),
                now.hour(), now.minute(), now.second());
            DEBUGPORT.println( buf); 
            dsLed.ok();
        } else {
            DEBUGPORT.println( F("<VoLAB> commande impossible erreur DS3231 ou NTP serveur") );
            dsLed.error();
        }
    }
    
    if ( bp.doubleClic() ){
        DEBUGPORT.println(F( "<VoLAB> bouton double clic !") );
        bp.acquit();        
    }
 }

/*
Work on global variables
wifi_ssid_s
wifipass_s
*/ 
bool readWifiCredit(){
    DEBUGPORT.println(F("<VoLAB reading wifi credit.> mounting FS..."));

    if (SPIFFS.begin()) {
        DEBUGPORT.println(F("<VoLAB reading wifi credit.> mounted file system"));
        if (SPIFFS.exists("/config.json")) {
            //file exists, reading and loading
            DEBUGPORT.println(F("<VoLAB reading wifi credit.> reading config file"));
            File configFile = SPIFFS.open("/config.json", "r");
            if (configFile) {
                DEBUGPORT.println( F("\topened config file") );
                size_t size = configFile.size();
                // Allocate a buffer to store contents of the file.
                std::unique_ptr<char[]> buf(new char[size]);

                configFile.readBytes(buf.get(), size);
                DynamicJsonBuffer jsonBuffer;
                JsonObject& json = jsonBuffer.parseObject(buf.get());
                // json.printTo(DEBUGPORT);
                if (json.success()) {
                    // DEBUGPORT.println("\nparsed json");
                    // strcpy(wifi_ssid, json["wifi_ssid"]);
                    // strcpy(wifipass, json["mqtt_port"]);
                    wifi_ssid_s = json["wifi_ssid"].as<String>();
                    wifipass_s = json["wifi_pass"].as<String>();
                    // wifi_ssid_s = String( wifi_ssid );
                    // wifipass_s = String( wifipass );
                } else {
                    DEBUGPORT.println(F("<VoLAB reading wifi credit.> failed to load json config"));
                    wifiLed.error();
                    return false;
                }
                configFile.close();
                return true;
            }
        }
    } else {
        DEBUGPORT.println(F("<VoLAB reading wifi credit.> failed to mount FS"));
        return false; 
    }
 }
 

 
