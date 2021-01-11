// Copyright 2020, University of Freiburg
// Authors: Axel Lehmann <lehmann@cs.uni-freiburg.de>.

#ifndef OSM2TTL_OSM_GEOMETRYHANDLER_H_
#define OSM2TTL_OSM_GEOMETRYHANDLER_H_

#include <unordered_map>
#include <utility>
#include <vector>
#include <stxxl.h>

#include "boost/geometry/index/rtree.hpp"
#include "osm2ttl/config/Config.h"
#include "osm2ttl/geometry/Area.h"
#include "osm2ttl/geometry/Location.h"
#include "osm2ttl/geometry/Node.h"
#include "osm2ttl/geometry/Way.h"
#include "osm2ttl/osm/Area.h"
#include "osm2ttl/ttl/Writer.h"
#include "osm2ttl/util/CacheFile.h"
#include "osm2ttl/util/DirectedGraph.h"
#include "osm2ttl/util/Output.h"
#include "osmium/handler.hpp"
#include "osmium/handler/node_locations_for_ways.hpp"
#include "osmium/index/map/sparse_file_array.hpp"
#include "osmium/osm/area.hpp"
#include "osmium/osm/node.hpp"
#include "osmium/osm/relation.hpp"
#include "osmium/osm/way.hpp"


namespace osm2ttl {
namespace osm {

typedef std::tuple<osm2ttl::geometry::Box, osm2ttl::osm::Area::id_t,
                   osm2ttl::geometry::Area, osm2ttl::osm::Area::id_t,
                   osm2ttl::geometry::area_result_t, bool>
    SpatialAreaValue;

typedef stxxl::vector<SpatialAreaValue> SpatialAreaVector;
//typedef std::vector<SpatialAreaValue> SpatialAreaVector;

typedef std::tuple<osm2ttl::geometry::Box, osm2ttl::osm::Node::id_t,
                   osm2ttl::geometry::Node>
    SpatialNodeValue;
typedef stxxl::vector<SpatialNodeValue> SpatialNodeVector;
//typedef std::vector<SpatialNodeValue> SpatialNodeVector;

typedef std::vector<osm2ttl::osm::Node::id_t> WayNodeList;
typedef std::tuple<osm2ttl::geometry::Box, osm2ttl::osm::Way::id_t,
                   osm2ttl::geometry::Way, WayNodeList>
    SpatialWayValue;
typedef stxxl::vector<SpatialWayValue> SpatialWayVector;
//typedef std::vector<SpatialWayValue> SpatialWayVector;

typedef boost::geometry::index::rtree<SpatialAreaValue,
                                      boost::geometry::index::quadratic<16>>
    SpatialIndex;

typedef std::unordered_map<osm2ttl::osm::Node::id_t,
                           std::vector<osm2ttl::osm::Area::id_t>>
    NodesContainedInAreasData;

template <typename W>
class GeometryHandler : public osmium::handler::Handler {
 public:
  GeometryHandler(const osm2ttl::config::Config& config,
                  osm2ttl::ttl::Writer<W>* writer);

  // Store data
  void area(const osm2ttl::osm::Area& area);
  void node(const osm2ttl::osm::Node& node);
  void way(const osm2ttl::osm::Way& way);
  // Calculate data
  void calculateRelations();

 protected:
  // Stores named areas in r-tree, used for all other calculations.
  void prepareRTree();
  // Generate DAG for areas using prepared r-tree.
  void prepareDAG();
  // Calculate relations for each area, this dumps the generated DAG.
  void dumpNamedAreaRelations();
  // Calculate relations for each node.
  NodesContainedInAreasData dumpNodeRelations();
  // Calculate relations for each way.
  void dumpRelationRelations(
      const osm2ttl::osm::NodesContainedInAreasData& nodeData);
  // Calculate relations for each area, this dumps the generated DAG.
  void dumpUnnamedAreaRelations();
  std::string statisticLine(std::string_view function, std::string_view part,
                            std::string_view check, uint64_t outerId,
                            std::string_view outerType, uint64_t innerId,
                            std::string_view innerType,
                            std::chrono::nanoseconds durationNS, bool result);
  // Global config
  osm2ttl::config::Config _config;
  osm2ttl::ttl::Writer<W>* _writer;
  // Statistics
  osm2ttl::util::Output _statistics;
  // Store areas as r-tree
  SpatialIndex spatialIndex;
  // Store dag
  osm2ttl::util::DirectedGraph<osm2ttl::osm::Area::id_t> directedAreaGraph;
  // Spatial Data
  SpatialAreaVector _spatialStorageArea;
  std::unordered_map<osm2ttl::osm::Area::id_t, uint64_t>
      _spatialStorageAreaIndex;

  SpatialAreaVector _spatialStorageUnnamedArea;

  SpatialNodeVector _spatialStorageNode;

  SpatialWayVector _spatialStorageWay;
};

}  // namespace osm
}  // namespace osm2ttl

#endif  // OSM2TTL_OSM_GEOMETRYHANDLER_H_
