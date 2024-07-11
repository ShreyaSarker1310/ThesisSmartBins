#include "CSE.h"
#include "declarative.h"
#include "discoveryMessage_m.h"
#include "types.h"
#include "utils.h"

CSE::CSE() {}
CSE::~CSE() {}

void CSE::initialize() {
  Uri = getId();

  EV << "URI of CSE: " << Uri << endl;

  NotificationDepth = par("notification_depth");
  multicastAlpha = par("alpha");
  multicastBeta = par("beta");
  multicastGamma = par("gamma");
  multicastDelta = par("delta");
  queryBufferTTL = par("queryBufferTTL");
  maxHops = par("maxHops");
  delay = par("delayTime");

  notif = 0;
  WATCH(notif);
}

/*
 * handleMessage
 *
 * handleMessage is an entry point for handling messages
 *
 */
void CSE::handleMessage(cMessage *msg) {
  // if messages are from AE, it forward to AE message handler
  if (strcmp(msg->getSenderModule()->getClassName(), "AE") == 0) {
    handleAEMessage(msg);
  }

  else if (strcmp(msg->getSenderModule()->getClassName(), "CSE") == 0) {
    handleDiscoveryMessage(msg);
  }
}

/*
 * handleAEMessage
 *
 * handleAEMessage is used to process message from Application Entities (AEs)
 * Messages are:
 * REGISTRATION
 * CANCELLATION
 * QUERY
 * UPDATE
 *
 */
void CSE::handleAEMessage(cMessage *msg) {
  AEMessage *aeMsg = check_and_cast<AEMessage *>(msg);

  // Getting the type of message from AEMessage
  int op_code = aeMsg->getOp_code();

  switch (op_code) {
  case REGISTRATION: {
    registrationAndNotification(aeMsg);
    break;
  }
  case CANCELLATION: {
    cancelationAndNotification(aeMsg);
  }
  case QUERY: {
    // if it is a query msg first we look up the local devices
    // then we create a discovery msg to start ASDQ
    localDBLookup(aeMsg);
    generateDiscoveryMessage(aeMsg);
    break;
  }
  case UPDATE: {
    updateData(aeMsg);
    localSubscriberLookup(aeMsg);
    generateUpdateMessage(aeMsg);
    break;
  }
  case SUBSCRIBE: {
    registerSubscriber(aeMsg);
    break;
  }
  default:
    break;
  }
  delete aeMsg;
}

/*
 * registrationAndNotification
 *
 * registrationAndNotification is for registering AEs in their present CSE
 * and, notifying the other CSEs about existence of the AEs.
 *
 */
void CSE::registrationAndNotification(AEMessage *msg) {
  // Extract
  // the feature_type;
  // URI;
  // data
  // from the AEMessage

  std::string feature_type = msg->getFeature_type();
  URI uri = msg->getURI();
  int data = msg->getData();

  // in graphical mode, show the feature type when AE is registering in CSE
  bubble(feature_type.c_str());

  // register AE to parent CSE
  registerAE(feature_type, uri, data);

  notifyCSE(feature_type, 1);
}

/*
 * registerAE
 *
 * registerAE is for registering AEs in their parents CSEs local database
 *
 */
void CSE::registerAE(std::string feature_type, URI uri, int data) {

  SemanticRoutingTable[feature_type].database.insert(
      std::pair<URI, int>(uri, data));

  EV << "AE which URI " << uri << " is registered to CSE" << endl;

  EV << "Semantic Routing Table size is: "
     << SemanticRoutingTable[feature_type].database.size() << endl;
}

/*
 * cancelationAndNotification
 *
 * cancelationAndNotification is used to perform AE deregistration at parent
 * CSE. Also, it invokes CSE neighbors notification as a result of new entity
 * deregistration (cancellation).
 *
 */
void CSE::cancelationAndNotification(AEMessage *msg) {
  // Extract
  // the feature_type;
  // URI;
  // from the AEMessage
  std::string feature_type = msg->getFeature_type();
  URI uri = msg->getURI();

  // deregister AE from parent CSE
  deregisterAE(feature_type, uri);

  notifyCSE(feature_type, -1);
}

