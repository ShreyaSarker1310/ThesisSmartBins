#ifndef TRUCK_H_
#define TRUCK_H_

#include <omnetpp.h>
#include "WasteMessage_m.h"
#include "TruckMessage_m.h"

using namespace omnetpp;

class Truck : public cSimpleModule {
  private:
    int capacity;
    int currentLoad;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void processWasteMessage(WasteMessage *wm);
    void assignTruck(int binId);
};

#endif
