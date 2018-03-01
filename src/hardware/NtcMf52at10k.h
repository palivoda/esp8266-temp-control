#include <Arduino.h>

#ifndef NtcMf52at10k_h
#define NtcMf52at10k_h

class NtcMf52at10k {
  uint8_t pin;
  float getR(float V);

  public:
    NtcMf52at10k(const uint8_t p);
    float getTemp();
};

#endif