/*
 * deregisterAE
 *
 * deregisterAE is for updating semantic routing table to accustom for AE
 * cancellation.
 *
 */
void CSE::deregisterAE(std::string feature_type, URI uri) {
  SemanticRoutingTable[feature_type].database.erase(
      SemanticRoutingTable[feature_type].database.find(uri));

  EV << "AE which URI " << uri << "is deregistered from CSE" << endl;
  EV << "Semantic Routing Table size is: "
     << SemanticRoutingTable[feature_type].database.size() << endl;
}

/*
 * notifyCSE
 *
 * notifyCSE method is used for creating and broadcasting notification message
 * to the neighbors with limted notification depth.
 *
 */
void CSE::notifyCSE(std::string feature_type, int delta) {

  // creating notification message to send to the neighbors
  auto msg = generateMessage(NOTIFY);

  msg->setFeature_type(feature_type.c_str());
  msg->setHopCount(NotificationDepth);
  msg->setDelta(delta);

  // send to CSEs
  notifyNeighbors(msg);
}

/*
 * generateMessage
 *
 * generateMessage is used to generate message of specified type.
 *
 */
discoveryMessage *CSE::generateMessage(int op_code) {
  switch (op_code) {
  case NOTIFY: {
    int URI_route = getId();
    char msgname[20];
    sprintf(msgname, "Notif");

    // Create message object and set source and destination field.
    NotifMsg = new discoveryMessage(msgname);
    NotifMsg->setDirection(DOWN);
    NotifMsg->setOp_code(NOTIFY);
    NotifMsg->setURI_route(URI_route);
    NotifMsg->setURI_init(URI_route);
    return NotifMsg;
    break;
  }
  case RESPONSE: {
    int URI_route = getId();
    char msgname[20];
    sprintf(msgname, "Rsp");

    // Create message object and set source and destination field.
    ResMsg = new discoveryMessage(msgname);
    ResMsg->setOp_code(RESPONSE);
    ResMsg->setURI_route(URI_route);
    return ResMsg;
    break;
  }
  default:
    break;
  }
  return nullptr;
}

/*
 * notifyNeighbors
 *
 * notifyNeighbors is used to broadcast notification to all neighbors,
 * excluding the neighbor that sent the message to the current CSE.
 * Also, populates gate vector of the message with the arrival gate.
 *
 */
void CSE::notifyNeighbors(discoveryMessage *msg) {
  std::vector<cGate *> gateVector = msg->getGateVector();

  msg->setGateVector(gateVector);

  if (msg->getArrivalGate() != nullptr) {
    gateVector.push_back(msg->getArrivalGate()->getOtherHalf());
    msg->setGateVector(gateVector);
  }

  EV << "Sending messages to upstream" << endl;
  multicast("provider", msg);

  delete msg;
}

/*
 * multicast
 *
 * multicast is used to send messages in a multicast manner through the
 * specified gate, optionally restricting maximal number of messages.
 *
 */
bool CSE::multicast(std::string gateName, discoveryMessage *discoveryMsg,
                    int maxMessages) {
  auto dir = gateToDirection[gateName];
  std::string outGate = gateName + "$o";

  // checking the size of gate
  int t = gateSize(gateName.c_str());

  // if it is greater than zero, it means we have the gate which we want to
  // direct the message.
  if (t <= 0) {
    return false;
  }

  // if it detects the size of the target gate or gates
  int Uri = gate(outGate.c_str(), 0)->getId();
  EV << "URI of destination " << Uri << endl;

  int vectSize = gate(outGate.c_str(), 0)->getVectorSize();
  // it register in the scheduler map the URI of the CSE and the parameters of
  // the gate we will forward through the vectSize of the gate which have all
  // the target gates

  int sent = 0;
  for (int i = 0; i < vectSize; i++) {
    if (sent >= maxMessages) {
      break;
    }

    auto gateVector = discoveryMsg->getGateVector();
    bool visited = false;
    cGate *gateToSend = gate(outGate.c_str(), i);
    for (auto g : gateVector) {
      auto gID = g->getConnectionId();
      auto sID = gateToSend->getConnectionId();
      if (gID == sID) {
        visited = true;
        break;
      }
    }
    if (visited) {
      continue;
    }

    auto msg = discoveryMsg->dup();
    msg->setDirection(dir);
    send(msg, outGate.c_str(), i);
    sent++;
  }
  return sent > 0;
}

