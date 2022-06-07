#include <fstream>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/algorithm/string.hpp>

typedef boost::geometry::model::d2::point_xy<double> Point;
typedef boost::geometry::model::polygon<Point> Polygon;
typedef boost::geometry::model::multi_polygon<Polygon> MultiPolygon;

int main(int argc, char* argv[]) {
  if (argc < 3) {
    std::cerr << "Usage: " << argv[0] << " <multipolygon A wkt file> <multipolygon B wkt file>" << std::endl;
    exit(2);
  }

  std::ifstream a(argv[1]);
  std::ifstream b(argv[2]);

  std::stringstream ssA, ssB;
  ssA << a.rdbuf();
  ssB << b.rdbuf();

  auto wktA = ssA.str();
  auto wktB = ssB.str();

  // strip!
  boost::trim(wktA);
  boost::trim(wktB);

  MultiPolygon ap, bp;

  boost::geometry::read_wkt(wktA, ap);
  boost::geometry::read_wkt(wktB, bp);

  if (boost::geometry::covered_by(ap, bp)) exit(0);
  exit(1);
}
