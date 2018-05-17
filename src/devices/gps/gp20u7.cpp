#include "gp20u7.h"
// TODO: Handle uninitialized _currentLocation

GP20U7::GP20U7(PlatformStream &s){
  _stream = &s;
}

GP20U7::GP20U7(PlatformStream *s){
  _stream = s;
}

Geolocation GP20U7::getGeolocation(){
    return _gpsdata;
}



int GP20U7::read(){
  long lat, lon;
  unsigned long fix_age,jdate, jtime;
  int thedate[6];
  int thetime[8];

  while(_stream->available()){
    int c = _stream->read();
    if(_gps.encode(c)){
      _gps.get_position(&lat, &lon, &fix_age);
      _gps.get_datetime(&jdate, &jtime, &fix_age);
      jtime /= 100;
    for (int i=5; i>=0; i--) {
        thedate[i] = jdate % 10;
        thetime[i] = jtime % 10;
        jdate /= 10;
        jtime /= 10;
        i-1;
      }
      // Map tinygps values into Geolocation struct
      _gpsdata.latitude = lat / 1000000.0;
      _gpsdata.longitude = lon / 1000000.0;
      _gpsdata.hours = thetime[0]*10 + thetime[1] + _gpsdata.zoneoffset;
      _gpsdata.minutes = thetime[2]*10 + thetime[3];
      _gpsdata.seconds = thetime[4]*10 + thetime[5];
      _gpsdata.day = thedate[0]*10 + thedate[1];
      _gpsdata.month = thedate[2]*10 + thedate[3];
      _gpsdata.year = thedate[4]*10 + thedate[5];
      _gpsdata.numSats = _gps._numsats;

      return 1;
    }
  }

  return 0;
}

void GP20U7::begin(){
  #if defined (ARDUINO_PLATFORM)
    reinterpret_cast<HardwareSerial *>(_stream)->begin(9600);
  #endif
}