/*
 * localDBLookup
 *
 * localDBLookup is used to look up for the devices in the CSE
 * in which there is AE which starts the query
 * and returns the result directly
 *
 */
void CSE::localDBLookup(AEMessage *msg) {
  auto feature_type = msg->getFeature_type();

  if (SemanticRoutingTable[feature_type].database.size() != 0) {
    auto localresponseMsg = generateMessage(RESPONSE);
    localresponseMsg->setDirection(NODIR);
    localresponseMsg->setFeature_type(feature_type);
    localresponseMsg->setURI_init(getId());
    localresponseMsg->setReturnCode(ResultCode::SUCCESS);
    send(localresponseMsg, msg->getArrivalGate()->getOtherHalf()->getId());
    return;
  } else {
    auto localresponseMsg = generateMessage(RESPONSE);
    localresponseMsg->setDirection(NODIR);
    localresponseMsg->setFeature_type(feature_type);
    localresponseMsg->setURI_init(getId());
    localresponseMsg->setReturnCode(ResultCode::NOT_FOUND);
    send(localresponseMsg, msg->getArrivalGate()->getOtherHalf()->getId());
    return;
  }
}

/*
 * generateDiscoveryMessage
 *
 * generateDiscoveryMessage is used to create a discovery message
 *
 */
void CSE::generateDiscoveryMessage(AEMessage *msg) {

  // the followind data should not be changed during routing between CSEs
  queryMsg = new discoveryMessage("QUERY");
  queryMsg->setURI_init(msg->getURI());
  queryMsg->setFeature_type(msg->getFeature_type());
  queryMsg->setOp_code(QUERY);
  queryMsg->setQueryID(msg->getQueryID());

  // the following data may change during routing between CSEs
  queryMsg->setHopCount(maxHops);
  std::vector<cGate *> gateVector;
  gateVector.push_back(msg->getArrivalGate()->getOtherHalf());
  queryMsg->setGateVector(gateVector);
  gateVector.clear();

  // send query message to process query in order to foward to ther other CSE in
  // valley-free manner.
  processQuery(queryMsg);
}

/*
 * processQuery
 *
 * processQuery is used to route query if local DB lookup failed.
 * It tries to perform semantic routing, and if no records satisfying query were
 * found. It uses a fallback routing to multicast query to the best match
 * neighbors.
 *
 */
void CSE::processQuery(discoveryMessage *msg) {
  EV << "The Message is a query " << endl;

  if (msg->getHopCount() <= 0) {
    bubble("TTL expired");
    // Respond to the URI_init that the discovery ends
    msg->setOp_code(RESPONSE);

    EV << "TTL expired so we generate a response message" << endl;
    generateResponseMessage(msg, ResultCode::NOT_FOUND);
    return;
  }

  // Decreasing the hop count
  msg->setHopCount(msg->getHopCount() - 1);
  fallbackRouteQuery(msg);
}

/*
 * fallbackRouteQuery
 *
 * fallbackRouteQuery is used when semantic routing fails.
 * i.e. semantic routing table lookup returns no results
 * It multicasts query with coefficients.
 * It routes query in valley-free manner.
 *
 */
