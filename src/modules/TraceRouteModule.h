#pragma once
#include "ProtobufModule.h"


/**
 * A module that traces the route to a certain destination node
 */
class TraceRouteModule : public ProtobufModule<RouteDiscovery>
{
    public:
        TraceRouteModule();

        // Let FloodingRouter call updateRoute upon rebroadcasting a TraceRoute request
        friend class FloodingRouter;

    protected:
        bool handleReceivedProtobuf(const MeshPacket &mp, RouteDiscovery *r) override;

        virtual MeshPacket *allocReply() override;

        /* Call before rebroadcasting a RouteDiscovery payload in order to update 
           the route array containing the IDs of nodes this packet went through */
        void updateRoute(MeshPacket* p);
    
    private:
        // Call to add your ID to the route array of a RouteDiscovery message
        void appendMyID(RouteDiscovery *r);

        /* Call to print the route array of a RouteDiscovery message.
           Set origin to where the request came from.
           Set dest to the ID of its destination, or NODENUM_BROADCAST if it has not yet arrived there. */
        void printRoute(RouteDiscovery* r, uint32_t origin, uint32_t dest); 

};

extern TraceRouteModule *traceRouteModule;