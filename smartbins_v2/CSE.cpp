#include "CSE.h"
#include "declarative.h"
#include <algorithm>

// Constructor for Messages
CSE::CSE() {
        // Set the pointer to nullptr, so that the destructor won't crash
        // even if initialize() doesn't get called because of a runtime
        // error or user cancellation during the startup process.
//    queryMsg = NotifMsg = ResMsg = nullptr;
}

// Destructor for Messages
CSE::~CSE() {
    // Dispose of dynamically allocated the objects
//    delete queryMsg;
//    delete NotifMsg;
//    delete ResMsg;
}


void CSE::initialize() {

    this->Uri = getId(); // this is the omnet id which is given when creating the module in the NED file (sequential numbering )

    EV << "URI II " << Uri << "\n";
    NotificationDepth = par("notification_depth");
    this->multicastAlpha = par("alpha");
    this->multicastBeta = par("beta");
    this->multicastGamma = par("gamma");
    this->multicastDelta = par("delta");
    this->queryBufferTTL = par("queryBufferTTL");
    this->maxHops = par("maxHops");
    this->delay = par("delayTime");

    notif = 0;
    WATCH(notif);
}

/*
 * routeQuery
 * Used to perform semantic routing
 * Function returns the list of CSEs to redirect query to.
 * It returns the list of URIs of the same relationship type,
 * e.g. Customer, Sibling, Peer, Provider.
 *
 * */
/*
std::vector<URI> CSE::routeQuery(discoveryMessage *msg) {
    std::string feature_type = msg->getFeature_type();
    std::vector<URI> URI_Found;
    auto it = this->SemanticRoutingTable.find(feature_type);
    if (it == this->SemanticRoutingTable.end()) {
        EV << "feature Type not exist" << "\n";
        return URI_Found;
    }

    if (it->second.CSECustomer.size() > 0) {
        for (auto cit = it->second.CSECustomer.begin();
                cit != it->second.CSECustomer.end(); cit++) {
            URI_Found.push_back(cit->first);
        }
        return URI_Found;
    }
    if (it->second.CSESibling.size() > 0) {
        for (auto sit = it->second.CSESibling.begin();
                sit != it->second.CSESibling.end(); sit++) {
            URI_Found.push_back(sit->first);
        }
        return URI_Found;
    }
    if (it->second.CSEPeer.size() > 0) {
        for (auto sit = it->second.CSEPeer.begin();
                sit != it->second.CSEPeer.end(); sit++) {
            URI_Found.push_back(sit->first);
        }
        return URI_Found;
    }
    if (it->second.CSEProvider.size() > 0) {
        for (auto pit = it->second.CSEProvider.begin();
                pit != it->second.CSEProvider.end(); pit++) {
            URI_Found.push_back(pit->first);
        }
        return URI_Found;
    }

    return URI_Found;
}

*/

/*
 * processQuery is used to route query if local DB lookup failed.
 * It tries to perform semantic routing, and if no records satisfying query were found,
 * if uses a so-called fallback routing to multicast query to the best match neighbors.
 */
void CSE::processQuery(discoveryMessage *msg) {

    EV << "The Message is a query \n";

    if (msg->getHopCount() <= 0) {
        bubble("TTL expired");
        //Respond to the URI_init that the discovery ends
        msg->setOp_code(RESPONSE);
        //You extract from the top of the list the gate that has to be used
        EV << "TTL expired so we generate a response message \n";
        generateResponseMessage(msg, ResultCode::NOT_FOUND);
        return;
    }

    // Decreasing the hop count
    msg->setHopCount(msg->getHopCount() - 1);

//    auto res = routeQuery(msg);
//
//    if (res.size() > 0) {
//        for (auto it : res) {
//            auto gateit = this->Gates[it];
//            int gateindex = gateit.second;
//            std::string gateName = gateit.first + "$o";
//            bubble("Semantic record found");
////            sendDelayed(msg->dup(), delay, gateName.c_str(), gateindex);
//            send(msg->dup(), gateName.c_str(), gateindex);
//        }
//
//        return;
//    }
    fallbackRouteQuery(msg);
}

/*
 * fallbackRouteQuery is used when semantic routing fails
 * (i.e. semantic routing table lookup returns no results)
 * It multicasts query with coefficients.
 * It routes query in valley-free manner.
 */