void CSE::fallbackRouteQuery(discoveryMessage *msg) {
  int D = msg->getDirection();

  bool successful = false;
  /*
   * We need to send response only if all of the broadcasts have failed.
   * Thus, we are performing logical AND between all invocations of broadcast.
   * If all of them fail - we will send response
   *
   */
  switch (D) {
  case DOWN: {
    successful = multicast("customer", msg, multicastAlpha);
    successful = !successful ? multicast("sibling", msg, multicastGamma) : true;
    break;
  }
  case SIDE_SIBLING: {
    successful = multicast("sibling", msg, multicastGamma);
    successful &= multicast("customer", msg, multicastAlpha);
    break;
  }
  case SIDE_PEER: {
    break;
  }
  case UP: {
    successful = multicast("provider", msg, multicastBeta);
    successful = !successful ? multicast("sibling", msg, multicastGamma) : true;
    successful &= multicast("customer", msg, multicastDelta);
    break;
  }
  default:
    break;
  }

  if (!successful) {
    bubble("No result");
    generateResponseMessage(msg, ResultCode::NOT_FOUND);
  }
}

/*
 * handleDiscoveryMessage
 *
 * handleDiscoveryMessage is used to handle messages from CSE
 *
 */
void CSE::handleDiscoveryMessage(cMessage *msg) {
  EV << "Entering into the CSE" << endl;
  discoveryMessage *discoveryMsg = check_and_cast<discoveryMessage *>(msg);

  EV << "The message type is : " << discoveryMsg->getOp_code() << endl;
  int op_code = discoveryMsg->getOp_code();

  switch (op_code) {
  case NOTIFY: {
    notif++;
    updatingRoutingTableAndNotify(discoveryMsg);
    break;
  }
  case RESPONSE: {
    EV << "Message type is reponse so no new gate added" << endl;
    returnResponse(discoveryMsg);
    break;
  }
  case QUERY: {
    EV << "Message is a query" << endl;

    std::vector<cGate *> tempGateVector;
    tempGateVector = discoveryMsg->getGateVector();
    tempGateVector.push_back(msg->getArrivalGate()->getOtherHalf());
    discoveryMsg->setGateVector(tempGateVector);
    EV << "A new gate is added = " << tempGateVector.back()->getFullName()
       << endl;
    tempGateVector.clear();

    handleQuery(discoveryMsg);
    break;
  }
  case UPDATE: {
    EV << "Message is an update" << endl;

    std::vector<cGate *> tempGateVector;
    tempGateVector = discoveryMsg->getGateVector();
    tempGateVector.push_back(msg->getArrivalGate()->getOtherHalf());
    discoveryMsg->setGateVector(tempGateVector);
    EV << "A new gate is added = " << tempGateVector.back()->getFullName()
       << endl;
    tempGateVector.clear();

    handleUpdate(discoveryMsg);
    break;
  }
  }

  delete discoveryMsg;
}

/*
 * updatingRoutingTableAndNotify
 *
 * updatingRoutingTableAndNotify is used to update sematic routing table
 * and notify other CSE neighbors (e.g. Customer, Peer, Sibling, Provider)
 *
 */
void CSE::updatingRoutingTableAndNotify(discoveryMessage *msg) {
  // Extract
  // the feature_type;
  // URI;
  // delta
  // direction
  // from the discoveryMessage
  std::string feature_type = msg->getFeature_type();
  URI cse = msg->getURI_route();
  int delta = msg->getDelta();
  int direction = msg->getDirection();

  std::string inputGate = msg->getArrivalGate()->getBaseName();
  Gates[cse] = std::make_pair(inputGate, msg->getArrivalGate()->getIndex());

  switch (direction) {
  case UP: {
    SemanticRoutingTable[feature_type].CSECustomer[cse] += delta;
    break;
  }
  case DOWN: {
    SemanticRoutingTable[feature_type].CSEProvider[cse] += delta;
    break;
  }
  case SIDE_SIBLING: {
    SemanticRoutingTable[feature_type].CSESibling[cse] += delta;
    break;
  }
  case SIDE_PEER: {
    SemanticRoutingTable[feature_type].CSEPeer[cse] += delta;
    break;
  }
  }

  // notification depth reached
  if (msg->getHopCount() >= NotificationDepth) {
    EV << "notification depth reached" << endl;
    return;
  }

  EV << "Redirecting notify" << endl;

  // Notify
  msg->setHopCount(msg->getHopCount() + 1);
  msg->setURI_route(Uri);
  notifyNeighbors(msg->dup());
}

