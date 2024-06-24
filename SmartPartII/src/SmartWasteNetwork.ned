package src;

import omnetpp.*;

simple SmartBin {
    gates:
        inout truck[];
}

simple Truck {
    gates:
        inout bin[];
        inout truck[];
}

simple LocalGateway {
    gates:
        inout bin[];
        inout cse[];
}

simple CentralGateway {
    gates:
        inout cse[];
        inout truck[];
}

network SmartWasteNetwork {
    types:
        channel Channel extends ned.DelayChannel {
            delay = 10ms;
        }

    submodules:
        centralGateway: CentralGateway;
        localGateway[5]: LocalGateway;
        truck[4]: Truck;
        bin[40]: SmartBin;

    connections allowunconnected:
        // Connect bins to local gateways
        for i=0..7 {
            bin[i].truck++ <--> Channel <--> localGateway[0].bin++;
        }
        for i=8..15 {
            bin[i].truck++ <--> Channel <--> localGateway[1].bin++;
        }
        for i=16..23 {
            bin[i].truck++ <--> Channel <--> localGateway[2].bin++;
        }
        for i=24..31 {
            bin[i].truck++ <--> Channel <--> localGateway[3].bin++;
        }
        for i=32..39 {
            bin[i].truck++ <--> Channel <--> localGateway[4].bin++;
        }

        // Connect local gateways to the central gateway
        for j=0..4 {
            localGateway[j].cse++ <--> Channel <--> centralGateway.cse++;
        }

        // Connect central gateway to trucks
        for k=0..3 {
            centralGateway.truck++ <--> Channel <--> truck[k].bin++;
        }

        // Allow trucks to communicate with each other
        truck[0].truck++ <--> Channel <--> truck[1].truck++;
        truck[0].truck++ <--> Channel <--> truck[2].truck++;
        truck[0].truck++ <--> Channel <--> truck[3].truck++;
        truck[1].truck++ <--> Channel <--> truck[2].truck++;
        truck[1].truck++ <--> Channel <--> truck[3].truck++;
        truck[2].truck++ <--> Channel <--> truck[3].truck++;
}
