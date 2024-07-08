cplusplus{{
    #include <map>
    #include <vector>
    //using namespace omnetpp;
    typedef std::map<int,int> DBresult;
    // this has a problem
    typedef std::vector<omnetpp::cGate *> GateVector;
}}

class DBresult { @existingClass; };
class GateVector { @existingClass; };

message discoveryMessage
{
    // ID assigned to QUERY
    int queryID;
    // this is the identifer of the very first AE generating Discovery QUERY
    int URI_init;
    // this is identifer of in route CSE, sending the message to another CSE
    int URI_route;
    // this is type of Resource CSE is looking for. Values can be "waterValve","thermometer","airStation","ATM","smartLock"
    string feature_type; 
	//this can be Registration, update, cancellation, Query, Response, Notify      
    int op_code; 
  	// Indicates result of query
  	int returnCode; 
  	// It can be set to +1 or -1 respectively to add or remove the AEs from routing table. 
  	int delta;
  	// It is used for notification for measuring the depth of notification 
    int hopCount;
    // this will be UP (customer to provider) or DOWN (Provider to Customer)
    // or SIDE (Sibling to Sibling and Peer to Peer). direction where the message has been sent
    int direction;
    // this is the index of the gate from which the request has been sent originator gate.
    int initialGateIndex;
    //This is the result obtained when looking in the local database
    DBresult dbResult;    
    // this is the list that contains the discovery path (list of CSE which forward the query) 
    GateVector gateVector;   
}