/*
 * returnResponse
 *
 * returnResponse is used to return response in predefined manner,
 * i.e. unfolding path setp by step and sending messages back.
 *
 */
void CSE::returnResponse(discoveryMessage *msg) {
  EV << "The message is a response message." << endl;

  std::vector<cGate *> tempGateVector;

  // getting the return gate and index of return gate
  tempGateVector = msg->getGateVector();
  const char *returnGate = tempGateVector.back()->getName();
  int returnIndex = tempGateVector.back()->getIndex();

  // removing the used return gate
  tempGateVector.pop_back();
  msg->setGateVector(tempGateVector);
  tempGateVector.clear();

  // sending msg to the return gate
  send(msg->dup(), returnGate, returnIndex);
}

/*
 * handleQuery
 *
 * handleQuery is used to handle message type QUERY.
 * It memorizes distinct queries and omit duplicate ones.
 *
 */
void CSE::handleQuery(discoveryMessage *msg) {
  auto cse = msg->getURI_route();
  std::string inputGate = msg->getArrivalGate()->getBaseName();
  Gates[cse] = std::make_pair(inputGate, msg->getArrivalGate()->getIndex());

  if (seenQuery(msg)) {
    bubble("Dropping seen query");
    return;
  }

  int64_t ttl = SimTime(queryBufferTTL).inUnit(SimTimeUnit::SIMTIME_S);
  ttl = ttl + msg->getArrivalTime().inUnit(SimTimeUnit::SIMTIME_S);
  queryKey key;
  key.first = msg->getURI_init();
  key.second = msg->getQueryID();

  processedQueries[key] = ttl;

  auto res = DBLookup(msg);
  // If we find the index "NOT_FOUND" in the map, it means that the feature is
  // not present in the database.
  if (res == NOT_FOUND) {
    processQuery(msg);
    return;
  }

  std::map<int, int> dbres;
  dbres[res] = 0;
  EV << "DB Lookup Successful" << endl;
  msg->setDbResult(dbres);

  generateResponseMessage(msg);
}

/*
 * seenQuery
 *
 * seenQuery is used to check if the query processed previously or not.
 * It checks the local query buffer for the query ID.
 * Also, it performs cleanup of stale buffer records.
 *
 */
bool CSE::seenQuery(discoveryMessage *msg) {
  std::map<queryKey, int64_t> newProcessed(processedQueries);
  for (auto record : newProcessed) {
    if (record.second < simTime().inUnit(SimTimeUnit::SIMTIME_S)) {
      processedQueries.erase(record.first);
    }
  }

  queryKey key;
  key.second = msg->getQueryID();
  key.first = msg->getURI_init();

  if (processedQueries.find(key) != processedQueries.end()) {
    return true;
  }

  return false;
}

/*
 * DBLookup
 *
 * DBLookup is used to perform lookup in the semantic routing Table
 * for AEs children of the current CSE
 *
 */
URI CSE::DBLookup(discoveryMessage *msg) {

  auto feature_type = msg->getFeature_type();
  // extracting the feature_type
  // if we find the data correspond to the feature_type
  if (this->SemanticRoutingTable[feature_type].database.size() != 0) {
    bubble("Success in database");
    return this->SemanticRoutingTable[feature_type].database.begin()->first;
  } else if (this->SemanticRoutingTable[feature_type].CSECustomer.size() != 0) {
    bubble("Success in customer");
    return this->SemanticRoutingTable[feature_type].CSECustomer.begin()->first;
  } else if (this->SemanticRoutingTable[feature_type].CSEPeer.size() != 0) {
    bubble("Success in peer");
    return this->SemanticRoutingTable[feature_type].CSEPeer.begin()->first;
  } else if (this->SemanticRoutingTable[feature_type].CSESibling.size() != 0) {
    bubble("Success in sibiling");
    return this->SemanticRoutingTable[feature_type].CSESibling.begin()->first;
  } else if (this->SemanticRoutingTable[feature_type].CSEProvider.size() != 0) {
    bubble("Success in provider");
    return this->SemanticRoutingTable[feature_type].CSEProvider.begin()->first;
  } else
    return NOT_FOUND;
}

