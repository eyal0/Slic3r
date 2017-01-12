#include <iostream>
#include "../Surface.hpp"
#include "../ExPolygon.hpp"
#include <memory>
#include "FillBase.hpp"
#include "Flow.hpp"
#include "Geometry.hpp"

/*
Build and run like this:

/usr/bin/g++ -I/usr/lib/perl/5.18/CORE -fPIC -D_REENTRANT -D_GNU_SOURCE -DSLIC3R_HAS_BROKEN_CROAK -DDEBIAN -fstack-protector -fno-strict-aliasing -pipe -I/usr/local/include -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64 -xc++ -Isrc/libslic3r -Isrc/glew/include -D_GLIBCXX_USE_C99 -DHAS_BOOL -DNOGDI -DSLIC3RXS -DBOOST_ASIO_DISABLE_KQUEUE -DGLEW_STATIC -std=c++11 -DBOOST_LIBS -DNDEBUG -Isrc -Ibuildtmp -D_REENTRANT -D_GNU_SOURCE -DDEBIAN -fstack-protector -fno-strict-aliasing -pipe -I/usr/local/include -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64 -g -o TestFillRectilinear2 src/libslic3r/Fill/TestFillRectilinear2.cpp src/libslic3r/Polygon.cpp src/libslic3r/ClipperUtils.cpp src/clipper.cpp src/libslic3r/MultiPoint.cpp src/libslic3r/BoundingBox.cpp src/libslic3r/Polyline.cpp src/libslic3r/Point.cpp src/libslic3r/utils.cpp src/libslic3r/Line.cpp src/libslic3r/ExPolygon.cpp src/libslic3r/Surface.cpp src/libslic3r/Geometry.cpp src/libslic3r/SVG.cpp src/polypartition.cpp src/poly2tri/sweep/cdt.cc src/poly2tri/sweep/sweep.cc src/poly2tri/sweep/sweep_context.cc src/poly2tri/sweep/advancing_front.cc src/poly2tri/common/shapes.cc src/libslic3r/ExPolygonCollection.cpp src/libslic3r/Fill/FillBase.cpp src/libslic3r/Fill/FillConcentric.cpp src/libslic3r/Fill/FillHoneycomb.cpp src/libslic3r/Fill/Fill3DHoneycomb.cpp src/libslic3r/PolylineCollection.cpp src/libslic3r/Fill/Fill.cpp src/libslic3r/Fill/FillPlanePath.cpp src/libslic3r/Layer.cpp src/libslic3r/LayerRegion.cpp src/libslic3r/Flow.cpp src/libslic3r/Fill/FillRectilinear2.cpp src/libslic3r/ExtrusionEntityCollection.cpp src/libslic3r/BridgeDetector.cpp src/libslic3r/SurfaceCollection.cpp src/libslic3r/Config.cpp src/libslic3r/PrintRegion.cpp src/libslic3r/ExtrusionEntity.cpp src/libslic3r/PerimeterGenerator.cpp src/libslic3r/Fill/FillRectilinear.cpp src/libslic3r/PrintConfig.cpp && ./TestFillRectilinear2

*/
int main() {
  Slic3r::Point p1{0,0};
  Slic3r::Point p2{50000000,0};
  Slic3r::Point p3{50000000,50000000};
  Slic3r::Point p4{0,50000000};
  Slic3r::Points points1{p1,p2,p3,p4};
  Slic3r::Polygon polygon1{points1};
  Slic3r::ExPolygon expolygon1{polygon1};
  std::cout << expolygon1.dump_perl();
  std::unique_ptr<Fill> f = std::unique_ptr<Fill>(Fill::new_from_type(ipRectilinear));
  f->set_bounding_box(expolygon1.contour.bounding_box());
  f->angle = 0;
  Surface s(stTop, expolygon1);
  Flow flow(0.69, 0.4, 0.50);
  f->spacing = flow.spacing();
  s.expolygon.rotate(Slic3r::Geometry::deg2rad(0), p1);
  FillParams fill_params;
  fill_params.density = 0.4;
  printf("Fill surface result: %ld\n", f->fill_surface(&s, fill_params).size());
  //ExPolygon e1;
  //printf("%d", e1.is_valid());
      // Surface surface(Surfacetype::stTop, ExPolygon;
  return 0;
}
