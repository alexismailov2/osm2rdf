// Copyright 2020, University of Freiburg
// Authors: Axel Lehmann <lehmann@cs.uni-freiburg.de>.

#ifndef OSM2NT_NT_BLANKNODELABEL_H_
#define OSM2NT_NT_BLANKNODELABEL_H_

#include <string>

#include "osm2nt/nt/Object.h"
#include "osm2nt/nt/Subject.h"

namespace osm2nt {
namespace nt {

struct BlankNodeLabel : public Subject, public Object {
 public:
  BlankNodeLabel();
  std::string toString() const;
 protected:
  uint64_t _id;
  static uint64_t _idCounter;
};

}  // namespace nt
}  // namespace osm2nt

#endif  // OSM2NT_NT_BLANKNODELABEL_H_
