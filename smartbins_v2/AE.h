#ifndef AE_H_
#define AE_H_

#include "AEMessage_m.h"
#include "utils.h"
#include <omnetpp.h>
#include <stdio.h>
#include <string.h>

using namespace omnetpp;

enum InitStage {
    INIT_REGISTRATION = 0,
    INIT_QUERY = 1
};

class AE : public cSimpleModule {
public:
  AE();
  virtual ~AE();

protected:
  // by default in omnet methods
  virtual void initialize(int stage) override;
  virtual void handleMessage(cMessage *msg) override;
  // application specific
  void sendAEMessage(int op_code);
  void registration();
  void sendQuery();
  virtual int numInitStages() const;
  virtual void finish() override;

private:
  AEMessage *canMsg;
  AEMessage *regMsg;
  AEMessage *queryMsg;

  long numOfFound;
  int queryIndex;
  int URI;
  int data;
  int maxHop;
  int ran_number;
  int aeType;
  std::string feature_type;
  std::string query_feature_type;
  std::vector<std::string> feature_types{"smartBin", "smartTruck",
                                         "smartWarehouse"};
};

Define_Module(AE);

#endif
