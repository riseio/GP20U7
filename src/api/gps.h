#ifndef TOI_API_GPS
#define TOI_API_GPS

typedef struct _Geolocation
{
  double latitude;
  double longitude;
  int hours;
  int minutes;
  int seconds;
  int year;
  int month;
  int day;
  int zoneoffset = 10;
  int numSats;
} Geolocation, *PGeolocation;

class GeolocationDevice{
public:
  virtual ~GeolocationDevice(){}
  virtual Geolocation getGeolocation(void) = 0;
  virtual int read(void) = 0; // used for polling only
  virtual void begin(void) = 0;

protected:
  Geolocation _gpsdata;
};

#endif
