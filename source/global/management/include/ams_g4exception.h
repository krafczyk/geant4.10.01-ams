//dummy geexception class to prevent G4Exception calling abort()
#ifndef __AMS_G4EXCEPTION__
#define __AMS_G4EXCEPTION__
class ams_g4exception{
  //do nothing
public:
int Severity;
ams_g4exception(int k=0):Severity(k){};
};

#endif
