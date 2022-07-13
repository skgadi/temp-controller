#ifndef GSK_RELAYS_H
#define GSK_RELAYS_H

#include "gsk_global.h"


class GSK_RELAYS {
  void setup();
  bool states[NO_OF_RELAYS];
  int pins[NO_OF_RELAYS];
  public:
  GSK_RELAYS();
  void resetAllRelays();
  void setAllRelays(bool);
  bool getStateFor(int);
  void setStateFor(int, bool);
};

#endif