#ifndef _BoatData_H_
#define _BoatData_H_


struct tBoatPosition{
  uint32_t ts; // Millis() of last update
//  double Latitude, Longitude,Altitude, HDOP, GeoidalSeparation;
};

struct tBoatDatum{
  uint32_t ts; // Millis() of last update
//  unsigned long DaysSince1970;   // Days since 1970-01-01
//  double GPSTime;// Secs since midnight,
};

struct tBoatGPSFix {
  uint32_t ts; // Millis() of last update
  // double DGPSAge;
  // int GPSQualityIndicator, SatelliteCount, DGPSReferenceStationID;
};

struct tBoatCourse{
  // updated from N2K: COGSOG,GNSS(?)  N0183: RMC,GGA(?)
  uint32_t ts; // Millis() of last update
  double TrueHeading,SOG,COG,Variation;
};

struct tBoatEnv{
  uint32_t ts; // Millis() of last update
  // temp
  // pressure
};

struct tBoatAttitude{
  // "Attitude = The orientation of a vehicle or other object relative to the horizon, direction of motion, other objects, etc.  [Wiki]"
  uint32_t ts; // Millis() of last update
  // pitch
  // roll
  // yaw
};

struct tBoatEngineRapid{
  uint32_t ts; // Millis() of last update
  double EngineSpeed; // rpm
};

struct tBoatEngineDynamic{
  uint32_t ts; // Millis() of last update
  double EngineHours;
  double FuelRate;
};

struct tBoatData {
  uint32_t Timestmp; // Millis() of last update
  tBoatPosition Position;
  tBoatDatum Datum;
  tBoatGPSFix GPSFix;
  tBoatCourse Course;
  tBoatAttitude Attitude;
  tBoatEnv Environment;
  tBoatEngineRapid EngineRapid;
  tBoatEngineDynamic EngineDynamic;

  // uint8_t SID;
  // bool MOBActivated;

public:
  tBoatData() {
    Timestmp = 0;
    Course.TrueHeading=0;
    Course.SOG=0;
    Course.COG=0; 
    Course.Variation=7.0;
    EngineRapid.EngineSpeed=0.0; 
    EngineDynamic.EngineHours=0.0; 
    EngineDynamic.FuelRate=0.0; 
    // Datum.GPSTime=0;
    // Datum.DaysSince1970=0; 
    // Position.Latitude = 0;
    // Position.Longitude = 0;
    // Position.Altitude=0;
    // Position.HDOP=100000;
    // GPSFix.DGPSAge=100000;
    // GPSFix.SatelliteCount=0; 
    // GPSFix.DGPSReferenceStationID=0;
    // SID=0;
    // MOBActivated=false; 
  };
};

#endif // _BoatData_H_
