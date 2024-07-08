#include "AE.h"
#include "discoveryMessage_m.h"
#include "types.h"
#include "utils.h"
#include <cmath>

AE::AE() {}

AE::~AE() {}

int AE::numInitStages() const { return 2; }

void AE::initialize(int stage) {
  numOfFound = 0;
  canMsg = regMsg = queryMsg = nullptr;

  // Get Resource Type from user
  aeType = par("aeType").intValue();
  queryType = par("queryType").intValue();

  if (aeType == 0) {
    switch (stage) {
    case 0:
      registration();
      break;
    case 1:
      updateData();
      break;
    default:
      EV_FATAL << "Unknown initialization phase!" << endl;
      break;
    }
  } else if (aeType == 1) {
    switch (stage) {
    case 0:
      registration();
      break;
    case 1:
      sendQuery();
      break;
    default:
      EV_FATAL << "Unknown initialization phase!" << endl;
      break;
    }
  } else if (aeType == 2) {
    switch (stage) {
    case 0:
      registration();
      break;
    case 1:
      sendQuery();
      break;
    default:
      EV_FATAL << "Unknown initialization phase!" << endl;
      break;
    }
  }
}

void AE::handleMessage(cMessage *msg) {
  // when AE receive the self message
  if (msg == event) {
    updateData();
  }

  // when AE receive the response from CSE
  EV << "AE receives a response" << endl;
  discoveryMessage *responseMsg = check_and_cast<discoveryMessage *>(msg);

  if (responseMsg->getReturnCode() == ResultCode::SUCCESS) {
    numOfFound++;
    EV << "Resource of type " << responseMsg->getFeature_type()
       << " found in URI " << responseMsg->getURI_init() << endl;
  }
  if (responseMsg->getReturnCode() == ResultCode::NOT_FOUND) {
    EV << "Resource of type " << responseMsg->getFeature_type()
       << " not found in URI " << responseMsg->getURI_init() << endl;
  }

  delete responseMsg;
}

void AE::registration() {
  URI = getId();

  // Set Resource feature type
  feature_type = feature_types[aeType];
  EV << "AE with Id number " << URI << " is " << feature_type << endl;

  // assign bin level randomly
  data = uniform(0, 100);

  // send an AE message with op_code REGISTRATION
  sendAEMessage(REGISTRATION);
}

void AE::deregistration() {
  URI = getId();

  EV << "AE with Id number " << URI << " will be deleted." << endl;

  // send an AE message with op_code CANCELLATION
  sendAEMessage(CANCELLATION);
}

void AE::sendQuery() {
  URI = getId();

  if (aeType != 0) {
    query_feature_type = feature_types[queryType];
    EV << "AE of URI " << URI << " is searching for " << query_feature_type
       << endl;
    sendAEMessage(QUERY);
  }

  sendAEMessage(QUERY);
}

void AE::sendUpdate() { URI = getId(); }

void AE::sendAEMessage(int op_code) {
  switch (op_code) {
  case REGISTRATION: {
    regMsg = new AEMessage("R");
    regMsg->setURI(URI);
    regMsg->setData(data);
    regMsg->setOp_code(REGISTRATION);
    regMsg->setFeature_type(feature_type.c_str());
    send(regMsg, "cse$o");
    break;
  }
  case CANCELLATION: {
    canMsg = new AEMessage("C");
    canMsg->setURI(URI);
    canMsg->setData(data);
    canMsg->setOp_code(CANCELLATION);
    canMsg->setFeature_type(feature_type.c_str());
    send(canMsg, "cse$o");
    break;
  }
  case QUERY: {
    queryMsg = new AEMessage("Q");
    queryMsg->setURI(URI);
    queryMsg->setFeature_type(query_feature_type.c_str());
    queryMsg->setOp_code(QUERY);
    send(queryMsg, "cse$o");
    break;
  }
  case UPDATE: {
    updateMsg = new AEMessage("U");
    updateMsg->setURI(URI);
    updateMsg->setFeature_type(feature_type.c_str());
    updateMsg->setData(data);
    updateMsg->setOp_code(UPDATE);
    send(updateMsg, "cse$o");
    break;
  }
  default:
    break;
  }
}

double AE::getWasteDisposalRate(simtime_t currentTime) {
  double rate;

  simtime_t quotient = currentTime / (24 * 3600);
  simtime_t normalizedTime = currentTime - (24 * 3600) * quotient;

  if (normalizedTime <= 6 * 3600)
    rate = 0.01;
  else if (normalizedTime <= 7 * 3600)
    rate = 0.3;
  else if (normalizedTime <= 8 * 3600)
    rate = 0.5;
  else if (normalizedTime <= 9 * 3600)
    rate = 0.9;
  else if (normalizedTime <= 10 * 3600)
    rate = 0.5;
  else if (normalizedTime <= 11 * 3600)
    rate = 0.3;
  else if (normalizedTime <= 16 * 3600)
    rate = 0.01;
  else if (normalizedTime <= 17 * 3600)
    rate = 0.5;
  else if (normalizedTime <= 18 * 3600)
    rate = 0.8;
  else if (normalizedTime <= 19 * 3600)
    rate = 0.5;
  else if (normalizedTime <= 24 * 3600)
    rate = 0.01;
  else
    rate = 0.01;

  return rate;
}

void AE::updateData() {
  URI = getId();
  event = new cMessage("updateData");

  simtime_t currentTime = simTime().inUnit(SimTimeUnit::SIMTIME_S);
  // generate random waste amount
  int amount = intuniform(0, 100);
  // get disposal rate
  double rate = getWasteDisposalRate(currentTime);

  if (data < 100) {
    // calcuate waste amount relative to time
    data += (int)(amount * rate);
    EV << "AE with URI " << URI << " data value updated to " << data << endl;
  }

  if (data > 80) {
    sendAEMessage(UPDATE);
  }

  scheduleAt(currentTime + 45 * 60, event);
}

void AE::finish() {
  EV << "The number of requested Resources are found is: " << numOfFound
     << endl;
}
