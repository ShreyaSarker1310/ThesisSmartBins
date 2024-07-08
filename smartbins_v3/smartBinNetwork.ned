network SmartBinNetwork
{
    types:
        channel Channel extends ned.DelayChannel
        {
            delay = 100ms;
        }

    submodules:        
        AE_sb_1: AE {
            aeType = 0;
            queryType = 0;
            @display("p=100,0;i=smartbins/bin;is=n");
        }
        AE_sb_2: AE {
            aeType = 0;            
            queryType = 0;
            @display("p=150,0;i=smartbins/bin;is=n");
        }        
        AE_sb_3: AE {
            aeType = 0;            
            queryType = 0;
            @display("p=200,0;i=smartbins/bin;is=n");
        }                
        AE_sb_4: AE {
            aeType = 0;            
            queryType = 0;
            @display("p=100,50;i=smartbins/bin;is=n");
        }
        AE_sb_5: AE {
            aeType = 0;            
            queryType = 0;
            @display("p=200,50;i=smartbins/bin;is=n");
        }        
        AE_sb_6: AE {
            aeType = 0;            
            queryType = 0;
            @display("p=100,100;i=smartbins/bin;is=n");
        }
        AE_sb_7: AE {
            aeType = 0;            
            queryType = 0;
            @display("p=150,100;i=smartbins/bin;is=n");
        }
        AE_sb_8: AE {
            aeType = 0;            
            queryType = 0;
            @display("p=200,100;i=smartbins/bin;is=n");
        }
        CSE_mn_1: CSE {
            notification_depth = 8;
            @display("p=150,50;i=abstract/router,blue,9");            
        }
        
        
        AE_sb_9: AE {
            aeType = 0;            
            queryType = 0;
            @display("p=300,0;i=smartbins/bin;is=n");
        }
        AE_sb_10: AE {
            aeType = 0;            
            queryType = 0;
            @display("p=350,0;i=smartbins/bin;is=n");
        }        
        AE_sb_11: AE {
            aeType = 0;            
            queryType = 0;
            @display("p=400,0;i=smartbins/bin;is=n");
        }                
        AE_sb_12: AE {
            aeType = 0;            
            queryType = 0;
            @display("p=300,50;i=smartbins/bin;is=n");
        }
        AE_sb_13: AE {
            aeType = 0;            
            queryType = 0;
            @display("p=400,50;i=smartbins/bin;is=n");
        }        
        AE_sb_14: AE {
            aeType = 0;            
            queryType = 0;
            @display("p=300,100;i=smartbins/bin;is=n");
        }
        AE_sb_15: AE {
            aeType = 0;           
            queryType = 0;
            @display("p=350,100;i=smartbins/bin;is=n");
        }
        AE_sb_16: AE {
            aeType = 0;            
            queryType = 0;
            @display("p=400,100;i=smartbins/bin;is=n");
        }
        CSE_mn_2: CSE {
            notification_depth = 8;
            @display("p=350,50;i=abstract/router,blue,9");            
        }


        AE_sb_17: AE {
            aeType = 0;            
            queryType = 0;
            @display("p=100,200;i=smartbins/bin;is=n");
        }
        AE_sb_18: AE {
            aeType = 0;            
            queryType = 0;
            @display("p=150,200;i=smartbins/bin;is=n");
        }        
        AE_sb_19: AE {
            aeType = 0;            
            queryType = 0;
            @display("p=200,200;i=smartbins/bin;is=n");
        }                
        AE_sb_20: AE {
            aeType = 0;            
            queryType = 0;
            @display("p=100,250;i=smartbins/bin;is=n");
        }
        AE_sb_21: AE {
            aeType = 0;            
            queryType = 0;
            @display("p=200,250;i=smartbins/bin;is=n");
        }        
        AE_sb_22: AE {
            aeType = 0;            
            queryType = 0;
            @display("p=100,300;i=smartbins/bin;is=n");
        }
        AE_sb_23: AE {
            aeType = 0;            
            queryType = 0;
            @display("p=150,300;i=smartbins/bin;is=n");
        }
        AE_sb_24: AE {
            aeType = 0;            
            queryType = 0;
            @display("p=200,300;i=smartbins/bin;is=n");
        }
        CSE_mn_3: CSE {
            notification_depth = 8;            
            @display("p=150,250;i=abstract/router,blue,9");            
        }
        
        
        AE_sb_25: AE {
            aeType = 0;            
            queryType = 0;
            @display("p=300,200;i=smartbins/bin;is=n");
        }
        AE_sb_26: AE {
            aeType = 0;            
            queryType = 0;
            @display("p=350,200;i=smartbins/bin;is=n");
        }        
        AE_sb_27: AE {
            aeType = 0;            
            queryType = 0;
            @display("p=400,200;i=smartbins/bin;is=n");
        }                
        AE_sb_28: AE {
            aeType = 0;            
            queryType = 0;
            @display("p=300,250;i=smartbins/bin;is=n");
        }
        AE_sb_29: AE {
            aeType = 0;            
            queryType = 0;
            @display("p=400,250;i=smartbins/bin;is=n");
        }        
        AE_sb_30: AE {
            aeType = 0;            
            queryType = 0;
            @display("p=300,300;i=smartbins/bin;is=n");
        }
        AE_sb_31: AE {
            aeType = 0;            
            queryType = 0;
            @display("p=350,300;i=smartbins/bin;is=n");
        }
        AE_sb_32: AE {
            aeType = 0;            
            queryType = 0;
            @display("p=400,300;i=smartbins/bin;is=n");
        }
        CSE_mn_4: CSE {
            notification_depth = 8;
            @display("p=350,250;i=abstract/router,blue,9");            
        }
        
        
        CSE_in_1: CSE {
            notification_depth = 50;
            delta = 4;
            @display("p=250,400;i=abstract/router,blue,9");
        }
        
        AE_st_1: AE {
            aeType = 1;
            queryType = 0;
            @display("p=150,500;i=smartbins/truck;is=n");            
        }
        AE_st_2: AE {
            aeType = 1;
            queryType = 0;
            @display("p=200,500;i=smartbins/truck;is=n");            
        }
        AE_st_3: AE {
            aeType = 1;
            queryType = 0;
            @display("p=250,500;i=smartbins/truck;is=n");            
        }
        AE_st_4: AE {
            aeType = 1;
            queryType = 0;
            @display("p=300,500;i=smartbins/truck;is=n");            
        }
                                         
        AE_sw_1: AE {
            aeType = 2;
            queryType = 1;
            @display("p=350,500;i=smartbins/incineration;is=n");
        }
        
    connections allowunconnected:
        CSE_mn_1.ae++ <--> Channel <--> AE_sb_1.cse;
        CSE_mn_1.ae++ <--> Channel <--> AE_sb_2.cse;
        CSE_mn_1.ae++ <--> Channel <--> AE_sb_3.cse;
        CSE_mn_1.ae++ <--> Channel <--> AE_sb_4.cse;
        CSE_mn_1.ae++ <--> Channel <--> AE_sb_5.cse;
        CSE_mn_1.ae++ <--> Channel <--> AE_sb_6.cse;
        CSE_mn_1.ae++ <--> Channel <--> AE_sb_7.cse;
        CSE_mn_1.ae++ <--> Channel <--> AE_sb_8.cse;

        CSE_mn_2.ae++ <--> Channel <--> AE_sb_9.cse;
        CSE_mn_2.ae++ <--> Channel <--> AE_sb_10.cse;
        CSE_mn_2.ae++ <--> Channel <--> AE_sb_11.cse;
        CSE_mn_2.ae++ <--> Channel <--> AE_sb_12.cse;
        CSE_mn_2.ae++ <--> Channel <--> AE_sb_13.cse;
        CSE_mn_2.ae++ <--> Channel <--> AE_sb_14.cse;
        CSE_mn_2.ae++ <--> Channel <--> AE_sb_15.cse;
        CSE_mn_2.ae++ <--> Channel <--> AE_sb_16.cse;
        
        CSE_mn_3.ae++ <--> Channel <--> AE_sb_17.cse;
        CSE_mn_3.ae++ <--> Channel <--> AE_sb_18.cse;
        CSE_mn_3.ae++ <--> Channel <--> AE_sb_19.cse;
        CSE_mn_3.ae++ <--> Channel <--> AE_sb_20.cse;
        CSE_mn_3.ae++ <--> Channel <--> AE_sb_21.cse;
        CSE_mn_3.ae++ <--> Channel <--> AE_sb_22.cse;
        CSE_mn_3.ae++ <--> Channel <--> AE_sb_23.cse;
        CSE_mn_3.ae++ <--> Channel <--> AE_sb_24.cse;        

        CSE_mn_4.ae++ <--> Channel <--> AE_sb_25.cse;
        CSE_mn_4.ae++ <--> Channel <--> AE_sb_26.cse;
        CSE_mn_4.ae++ <--> Channel <--> AE_sb_27.cse;
        CSE_mn_4.ae++ <--> Channel <--> AE_sb_28.cse;
        CSE_mn_4.ae++ <--> Channel <--> AE_sb_29.cse;
        CSE_mn_4.ae++ <--> Channel <--> AE_sb_30.cse;
        CSE_mn_4.ae++ <--> Channel <--> AE_sb_31.cse;
        CSE_mn_4.ae++ <--> Channel <--> AE_sb_32.cse;
        
        CSE_in_1.ae++ <--> Channel <--> AE_st_1.cse;
        CSE_in_1.ae++ <--> Channel <--> AE_st_2.cse;
        CSE_in_1.ae++ <--> Channel <--> AE_st_3.cse;
        CSE_in_1.ae++ <--> Channel <--> AE_st_4.cse;
        CSE_in_1.ae++ <--> Channel <--> AE_sw_1.cse;
        
        CSE_mn_1.provider++ <--> Channel <--> CSE_in_1.customer++;
        CSE_mn_2.provider++ <--> Channel <--> CSE_in_1.customer++;
        CSE_mn_3.provider++ <--> Channel <--> CSE_in_1.customer++;
        CSE_mn_4.provider++ <--> Channel <--> CSE_in_1.customer++;
}
