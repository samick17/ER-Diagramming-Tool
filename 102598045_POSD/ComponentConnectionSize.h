#pragma once

class ComponentConnectionSize{
public:
    static const unsigned int AttributeConnectionSize;//an attribute can only connect to one entity
    static const unsigned int RelationShipConnectionSize;//a relation can connect up to two entity
    static const unsigned int ConnectorConnectionSize;    //connector can connect up to 2 node
};