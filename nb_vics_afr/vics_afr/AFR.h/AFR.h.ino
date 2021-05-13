/*
 * afr.h
 * used to calculate air fuel ratio for gasoline vehicles.
 * input sidnal from a wideband meter is converted into a narrowband signal siutable for OBDI vehicles
 */
 #ifndef afr_h
 #define afr_h
 #include "Arduino.h"
 class AFR
 {
  public:
    AFR(int wideband_sig);
    float calc_afr(float voltage);
    void set_narr_sig(float afr);
   private:
    int _wideband_sig;
 };

#endif