/*
 * generateResponseMessage
 *
 * generateResponseMessage is used to generate query response message
 * to be redirected to the source of the query
 *
 */
void CSE::generateResponseMessage(discoveryMessage *msg, ResultCode result) {
  EV << "inside generateResponseMessage Procedure" << "\n";

  auto responseMsg = generateMessage(RESPONSE);
  // These data may change during the routing of the query_buffer_TTL
  //  we set the direction to NODIR
  responseMsg->setDirection(NODIR);
  responseMsg->setFeature_type(msg->getFeature_type());
  responseMsg->setGateVector(msg->getGateVector());
  responseMsg->setReturnCode(result);
  responseMsg->setURI_init(this->Uri);

  handleDiscoveryMessage(responseMsg);
}

/*
 * updateData
 *
 * updateData is used to update value from AE to local database
 *
 */
void CSE::updateData(AEMessage *msg) {
  // Extract
  // feature_type;
  // URI;
  // data;
  // from the AEMessage

  std::string feature_type = msg->getFeature_type();
  URI uri = msg->getURI();
  int data = msg->getData();

  bubble(feature_type.c_str());

  saveAEData(feature_type, uri, data);
}

/*
 * saveAEData
 *
 * saveAEData is for saving AE data into CSE local database
 *
 */
void CSE::saveAEData(std::string feature_type, URI uri, int data) {

  if (SemanticRoutingTable.find(feature_type) != SemanticRoutingTable.end()) {
    if (SemanticRoutingTable[feature_type].database.find(uri) !=
        SemanticRoutingTable[feature_type].database.end()) {
      SemanticRoutingTable[feature_type].database[uri] = data;
      EV << "IN CSE: AE which URI " << uri << " value " << data
         << " is saved to local database" << endl;
    } else {
      EV << "IN CSE: Cannot find AE with URI " << uri << "in the local database"
         << endl;
    }
  } else {
    EV << "IN CSE: Cannot find Resource which type is " << feature_type
       << "in the local database" << endl;
  }
}

/*
 * localSubscriberLookup
 *
 * check subscribers in local database
 *
 */
void CSE::localSubscriberLookup(AEMessage *msg) {
  auto feature_type = msg->getFeature_type();

  updateMsg = new discoveryMessage("UPDATE");
  updateMsg->setURI_init(msg->getURI());
  updateMsg->setFeature_type(msg->getFeature_type());
  updateMsg->setOp_code(UPDATE);
  updateMsg->setUpdateID(msg->getUpdateID());
  updateMsg->setData(msg->getData());

  auto it = SubscribersTable.find(feature_type);
  if (it != SubscribersTable.end()) {
    if (!it->second.subscribers.empty()) {
      for (auto const &[id, gate] : it->second.subscribers) {
        send(updateMsg, gate);
      }
    }

    auto localresponseMsg = generateMessage(RESPONSE);
    localresponseMsg->setDirection(NODIR);
    localresponseMsg->setFeature_type(feature_type);
    localresponseMsg->setURI_init(getId());
    localresponseMsg->setReturnCode(ResultCode::SUCCESS);
    send(localresponseMsg, msg->getArrivalGate()->getOtherHalf()->getId());
    return;
  } else {
    auto localresponseMsg = generateMessage(RESPONSE);
    localresponseMsg->setDirection(NODIR);
    localresponseMsg->setFeature_type(feature_type);
    localresponseMsg->setURI_init(getId());
    localresponseMsg->setReturnCode(ResultCode::NOT_FOUND);
    send(localresponseMsg, msg->getArrivalGate()->getOtherHalf()->getId());
    return;
  }
}

/*
 * generateUpdateMessage
 *
 * generateUpdateMessage is used to generate a update message
 *
 */
