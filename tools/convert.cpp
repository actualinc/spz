#include <iostream>
#include "load-spz.h"

int main(int argc, char* argv[]) {
  if (argc < 3) {
    std::cerr << "Usage: convert <input.ply> <output.spz>\n";
    return 1;
  }

  spz::UnpackOptions uopts;
  spz::GaussianCloud gc = spz::loadSplatFromPly(argv[1], uopts);
  if (gc.numPoints == 0) {
    std::cerr << "❌ PLY load failed or empty: " << argv[1] << "\n";
    return 1;
  }

  spz::PackOptions popts;
  bool ok = spz::saveSpz(gc, popts, std::string(argv[2]));
  if (!ok) {
    std::cerr << "❌ SPZ write failed: " << argv[2] << "\n";
    return 1;
  }

  std::cout << "✅ Saved SPZ: " << argv[2] << "\n";
  return 0;
}
