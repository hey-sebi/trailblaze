/* ------------------------------------------------------------------------
 * Copyright(c) 2024-present, Sebastian Klemm & contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */
#pragma once

#include <filesystem>
#include <fstream>
#include <sstream>

#include "trailblaze/plot/renderer.h"

namespace trailblaze::plot {

class matplotlib_renderer final : public renderer {
public:
  explicit matplotlib_renderer(std::filesystem::path out_filepath)
      : out_filepath_(std::move(out_filepath)) {}

  void begin_figure(int width, int height) override {
    ss_.str({});
    ss_.clear();
    ss_ << "import matplotlib.pyplot as plt\n"
           "fig = plt.figure(figsize=("
        << (width / 100.0) << ", " << (height / 100.0)
        << "))\n"
           "ax = fig.add_subplot(111)\n";
  }

  void end_figure() override {
    ss_ << "ax.grid(True)\nplt.show()\n";
    std::ofstream file(out_filepath_);
    file << ss_.str();
  }

  void set_title(std::string_view title) override {
    ss_ << "ax.set_title(" << py_str(title) << ")\n";
  }

  void set_axis_equal(bool equal = true) override {
    if (equal) {
      ss_ << "ax.set_aspect('equal', adjustable='box')\n";
    }
  }

  void draw(const polyline_2d& polyline) override {
    ss_ << "ax.plot([";
    for (std::size_t i = 0; i < polyline.pts.size(); ++i) {
      if (i != 0) {
        ss_ << ",";
      }
      ss_ << polyline.pts[i][0];
    }
    ss_ << "],[";
    for (std::size_t i = 0; i < polyline.pts.size(); ++i) {
      if (i != 0) {
        ss_ << ",";
      }
      ss_ << polyline.pts[i][1];
    }
    ss_ << "])\n";
  }

  void draw(const polygon_2d& polygon) override {
    ss_ << "ax.fill([";
    for (std::size_t i = 0; i < polygon.pts.size(); ++i) {
      if (i)
        ss_ << ",";
      ss_ << polygon.pts[i][0];
    }
    ss_ << "],[";
    for (std::size_t i = 0; i < polygon.pts.size(); ++i) {
      if (i)
        ss_ << ",";
      ss_ << polygon.pts[i][1];
    }
    ss_ << "], alpha=0.2)\n";
  }

  void draw(const arrow_2d& arrow) override {
    ss_ << "ax.arrow(" << arrow.p[0] << "," << arrow.p[1] << "," << (arrow.q[0] - arrow.p[0]) << ","
        << (arrow.q[1] - arrow.p[1]) << ", length_includes_head=True, head_width=" << arrow.head_len
        << ", head_length=" << arrow.head_len << ")\n";
  }

  void draw(const text_2d& text) override {
    ss_ << "ax.text(" << text.p[0] << "," << text.p[1] << "," << py_str(text.text)
        << ", fontsize=" << text.size << ")\n";
  }

private:
  static std::string py_str(std::string_view str) {
    std::string q = "'";
    for (char c : str) {
      q += (c == '\'' ? "\\'" : std::string(1, c));
    }
    q += "'";
    return q;
  }

  /// Path where the resulting file is written to
  std::filesystem::path out_filepath_;
  /// Stream where all plot commands are written to
  std::ostringstream ss_;
};

} // namespace trailblaze::plot
