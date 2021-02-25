// Copyright 2020, University of Freiburg
// Authors: Axel Lehmann <lehmann@cs.uni-freiburg.de>.

#include "osm2ttl/osm/Box.h"

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include "gtest/gtest.h"
#include "osm2ttl/geometry/Box.h"
#include "osm2ttl/geometry/Location.h"
#include "osmium/builder/attr.hpp"
#include "osmium/builder/osm_object_builder.hpp"

namespace osm2ttl::osm {

TEST(OSM_Box, FromGeometryBox) {
  osm2ttl::geometry::Box b;
  b.min_corner() = osm2ttl::geometry::Location{50, 50};
  b.max_corner() = osm2ttl::geometry::Location{200, 200};
  osm2ttl::osm::Box o(b);

  ASSERT_TRUE(o.geom().min_corner() == b.min_corner());
  ASSERT_TRUE(o.geom().max_corner() == b.max_corner());
}

TEST(OSM_Box, equalsOperator) {
  osm2ttl::geometry::Box b1;
  b1.min_corner() = osm2ttl::geometry::Location{50, 50};
  b1.max_corner() = osm2ttl::geometry::Location{200, 200};
  osm2ttl::osm::Box o1(b1);

  osm2ttl::geometry::Box b2;
  b2.min_corner() = osm2ttl::geometry::Location{50, 200};
  b2.max_corner() = osm2ttl::geometry::Location{200, 200};
  osm2ttl::osm::Box o2(b2);

  osm2ttl::geometry::Box b3;
  b3.min_corner() = osm2ttl::geometry::Location{200, 200};
  b3.max_corner() = osm2ttl::geometry::Location{50, 50};
  osm2ttl::osm::Box o3(b3);

  ASSERT_TRUE(o1 == o1);
  ASSERT_FALSE(o1 == o2);
  ASSERT_FALSE(o1 == o3);

  ASSERT_FALSE(o2 == o1);
  ASSERT_TRUE(o2 == o2);
  ASSERT_FALSE(o2 == o3);

  ASSERT_FALSE(o3 == o1);
  ASSERT_FALSE(o3 == o2);
  ASSERT_TRUE(o3 == o3);
}

TEST(OSM_Box, notEqualsOperator) {
  osm2ttl::geometry::Box b1;
  b1.min_corner() = osm2ttl::geometry::Location{50, 50};
  b1.max_corner() = osm2ttl::geometry::Location{200, 200};
  osm2ttl::osm::Box o1(b1);

  osm2ttl::geometry::Box b2;
  b2.min_corner() = osm2ttl::geometry::Location{50, 200};
  b2.max_corner() = osm2ttl::geometry::Location{200, 200};
  osm2ttl::osm::Box o2(b2);

  osm2ttl::geometry::Box b3;
  b3.min_corner() = osm2ttl::geometry::Location{200, 200};
  b3.max_corner() = osm2ttl::geometry::Location{50, 50};
  osm2ttl::osm::Box o3(b3);

  ASSERT_FALSE(o1 != o1);
  ASSERT_TRUE(o1 != o2);
  ASSERT_TRUE(o1 != o3);

  ASSERT_TRUE(o2 != o1);
  ASSERT_FALSE(o2 != o2);
  ASSERT_TRUE(o2 != o3);

  ASSERT_TRUE(o3 != o1);
  ASSERT_TRUE(o3 != o2);
  ASSERT_FALSE(o3 != o3);
}

TEST(OSM_Box, serializationBinary) {
  std::stringstream boostBuffer;

  osm2ttl::geometry::Box b1;
  b1.min_corner() = osm2ttl::geometry::Location{50, 50};
  b1.max_corner() = osm2ttl::geometry::Location{200, 200};
  const osm2ttl::osm::Box src(b1);

  osm2ttl::osm::Box dst;

  // Store and load
  boost::archive::binary_oarchive oa(boostBuffer);
  oa << src;
  // std::cerr << buffer.str() << std::endl;
  boost::archive::binary_iarchive ia(boostBuffer);
  ia >> dst;

  // Compare
  ASSERT_TRUE(src == dst);
}

TEST(OSM_Box, serializationText) {
  std::stringstream boostBuffer;

  osm2ttl::geometry::Box b1;
  b1.min_corner() = osm2ttl::geometry::Location{50, 50};
  b1.max_corner() = osm2ttl::geometry::Location{200, 200};
  const osm2ttl::osm::Box src(b1);

  osm2ttl::osm::Box dst;

  // Store and load
  boost::archive::text_oarchive oa(boostBuffer);
  oa << src;
  // std::cerr << buffer.str() << std::endl;
  boost::archive::text_iarchive ia(boostBuffer);
  ia >> dst;

  // Compare
  ASSERT_TRUE(src == dst);
}

}  // namespace osm2ttl::osm