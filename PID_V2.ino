//----------------------------------------
// Config
//----------------------------------------
 
#define Kp            300L
#define Ki            600L
#define Kd            0L
 
//----------------------------------------
// Data
//----------------------------------------
 
int16_t pid_lastErr;
int16_t pid_sumErrs;
uint16_t pid_time;
 
//----------------------------------------
//
//----------------------------------------
 
void resetPID()
{
  pid_lastErr = 0;
  pid_sumErrs = 0;
  adjustLMotor = adjustRMotor = 0;
  updateMotors();
  clear_ticks();
  pid_time = 0;
}
 
//----------------------------------------
//
//----------------------------------------
 
void driveStraight()
{
  static int16_t lticks = 0, rticks = 0;
  static uint16_t ms = 0;
  int16_t dlticks, drticks, diff;
  int32_t delta;
  uint16_t dms;
  int adjustLMotor = adjustRMotor = 0;
 
  get_ticks_since_last( &dlticks, &drticks, &dms);
 
  lticks += dlticks;
  rticks += drticks;
  ms += dms;
  pid_time += dms;
 
  if ( ms >= 100 )
  {
    // we assume wheels are turning in the same direction
    int16_t dir = ( lticks &amp;lt; 0 || rticks &amp;lt; 0) ? -1 : 1;
 
    // make the values positive
    lticks *= dir;
    rticks *= dir;
 
    diff = ((lticks  - rticks)*100L)/ms + SYSTEM_BIAS;
 
    // we want the difference to be 0
 
    // track the integral
    pid_sumErrs += diff;
 
    // get the differential
    delta = (int32_t) (diff - pid_lastErr);
 
    int16_t P = (int16_t) ((Kp*((int32_t)diff)
                          + Ki*((int32_t)pid_sumErrs)
                          + (Kd*delta))/1000L);
 
    pid_lastErr = diff;
 
    // a positive error means the left motor is
    // turning more than the right so adjust
    // each motor accordingly
    int16_t adjust = (P/2)*dir;
 
    adjustLMotor -= adjust;
    adjustRMotor += adjust;
    updateMotors();
 
    lticks = 0;
    rticks = 0;
    ms = 0;
  }
}
