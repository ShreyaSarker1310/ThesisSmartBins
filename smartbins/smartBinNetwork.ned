network SmartBinNetwork
{
    @display("bgb=500,1000");
    types:
        channel Channel extends ned.DelayChannel
        {
            delay = 100ms;
        }

    submodules:
        CSE_in[1]: CSE {
            @display("p=250,400;i=abstract/router,blue,9");
        }
        CSE_mn[5]: CSE;
        AE_sb[32]: AE {
            aeType = 0;
            @display("i=smartbins/bin;is=n");
        }
        AE_st[1]: AE {
            aeType = 1;
            @display("p=200,700;i=smartbins/truck;is=n");
        }
        AE_sw[1]: AE {
            aeType = 2;
            @display("p=250,700;i=smartbins/incineration;is=n");
        }
    connections allowunconnected:
        for i=0..7 {
            CSE_mn[0].ae++ <--> Channel <--> AE_sb[i].cse;
        }

        for i=8..15 {
            CSE_mn[1].ae++ <--> Channel <--> AE_sb[i].cse;
        }
        
        for i=16..23 {
            CSE_mn[2].ae++ <--> Channel <--> AE_sb[i].cse;
        }
                
        for i=24..31 {
            CSE_mn[3].ae++ <--> Channel <--> AE_sb[i].cse;
        }
        
        CSE_mn[4].ae++ <--> Channel <--> AE_st[0].cse;
        CSE_mn[4].ae++ <--> Channel <--> AE_sw[0].cse;

        for j=0..4 {
            CSE_mn[j].provider++ <--> Channel <--> CSE_in[0].customer++;
        }

}