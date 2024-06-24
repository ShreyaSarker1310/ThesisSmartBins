#ifndef CSE_H_
#define CSE_H_

#include <omnetpp.h>

using namespace omnetpp;

class CSE : public cSimpleModule {
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

#endif /* CSE_H_ */
