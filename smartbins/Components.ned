
//===================================================COMPONENTS==================================================

simple CSE
{
        parameters:
        @signal[packet_size](type="long");
        @statistic[throughput](title="total_number_of_packets"; source="packet_size"; record=vector,last);
        @display("i=abstract/router,blue,9");
        int notification_depth = default(8);
        int alpha = default(0); // Sidestream multicast parameter (p2p)   ?? Peer
        int beta = default(1);  // Upstream multicast parameter (c2p)     ?? Provider
        int delta = default(1); // Downstream multicast parameter (p2c)   ?? Customer
        int gamma = default(1); // Sidestream multicast parameter (s2s)   ?? Sibiling
        int queryBufferTTL = default(2);
        int maxHops = default(10);
        //volatile double sendInterval @unit(s);
        volatile double delayTime = default(0);

    gates:
        // TODO Peering links handling has to be implemented
        inout provider[] @loose;
        inout customer[] @loose;
        inout sibling[] @loose;
        inout peer[] @loose;
        inout ae[] @loose;
}

simple AE
{
    parameters:
        int aeType;
        @display("i=misc/node,#0080FF,23;is=s");
    gates:
        inout cse @loose;
}