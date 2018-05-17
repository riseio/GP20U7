// include the library code:
#include <gp20u7.h>

// initialize the library with the serial port to which the device is
// connected
GP20U7 gps = GP20U7(Serial);

// Set up a Geolocation variable to track your current Location
Geolocation currentLocation;

void setup() {
  // Start the GPS module
  gps.begin();
}

void loop() {
  long _date,_time,_age;
  // The call to read() checks for new location information and returns 1
  // if new data is available and 0 if it isn't. It should be called
  // repeatedly.
  if(gps.read()){
    currentLocation = gps.getGeolocation();
    Serial.println("Your current location is:");
    Serial.print("    Latitude: ");
    Serial.println(currentLocation.latitude,5);
    Serial.print("    Longitude: ");
    Serial.println(currentLocation.longitude,5);
    Serial.print("   time: ");
    Serial.print(currentLocation.hours);
    Serial.print(" : ");
    Serial.print(currentLocation.minutes);
     Serial.print(" : ");
    Serial.println(currentLocation.seconds);
    Serial.print("   numsats: ");
    Serial.println(currentLocation.numSats);
  }
}