void CSE::generateUpdateMessage(AEMessage *msg) {
  // the following data should not be changed during routing between CSEs
  updateMsg = new discoveryMessage("UPDATE");
  updateMsg->setURI_init(msg->getURI());
  updateMsg->setFeature_type(msg->getFeature_type());
  updateMsg->setOp_code(UPDATE);
  updateMsg->setUpdateID(msg->getUpdateID());
  updateMsg->setData(msg->getData());

  // the following data may change during routing between CSEs
  updateMsg->setHopCount(maxHops);
  std::vector<cGate *> gateVector;
  gateVector.push_back(msg->getArrivalGate()->getOtherHalf());
  updateMsg->setGateVector(gateVector);
  gateVector.clear();

  // send update message to process update in order to forward to the other CSE
  // in valley-free manner.
  processUpdate(updateMsg);
}

/*
 * processUpdate
 *
 * processUpdate is used to route update to other CSEs
 *
 */
void CSE::processUpdate(discoveryMessage *msg) {
  EV << "The Message is an update " << endl;

  if (msg->getHopCount() <= 0) {
    bubble("TTL expired");
    // Respond to the URI_init that the discovery ends
    msg->setOp_code(RESPONSE);

    EV << "TTL expired so we generate a response message" << endl;
    generateResponseMessage(msg, ResultCode::NOT_FOUND);
    return;
  }

  // Decreasing the hop count
  msg->setHopCount(msg->getHopCount() - 1);
  fallbackRouteQuery(msg);
}

/*
 * handleUpdate
 *
 * handleUpdate is used to handle message type UPDATE.
 * It memorizes distinct updates and omit duplicate ones.
 *
 */
void CSE::handleUpdate(discoveryMessage *msg) {
  auto cse = msg->getURI_route();
  std::string inputGate = msg->getArrivalGate()->getBaseName();
  Gates[cse] = std::make_pair(inputGate, msg->getArrivalGate()->getIndex());

  if (seenUpdate(msg)) {
    bubble("Dropping seen update");
    return;
  }

  int64_t ttl = SimTime(queryBufferTTL).inUnit(SimTimeUnit::SIMTIME_S);
  ttl = ttl + msg->getArrivalTime().inUnit(SimTimeUnit::SIMTIME_S);
  queryKey key;
  key.first = msg->getURI_init();
  key.second = msg->getUpdateID();

  processedUpdates[key] = ttl;

  auto res = SubscriberLookup(msg);
  // If we find the index "NOT_FOUND" in the map, it means that the feature is
  // not present in the database.
  if (res == NOT_FOUND) {
    processUpdate(msg);
    return;
  }

  EV << "Subscriber Lookup Successful" << endl;

  generateResponseMessage(msg);
}

/*
 * seenUpdate
 *
 * seenUpdate is used to check if the update processed previously or not.
 *
 */
bool CSE::seenUpdate(discoveryMessage *msg) {
  std::map<queryKey, int64_t> newProcessed(processedUpdates);
  for (auto record : newProcessed) {
    if (record.second < simTime().inUnit(SimTimeUnit::SIMTIME_S)) {
      processedUpdates.erase(record.first);
    }
  }

  queryKey key;
  key.second = msg->getUpdateID();
  key.first = msg->getURI_init();

  if (processedUpdates.find(key) != processedUpdates.end()) {
    return true;
  }

  return false;
}

URI CSE::SubscriberLookup(discoveryMessage *msg) {
  auto feature_type = msg->getFeature_type();

  auto it = SubscribersTable.find(feature_type);
  if (it != SubscribersTable.end()) {
    if (!it->second.subscribers.empty()) {
      EV << "Found Subscribers" << endl;
      for (auto const &[id, gate] : it->second.subscribers) {
        send(msg->dup(), gate);
      }
    }
    return 0;
  } else {
    return NOT_FOUND;
  }
}

void CSE::registerSubscriber(AEMessage *msg) {
  // Extract
  // the feature_type;
  // URI;
  // data
  // from the AEMessage

  std::string feature_type = msg->getFeature_type();
  URI uri = msg->getURI();
  cGate *arrivalGate = msg->getArrivalGate()->getOtherHalf();

  SubscribersTable[feature_type].subscribers[uri] = arrivalGate;
  EV << "Register subscribers with URI " << uri << "for " << feature_type
     << endl;
}
