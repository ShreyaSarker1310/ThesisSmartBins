#ifndef SMARTBIN_H_
#define SMARTBIN_H_

#include <omnetpp.h>
#include <vector>
#include "WasteMessage_m.h"

using namespace omnetpp;

class SmartBin : public cSimpleModule {
  private:
    double fillLevel;
    double latitude;
    double longitude;
    simtime_t transmissionInterval;
    std::vector<double> wasteDisposalRates;
    int currentHour;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void sendWasteMessage();
    void updateFillLevel();
};

#endif
