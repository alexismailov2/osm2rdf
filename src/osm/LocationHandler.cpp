// Copyright 2020, University of Freiburg
// Authors: Axel Lehmann <lehmann@cs.uni-freiburg.de>.

// This file is part of osm2rdf.
//
// osm2rdf is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// osm2rdf is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with osm2rdf.  If not, see <https://www.gnu.org/licenses/>.

#include "osm2rdf/osm/LocationHandler.h"

#include <iostream>

#include "osm2rdf/config/Config.h"
#include "osmium/handler/node_locations_for_ways.hpp"
#include "osmium/index/map/dense_file_array.hpp"
#include "osmium/index/map/flex_mem.hpp"
#include "osmium/index/map/sparse_file_array.hpp"

// ____________________________________________________________________________
osm2rdf::osm::LocationHandler* osm2rdf::osm::LocationHandler::create(
    const osm2rdf::config::Config& config) {
  if (config.storeLocationsOnDisk == "sparse") {
    return new osm2rdf::osm::LocationHandlerFSSparse(config);
  }

  if (config.storeLocationsOnDisk == "dense") {
    return new osm2rdf::osm::LocationHandlerFSDense(config);
  }

  return new osm2rdf::osm::LocationHandlerRAM(config);
}

// ____________________________________________________________________________
template <typename T>
osmium::Location osm2rdf::osm::LocationHandlerImpl<T>::get_node_location(
    const osmium::object_id_type nodeId) const {
  return _handler.get_node_location(nodeId);
}

// ____________________________________________________________________________
template <typename T>
void osm2rdf::osm::LocationHandlerImpl<T>::node(const osmium::Node& node) {
  _handler.node(node);
}

// ____________________________________________________________________________
template <typename T>
void osm2rdf::osm::LocationHandlerImpl<T>::way(osmium::Way& way) {
  _handler.way(way);
}

// ____________________________________________________________________________
template <typename T>
osm2rdf::osm::LocationHandlerImpl<T>::LocationHandlerImpl(
    const osm2rdf::config::Config& /*unused*/)
    : _handler(_index) {
  _handler.ignore_errors();
}

// ____________________________________________________________________________
osm2rdf::osm::LocationHandlerImpl<osmium::index::map::SparseFileArray<
    osmium::unsigned_object_id_type, osmium::Location>>::
    LocationHandlerImpl(const osm2rdf::config::Config& config)
    : _cacheFile(config.getTempPath("osmium", "n2l.sparse.cache")),
      _index(_cacheFile.fileDescriptor()),
      _handler(_index) {
  _handler.ignore_errors();
}

// ____________________________________________________________________________
osmium::Location
osm2rdf::osm::LocationHandlerImpl<osmium::index::map::SparseFileArray<
    osmium::unsigned_object_id_type, osmium::Location>>::
    get_node_location(const osmium::object_id_type nodeId) const {
  return _handler.get_node_location(nodeId);
}

// ____________________________________________________________________________
void osm2rdf::osm::LocationHandlerImpl<osmium::index::map::SparseFileArray<
    osmium::unsigned_object_id_type,
    osmium::Location>>::node(const osmium::Node& node) {
  _handler.node(node);
}

// ____________________________________________________________________________
void osm2rdf::osm::LocationHandlerImpl<osmium::index::map::SparseFileArray<
    osmium::unsigned_object_id_type,
    osmium::Location>>::way(osmium::Way& way) {
  _handler.way(way);
}

// ____________________________________________________________________________
osm2rdf::osm::LocationHandlerImpl<osmium::index::map::DenseFileArray<
    osmium::unsigned_object_id_type, osmium::Location>>::
    LocationHandlerImpl(const osm2rdf::config::Config& config)
    : _cacheFile(config.getTempPath("osmium", "n2l.dense.cache")),
      _index(_cacheFile.fileDescriptor()),
      _handler(_index) {
  _handler.ignore_errors();
}

// ____________________________________________________________________________
void osm2rdf::osm::LocationHandlerImpl<osmium::index::map::DenseFileArray<
    osmium::unsigned_object_id_type,
    osmium::Location>>::node(const osmium::Node& node) {
  _handler.node(node);
}

// ____________________________________________________________________________
void osm2rdf::osm::LocationHandlerImpl<osmium::index::map::DenseFileArray<
    osmium::unsigned_object_id_type,
    osmium::Location>>::way(osmium::Way& way) {
  _handler.way(way);
}

// ____________________________________________________________________________
osmium::Location
osm2rdf::osm::LocationHandlerImpl<osmium::index::map::DenseFileArray<
    osmium::unsigned_object_id_type, osmium::Location>>::
    get_node_location(const osmium::object_id_type nodeId) const {
  return _handler.get_node_location(nodeId);
}
