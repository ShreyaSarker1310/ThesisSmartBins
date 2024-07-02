#include "AE.h"
#include "discoveryMessage_m.h"
#include "types.h"
#include "utils.h"

AE::AE() {}

AE::~AE() {}

int AE::numInitStages() const { return 2; }

void AE::initialize(int stage) {
  numOfFound = 0;
  canMsg = regMsg = queryMsg = nullptr;
  aeType = par("aeType").intValue();

  switch(stage) {
  case InitStage::INIT_REGISTRATION:
    registration();
    break;

  case InitStage::INIT_QUERY:
    sendQuery();
    break;

  default:
    EV_FATAL << "Unknown initialization phase!\n";
    break;
  }
} // end of initialize

void AE::registration() {
  URI = getId();

  feature_type = feature_types[aeType];

  EV << "AE with Id number " << URI << " is " << feature_type << endl;
  sendAEMessage(REGISTRATION);
}

void AE::sendQuery() {
  URI = getId();

  if (aeType == 1) {
    query_feature_type = feature_types[0];
    EV << "AE of URI " << URI << " is searching for smartBin" << endl;
    sendAEMessage(QUERY);
  }

  if (aeType == 2) {
    query_feature_type = feature_types[1];
    EV << "AE of URI " << URI << " is searching for smartTruck" << endl;
    sendAEMessage(QUERY);
  }
}

void AE::sendAEMessage(int op_code) {
  switch (op_code) {
  case CANCELLATION: {
    canMsg = new AEMessage("C");
    canMsg->setURI(URI);
    canMsg->setData(data);
    canMsg->setOp_code(CANCELLATION);
    canMsg->setFeature_type(feature_type.c_str());
    sendDelayed(canMsg, simTime() + 5, "cse$o");
    break;
  }

  case REGISTRATION: {
    regMsg = new AEMessage("Reg");
    regMsg->setURI(URI);
    regMsg->setFeature_type(feature_type.c_str());
    regMsg->setData(data);
    regMsg->setOp_code(REGISTRATION);
    send(regMsg, "cse$o");
    break;
  }
  case QUERY: {
    queryMsg = new AEMessage("Q");
    queryMsg->setURI(URI);
    queryMsg->setFeature_type(query_feature_type.c_str());
    queryMsg->setOp_code(QUERY);
    sendDelayed(queryMsg, simTime() + 2, "cse$o");
    break;
  }

  default:
    break;
  }
}

void AE::handleMessage(cMessage *msg) {
  discoveryMessage *responseMsg = check_and_cast<discoveryMessage *>(msg);
  EV << "AE receives a response" << "\n";

  if (responseMsg->getReturnCode() == ResultCode::SUCCESS) {
    numOfFound++;
    EV << "Resource of type " << responseMsg->getFeature_type()
       << " found in URI " << responseMsg->getURI_init() << "\n";
  }

  if (responseMsg->getReturnCode() == ResultCode::NOT_FOUND) {
    EV << "Resource of type " << responseMsg->getFeature_type()
       << " not found in URI " << responseMsg->getURI_init() << "\n";
  }

  delete responseMsg;
}

void AE::finish() {
  if (aeType == 1 || aeType == 2) {
    EV << "The number of requested Resources are found is: " << numOfFound
       << endl;
  }
}
