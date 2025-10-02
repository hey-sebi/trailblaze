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

class MatplotlibRenderer final : public Renderer
{
 public:
  explicit MatplotlibRenderer(std::filesystem::path out_py) : out_py_(std::move(out_py))
  {
  }

  void BeginFigure(int w, int h) override
  {
    ss_.str({});
    ss_.clear();
    ss_ << "import matplotlib.pyplot as plt\n"
           "fig = plt.figure(figsize=("
        << (w / 100.0) << ", " << (h / 100.0)
        << "))\n"
           "ax = fig.add_subplot(111)\n";
  }

  void EndFigure() override
  {
    ss_ << "ax.grid(True)\nplt.show()\n";
    std::ofstream f(out_py_);
    f << ss_.str();
  }

  void SetTitle(std::string title) override
  {
    ss_ << "ax.set_title(" << PyStr(title) << ")\n";
  }

  void SetAxisEqual(bool equal = true) override
  {
    if (equal)
      ss_ << "ax.set_aspect('equal', adjustable='box')\n";
  }

  void Draw(const Polyline2D& pl) override
  {
    ss_ << "ax.plot([";
    for (std::size_t i = 0; i < pl.pts.size(); ++i)
    {
      if (i)
        ss_ << ",";
      ss_ << pl.pts[i][0];
    }
    ss_ << "],[";
    for (std::size_t i = 0; i < pl.pts.size(); ++i)
    {
      if (i)
        ss_ << ",";
      ss_ << pl.pts[i][1];
    }
    ss_ << "])\n";
  }

  void Draw(const Polygon2D& pg) override
  {
    ss_ << "ax.fill([";
    for (std::size_t i = 0; i < pg.pts.size(); ++i)
    {
      if (i)
        ss_ << ",";
      ss_ << pg.pts[i][0];
    }
    ss_ << "],[";
    for (std::size_t i = 0; i < pg.pts.size(); ++i)
    {
      if (i)
        ss_ << ",";
      ss_ << pg.pts[i][1];
    }
    ss_ << "], alpha=0.2)\n";
  }

  void Draw(const Arrow2D& ar) override
  {
    ss_ << "ax.arrow(" << ar.p[0] << "," << ar.p[1] << "," << (ar.q[0] - ar.p[0]) << ","
        << (ar.q[1] - ar.p[1])
        << ", length_includes_head=True, head_width=" << ar.head_len
        << ", head_length=" << ar.head_len << ")\n";
  }

  void Draw(const Text2D& t) override
  {
    ss_ << "ax.text(" << t.p[0] << "," << t.p[1] << "," << PyStr(t.text)
        << ", fontsize=" << t.size << ")\n";
  }

 private:
  static std::string PyStr(const std::string& s)
  {
    std::string q = "'";
    for (char c : s) q += (c == '\'' ? "\\'" : std::string(1, c));
    q += "'";
    return q;
  }

  std::filesystem::path out_py_;
  std::ostringstream ss_;
};

}  // namespace plot
}  // namespace trailblaze

#endif