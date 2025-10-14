/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#ifndef TRAILBAZE_MATPLOTLIB_RENDERER_H_
#define TRAILBAZE_MATPLOTLIB_RENDERER_H_

#include <filesystem>
#include <fstream>
#include <sstream>

#include "trailblaze/plot/renderer.h"

namespace trailblaze {
namespace plot {

class MatplotlibRenderer final : public renderer {
public:
  explicit MatplotlibRenderer(std::filesystem::path out_py) : out_py_(std::move(out_py)) {}

  void begin_figure(int w, int h) override {
    ss_.str({});
    ss_.clear();
    ss_ << "import matplotlib.pyplot as plt\n"
           "fig = plt.figure(figsize=("
        << (w / 100.0) << ", " << (h / 100.0)
        << "))\n"
           "ax = fig.add_subplot(111)\n";
  }

  void end_figure() override {
    ss_ << "ax.grid(True)\nplt.show()\n";
    std::ofstream f(out_py_);
    f << ss_.str();
  }

  void set_title(std::string_view title) override {
    ss_ << "ax.set_title(" << py_str(title) << ")\n";
  }

  void set_axis_equal(bool equal = true) override {
    if (equal)
      ss_ << "ax.set_aspect('equal', adjustable='box')\n";
  }

  void draw(const polyline_2d& pl) override {
    ss_ << "ax.plot([";
    for (std::size_t i = 0; i < pl.pts.size(); ++i) {
      if (i)
        ss_ << ",";
      ss_ << pl.pts[i][0];
    }
    ss_ << "],[";
    for (std::size_t i = 0; i < pl.pts.size(); ++i) {
      if (i)
        ss_ << ",";
      ss_ << pl.pts[i][1];
    }
    ss_ << "])\n";
  }

  void draw(const polygon_2d& pg) override {
    ss_ << "ax.fill([";
    for (std::size_t i = 0; i < pg.pts.size(); ++i) {
      if (i)
        ss_ << ",";
      ss_ << pg.pts[i][0];
    }
    ss_ << "],[";
    for (std::size_t i = 0; i < pg.pts.size(); ++i) {
      if (i)
        ss_ << ",";
      ss_ << pg.pts[i][1];
    }
    ss_ << "], alpha=0.2)\n";
  }

  void draw(const arrow_2d& ar) override {
    ss_ << "ax.arrow(" << ar.p[0] << "," << ar.p[1] << "," << (ar.q[0] - ar.p[0]) << ","
        << (ar.q[1] - ar.p[1]) << ", length_includes_head=True, head_width=" << ar.head_len
        << ", head_length=" << ar.head_len << ")\n";
  }

  void draw(const text_2d& t) override {
    ss_ << "ax.text(" << t.p[0] << "," << t.p[1] << "," << py_str(t.text) << ", fontsize=" << t.size
        << ")\n";
  }

private:
  static std::string py_str(std::string_view s) {
    std::string q = "'";
    for (char c : s)
      q += (c == '\'' ? "\\'" : std::string(1, c));
    q += "'";
    return q;
  }

  std::filesystem::path out_py_;

  std::ostringstream ss_;
};

} // namespace plot
} // namespace trailblaze

#endif