// Copyright 2020, University of Freiburg
// Authors: Axel Lehmann <lehmann@cs.uni-freiburg.de>.

#ifndef OSM2TTL_CONFIG_CONFIG_H_
#define OSM2TTL_CONFIG_CONFIG_H_

#include <filesystem>
#include <string>
#include <unordered_map>

#include "osm2ttl/ttl/Format.h"
#include "osm2ttl/util/OutputMergeMode.h"

namespace osm2ttl::config {

struct Config {
  // Select what to do
  bool noDump = false;
  bool noContains = false;
  bool storeLocationsOnDisk = false;

  // Select types to dump
  bool noAreaDump = false;
  bool noNodeDump = false;
  bool noRelationDump = false;
  bool noWayDump = false;

  // Select amount to dump
  bool addAreaSources = false;
  bool addEnvelope = false;
  bool addMemberNodes = false;
  bool adminRelationsOnly = false;
  bool expandedData = false;
  bool metaData = false;
  bool skipWikiLinks = false;
  bool addInverseRelationDirection = false;

  // Default settings for data
  std::string osm2ttlPrefix = "osmadd";

  // Dot
  bool writeDotFiles = false;

  // Statistics
  bool writeStatistics = false;
  std::filesystem::path statisticsPath;

  // Output modifiers
  uint16_t wktSimplify = 250;
  uint8_t wktDeviation = 5;
  uint8_t wktPrecision = 12;

  // Output, empty for stdout
  std::filesystem::path output;
  std::string outputFormat;
  osm2ttl::util::OutputMergeMode mergeOutput =
      osm2ttl::util::OutputMergeMode::CONCATENATE;
  bool outputCompress = true;

  // osmium location cache
  std::filesystem::path cache{std::filesystem::temp_directory_path()};

  // Input file
  std::filesystem::path input;

  void load(const std::string& filename);
  void save(const std::string& filename);
  void fromArgs(int argc, char** argv);
  [[nodiscard]] std::string getInfo(std::string_view prefix) const;
  [[nodiscard]] std::filesystem::path getTempPath(const std::string& p,
                                                  const std::string& s) const;
};
}  // namespace osm2ttl::config

#endif  // OSM2TTL_CONFIG_CONFIG_H_
