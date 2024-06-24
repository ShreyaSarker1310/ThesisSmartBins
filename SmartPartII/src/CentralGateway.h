#ifndef CENTRALGATEWAY_H_
#define CENTRALGATEWAY_H_

#include <omnetpp.h>
#include "WasteMessage_m.h"

using namespace omnetpp;

class CentralGateway : public cSimpleModule {
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

#endif