void CSE::fallbackRouteQuery(discoveryMessage *msg) {
    int D = msg->getDirection();

    bool successful = false;

    /*
     * We need to send response only if all of the broadcasts have failed
     *
     * Thus, we are performing logical AND between all invocations of broadcast
     *
     * If all of them fail - we will send response
     * */
    switch (D) {
    case DOWN: {
        successful = multicast("customer", msg, this->multicastAlpha);
        successful =
                !successful ?
                        multicast("sibling", msg, this->multicastGamma) : true;
        break;
    }
    case SIDE_SIBLING: {
        successful = multicast("sibling", msg, this->multicastGamma);
        successful &= multicast("customer", msg, this->multicastAlpha);
        break;
    }
    case SIDE_PEER: {
        break;
    }
    case UP: {
        successful = multicast("provider", msg, this->multicastBeta);
        successful =
                !successful ?
                        multicast("sibling", msg, this->multicastGamma) : true;
        successful &= multicast("customer", msg, this->multicastDelta);
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
 * seenQuery is used to check if the query processed previously or not.
 * It checks the local query buffer for the query ID.
 * Also, performs cleanup of stale buffer records.
 */
bool CSE::seenQuery(discoveryMessage *msg) {
    std::map<queryKey, int64_t> newProcessed(this->processedQueries);
    for (auto record : newProcessed) {
        if (record.second < simTime().inUnit(SimTimeUnit::SIMTIME_S)) {
            this->processedQueries.erase(record.first);
        }
    }

    queryKey key;
    key.second = msg->getQueryID();
    key.first = msg->getURI_init();

    if (this->processedQueries.find(key) != this->processedQueries.end()) {
        return true;
    }

    return false;
}

/*
 * handleQuery is used to handle message of type QUERY.
 *It memorizes distinct queries and omits duplicate ones.
 */
void CSE::handleQuery(discoveryMessage *msg) {
    auto cse = msg->getURI_route();
    std::string inputGate = msg->getArrivalGate()->getBaseName();
    this->Gates[cse] = std::make_pair(inputGate, msg->getArrivalGate()->getIndex());

    if (seenQuery(msg)) {
        bubble("Dropping seen query");
        return;
    }

    int64_t ttl = SimTime(this->queryBufferTTL).inUnit(SimTimeUnit::SIMTIME_S);
    ttl = ttl + msg->getArrivalTime().inUnit(SimTimeUnit::SIMTIME_S);
    queryKey key;
    key.first = msg->getURI_init();
    key.second = msg->getQueryID();

    this->processedQueries[key] = ttl;

    auto res = DBLookup(msg);
    // If we find the index "NOT_FOUND" in the map, it means that
    // the feature is not present in the database
    if (res == NOT_FOUND) {
        processQuery(msg);
        return;
    }
    std::map<int, int> dbres;
    dbres[res] = 0;
    EV << "DB Lookup Successful" << "\n";
    msg->setDbResult(dbres);

    generateResponseMessage(msg);
}

/*
 * handleDiscoveryMessage is used to handle `discoveryMessage`.
*/
void CSE::handleDiscoveryMessage(cMessage *msg) {

    EV << "Entering into the CSE" << "\n";
    discoveryMessage *discoveryMsg = check_and_cast<discoveryMessage*>(msg);
    EV << "The Message type is : " << discoveryMsg->getOp_code() << "\n";

// switch on 3 possible opcodes: Notify, Query and Response

    int op_code = discoveryMsg->getOp_code();

    switch (op_code) {
    case NOTIFY:
        notif++;
        updatingRoutingTableAndNotify(discoveryMsg);
        break;
    case QUERY:
    {
        EV << "Message is a query\n";
        std::vector<cGate*> tempGateVector;
        // You put on top of the list  the name of the gate to be used in the return path (getOtherHalf)
        tempGateVector = discoveryMsg->getGateVector();
        tempGateVector.push_back(msg->getArrivalGate()->getOtherHalf());
        discoveryMsg->setGateVector(tempGateVector);
        EV << "A new  gate is added = " << tempGateVector.back()->getFullName() << "\n";
        tempGateVector.clear();

        handleQuery(discoveryMsg);

        break;
    }
    case RESPONSE:
        EV << "Message is type response so no new gate added\n";
        returnResponse(discoveryMsg);
        break;
    }

    delete discoveryMsg;
}

/*
 * returnResponse is used to return response in predefined manner, i.e.
 * unfolding path step by step and sending messages back.
 */
void CSE::returnResponse(discoveryMessage *msg) {
    EV << "The Message is a response message.\n";
    std::vector<cGate*> tempGateVector;
//  getting the return gate and index of return gate
    tempGateVector = msg->getGateVector();
    const char *returnGate = tempGateVector.back()->getName();
    int returnIndex = tempGateVector.back()->getIndex();
//  removing the used return gate
    tempGateVector.pop_back();
    msg->setGateVector(tempGateVector);
    tempGateVector.clear();
//  sending msg to the return gate
    send(msg->dup(), returnGate, returnIndex);
}

/*
 * handleAEMessage is used to process message from Application Entities (AEs)
 * Messages are registration or cancellation or query.
 */
void CSE::handleAEMessage(cMessage *msg) {

    AEMessage *aeMsg = check_and_cast<AEMessage*>(msg);

    // Getting the type of message from AE
    int op_code = aeMsg->getOp_code();  // op_code contains the type of message

    switch (op_code) {
    case REGISTRATION: {

        registrationAndNotification(aeMsg);
        break;
    }
    case CANCELLATION: {

        cancelationAndNotification(aeMsg);
        break;
    }
    case QUERY: {
        // if it is a query msg first we look up the loacl devices then we create a discovery msg and to start ASDQ
        localDBLookup(aeMsg);
        generateDiscoveryMessage(aeMsg);
        break;
    }
    default:
        break;
    }

    delete aeMsg;
}

/*
 * saveAEData is used to save AE data into CSE local database
 */
/*
void CSE::saveAEData(std::string feature_type, URI uri, int data) {
// we create an internal map
    std::map<URI, int> internalMap;
// we create an Iterator on the database
    std::map<std::string, std::map<URI, int>>::iterator it;
// we search for the feature_type in the database
    it = database.find(feature_type);
// if we don't find it
    if (it == database.end()) {
        // putting data in the internal map as a new entry
        internalMap[uri] = data;
    }
// if we find the feature_type
    else {
        internalMap = database[feature_type]; // we put the internal map inside the DataBase map next to the feature_type
        internalMap[uri] = data;
    }
    database[feature_type] = internalMap;

    EV << "feature type added in Database" << feature_type << "\n";
}
*/

/*
 * handleAERegistration is for registering AEs in their parent CSE.
 * And, notifying the other CSEs about existence of the AEs.
 */
void CSE::registrationAndNotification(AEMessage *msg) {

    // we extract the feature_type; URI_route; and data from the AEmessage
    std::string feature_type = msg->getFeature_type();

    int URI_route = msg->getURI();

//    int data = msg->getData();

    // bubble is used to show the feature type on graphical mode when AE is registering in CSE.
    bubble(feature_type.c_str());

    registerAE(feature_type, URI_route);

    // saveAEData(feature_type, URI_route, data);

    notifyCSE(feature_type, 1);

}

/*
 * handleAECancellation is used to perform Application Entity (AE) deregistration at parent CSE.
 * Also, it invokes CSE neighbors notification as a result of new entity deregistration (cancellation).
 */
void CSE::cancelationAndNotification(AEMessage *msg) {

    std::string feature_type = msg->getFeature_type();
    int URI_route = msg->getURI();

    deregisterAE(feature_type, URI_route);

    notifyCSE(feature_type, -1);
}


// This method (registerAE) is for registering AEs in their parents CSEs local databases.

void CSE::registerAE(std::string feature_type, URI uri) {

  // auto entry = getOrCreateRoutingEntry(feature_type);

    this->SemanticRoutingTable[feature_type].database.insert(std::pair<URI, int>(uri, 1));

//    this->SemanticRoutingTable[feature_type] = RoutingStruct;

//  This EV is just for testing the size of database contents :)
    EV << "SemanticRoutingTable[feature_type].database.size() is " << this->SemanticRoutingTable[feature_type].database.size() << '\n';

}

// deregisterAE is used to update semantic routing table to accustom for AE cancellation.

void CSE::deregisterAE(std::string feature_type, URI uri) {

//    auto entry = mustGetRoutingEntry(feature_type);

    this->SemanticRoutingTable[feature_type].database.erase(this->SemanticRoutingTable[feature_type].database.find(uri));

//    this->SemanticRoutingTable[feature_type] = RoutingStruct;

//  This EV is just for testing the size of database contents :)
    EV << "SemanticRoutingTable[feature_type].database.size() after deregitering is " << this->SemanticRoutingTable[feature_type].database.size() << '\n';
}

/*
 * handleMessage is an entry point for messages in OMNeT++
 */
void CSE::handleMessage(cMessage *msg) {

// Separating two kinds of messages, AEMessage and DiscoveryMessage
// AEMessages are coming from AEs and Discovery messages are coming from other CSEs

    if (strcmp(msg->getSenderModule()->getClassName(), "AE") == 0) {

        handleAEMessage(msg);
    }

    else if(strcmp(msg->getSenderModule()->getClassName(), "CSE") == 0) {

        handleDiscoveryMessage(msg);
    }

}

/*
 * generateResponseMessage is used to generate query response message
 * to be redirected to the source of the query
 */
void CSE::generateResponseMessage(discoveryMessage *msg, ResultCode result) {
    EV << "inside generateResponseMessage Procedure" << "\n";

    auto responseMsg = generateMessage(RESPONSE);
//These data may change during the routing of the query
// we set the direction to NODIR
    responseMsg->setDirection(NODIR);
    responseMsg->setFeature_type(msg->getFeature_type());
    responseMsg->setGateVector(msg->getGateVector());
    responseMsg->setReturnCode(result);
    responseMsg->setURI_init(this->Uri);

    handleDiscoveryMessage(responseMsg);
}

/*
 *This Method is creatinging a discovery message
 */
void CSE::generateDiscoveryMessage(AEMessage *msg) {
// these data should not change during the routing between CSEs

// we created a discovery message
    queryMsg = new discoveryMessage("QUERY");
// we extract the URI from the AE URI_init of the message
    queryMsg->setURI_init(msg->getURI());
// we extract the msg feature_type from AEmessage and we set it in the discovery Message
    queryMsg->setFeature_type(msg->getFeature_type());

// we set op_code to QUERY
    queryMsg->setOp_code(QUERY);
    queryMsg->setQueryID(msg->getQueryID());

//These data may change during the routing of the query

// set the hop count
    queryMsg->setHopCount(maxHops);

// we set the direction UP
//    queryMsg->setDirection(UP);

// create a omnet vector of type cGate* named gateVector
    std::vector<cGate*> gateVector;
// You put on top of the list  the name of the gates to use for the return path (getOtherHalf)
    gateVector.push_back(msg->getArrivalGate()->getOtherHalf());
// We  update the query msg with this vector
    queryMsg->setGateVector(gateVector);
    gateVector.clear();

// Sending query message to processQuery in order to forward to the other CSEs in valley-free manner.
    processQuery(queryMsg);
//    handleDiscoveryMessage(queryMsg);

// delete the AE message
}

/*
 * multicast is used to send messages in a multicast manner through the specified gate,
 * optionally restricting maximal number of messages.
 */
bool CSE::multicast(std::string gateName, discoveryMessage *discoveryMsg, int maxMessages) {

    auto dir = gateToDirection[gateName];
    std::string outGate = gateName + "$o";
    // checking the size of gate
    int t = gateSize(gateName.c_str());
    //if it is greater than zero, it means we have the gate which we want to direct the message.
    if (t <= 0) {
        return false;
    }

    // if it detects the size of the target gate or gates
    int Uri = gate(outGate.c_str(), 0)->getId();
    EV << "uri of destination " << Uri << "\n";
    int vectSize = gate(outGate.c_str(), 0)->getVectorSize();
    // it register in the scheduler map the UR of the CSE and the parameters of the gate
    // we will forward through the vectSize of the gate which have all the target gates

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
//        sendDelayed(msg, delay, outGate.c_str(), i);
        send(msg, outGate.c_str(), i);

        sent++;
    }
//        delete discoveryMsg;
    return sent > 0;
}

/*std::vector<URI> CSE::UpdateBucket(discoveryMessage *msg) {
    std::string feature_type = msg->getFeature_type();
    auto entry = getOrCreateRoutingEntry(feature_type);
    int uri = msg->getSenderModuleId();
    auto f = std::find(entry.CSEBucket.begin(), entry.CSEBucket.end(), uri);
// if the response is positive, we check the URI in the
    if (f != entry.CSEBucket.end()) {
        entry.CSEBucket.insert(entry.CSEBucket.begin(),
                msg->getSenderModuleId());
        return entry.CSEBucket;
    }
    //otherwise
    if (entry.CSEBucket.size() <= 100) {
        entry.CSEBucket.insert(entry.CSEBucket.begin(),
                msg->getSenderModuleId());
        return entry.CSEBucket;
    }
    // otherwise
    int i = entry.CSEBucket.back();
    auto it = this->Gates[i];
    int gateIndex = it.second;
    std::string gateName = it.first + "$o";


    // ping message
    send(ping, gateName.c_str(), gateIndex);

    // after receiving ping
    entry.CSEBucket.pop_back();
    entry.CSEBucket.insert(entry.CSEBucket.begin(), msg->getSenderModuleId());
    return entry.CSEBucket;
    // save the data in Routing Table
    this->SemanticRoutingTable[feature_type] = entry;
}*/

/*
 * getOrCreateRoutingEntry is a primitive to avoid cumbersome map access and entry creation
 * if map element with such key is missing
 */
/*
RoutingEntry CSE::getOrCreateRoutingEntry(std::string feature_type) {
    auto it = this->SemanticRoutingTable.find(feature_type);
    if (it == this->SemanticRoutingTable.end()) {
        return RoutingEntry{};
    }

        return it->second;
}
*/

/*
 * mustGetRoutingEntry is used to always get non-empty routing entry by key.
 * If it fails, fatal error will be thrown.
 */
RoutingEntry CSE::mustGetRoutingEntry(std::string feature_type) {
    auto it = this->SemanticRoutingTable.find(feature_type);
    if (it == this->SemanticRoutingTable.end()) {
        EV_INFO<< "Expected routing entry to exist\n";
        return RoutingEntry { };
    }

    return it->second;
}

/*
 * updateRoutingTableAndNotify is used to update sematic routing table
 * and notify other CSE neighbors (e.g. Customer, Peer, Sibling, Provider)
 */
void CSE::updatingRoutingTableAndNotify(discoveryMessage *msg) {
    std::string feature_type = msg->getFeature_type();
    URI cse = msg->getURI_route();
    int delta = msg->getDelta();
    int direction = msg->getDirection();

//    auto entry = getOrCreateRoutingEntry(feature_type);

    std::string inputGate = msg->getArrivalGate()->getBaseName();
    this->Gates[cse] = std::make_pair(inputGate, msg->getArrivalGate()->getIndex());

    switch (direction) {
    case UP:
        this->SemanticRoutingTable[feature_type].CSECustomer[cse] += delta;
        break;
    case DOWN:
        this->SemanticRoutingTable[feature_type].CSEProvider[cse] += delta;
        break;
    case SIDE_SIBLING:
        this->SemanticRoutingTable[feature_type].CSESibling[cse] += delta;
        break;
    case SIDE_PEER:
        this->SemanticRoutingTable[feature_type].CSEPeer[cse] += delta;
        break;
    }

//    notification depth reached
    if (msg->getHopCount() >= NotificationDepth) {
        EV << "notification depth reached\n";
        return;
    }

    EV << "Redirecting notify\n";

    // notify
    msg->setHopCount(msg->getHopCount() + 1);
    msg->setURI_route(this->Uri);
    notifyNeighbors(msg->dup());
}

// This method (notifyCSE) is used for creating and broadcasting notification message to the neighbors with limited depth (NotificationDepth).

void CSE::notifyCSE(std::string feature_type, int delta) {

//  creating notification message to send to the neighbors.
    auto msg = generateMessage(NOTIFY);

    msg->setFeature_type(feature_type.c_str());
    msg->setHopCount(NotificationDepth);
    msg->setDelta(delta);

// send to CSEs
    notifyNeighbors(msg);
}

/*
 * notifyNeighbors is used to broadcast notification to all neighbors,
 * excluding the neighbor that sent the message to the current CSE.
 * Also, populates gate vector of the message with the arrival gate.
 */
void CSE::notifyNeighbors(discoveryMessage *msg) {
    std::vector<cGate*> gateVector = msg->getGateVector();
    //You update the discoveryMessage with this object
    msg->setGateVector(gateVector);

    if (msg->getArrivalGate() != nullptr) {
        gateVector.push_back(msg->getArrivalGate()->getOtherHalf());
        msg->setGateVector(gateVector);
    }


//    EV << "sending messages to downstream\n";
//    multicast("customer", msg);

//    EV << "sending messages to sidestream\n";
//    multicast("peer", msg);
//    multicast("sibling", msg);

    EV << "sending messages to upstream\n";
    multicast("provider", msg);

    delete msg;
}

/* This method look up for the devices in the CSE in which there is AE which starts the query
 * and returns the result directly
 */
void CSE::localDBLookup(AEMessage *msg) {

    auto feature_type = msg->getFeature_type();

    if(this->SemanticRoutingTable[feature_type].database.size() != 0){

        auto localresponseMsg = generateMessage(RESPONSE);
        localresponseMsg->setDirection(NODIR);
        localresponseMsg->setFeature_type(feature_type);
        localresponseMsg->setURI_init(getId());
//        int lres = this->SemanticRoutingTable[feature_type].database.begin()->first;
//        std::map<int, int> ldbres;
//        ldbres[lres] = 0;
//        EV << "DB Lookup Successful" << "\n";
//        localresponseMsg->setDbResult(ldbres);
        localresponseMsg->setReturnCode(ResultCode::SUCCESS);
        send(localresponseMsg, msg->getArrivalGate()->getOtherHalf()->getId());
        return;
    }
    else {
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
 * DBLookup is used to perform lookup in the semantic routing table for
 * AEs children of the current CSE.
 */
URI CSE::DBLookup(discoveryMessage *msg)
{

    auto feature_type = msg->getFeature_type();
// extracting the feature_type
// if we find the data correspond to the feature_type
    if (this->SemanticRoutingTable[feature_type].database.size() != 0) {
        bubble("Success in database");
        return this->SemanticRoutingTable[feature_type].database.begin()->first;
    }
    else if(this->SemanticRoutingTable[feature_type].CSECustomer.size()!=0) {
        bubble("Success in customer");
        return this->SemanticRoutingTable[feature_type].CSECustomer.begin()->first;
    }
    else if(this->SemanticRoutingTable[feature_type].CSEPeer.size()!=0) {
            bubble("Success in peer");
            return this->SemanticRoutingTable[feature_type].CSEPeer.begin()->first;
    }
    else if(this->SemanticRoutingTable[feature_type].CSESibling.size()!=0) {
            bubble("Success in sibiling");
            return this->SemanticRoutingTable[feature_type].CSESibling.begin()->first;
    }
    else if(this->SemanticRoutingTable[feature_type].CSEProvider.size()!=0) {
            bubble("Success in provider");
            return this->SemanticRoutingTable[feature_type].CSEProvider.begin()->first;
    }
    else
        return NOT_FOUND;
}

/*
 * generateMessage is used to generate message of specified type.
 */
discoveryMessage *CSE::generateMessage(int op_code) {
    switch (op_code) {

    case RESPONSE: {
        int URI_route = getId();
        char msgname[20];
        sprintf(msgname, "Rsp");
        // Create message object and set source and destination field.
        ResMsg = new discoveryMessage(msgname);
        //msg->setPayload("thermometer");
        ResMsg->setOp_code(RESPONSE);
        ResMsg->setURI_route(URI_route);
        return ResMsg;
        break;
    }
    case NOTIFY: {
        int URI_route = getId();
        char msgname[20];
        sprintf(msgname, "Notif");
        // Create message object and set source and destination field.
        NotifMsg = new discoveryMessage(msgname);
        //msg->setPayload("thermometer");
        NotifMsg->setDirection(DOWN);
        NotifMsg->setOp_code(NOTIFY);
        NotifMsg->setURI_route(URI_route);
        NotifMsg->setURI_init(URI_route);
        return NotifMsg;
        break;
    }
    default:
        break;
    }
    return nullptr;
}


//void CSE::orderingMap(std::map<int, int>) {
//    return;
//}
