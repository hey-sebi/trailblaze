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

/** Implements a renderer backend that generates matplotlib plots.
 *  @see https://matplotlib.org/
 */
class matplotlib_renderer final : public renderer {
public:
  /** Constructor
   *  @param out_filepath Path to the file containing the plot instructions.
   */
  explicit matplotlib_renderer(std::filesystem::path out_filepath)
      : out_filepath_(std::move(out_filepath)) {}

  void begin_figure(const canvas_dimension& dim) override {
    ss_.str({});
    ss_.clear();
    ss_ << "import matplotlib.pyplot as plt\n"
           "fig = plt.figure(figsize=("
        << (dim.width / 100.0) << ", " << (dim.height / 100.0)
        << "))\n"
           "ax = fig.add_subplot(111)\n";
  }

  void end_figure() override {
    ss_ << "ax.grid(True)\nplt.show()\n";
    std::ofstream file(out_filepath_);
    file << ss_.str();
  }

  void set_title(std::string_view title) override {
    if (title.empty()) {
      ss_ << "ax.set_title(" << to_python_string_literal(title) << ")\n";
    }
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
      if (i != 0) {
        ss_ << ",";
      }
      ss_ << polygon.pts[i][0];
    }
    ss_ << "],[";
    for (std::size_t i = 0; i < polygon.pts.size(); ++i) {
      if (i != 0) {
        ss_ << ",";
      }
      ss_ << polygon.pts[i][1];
    }
    ss_ << "], alpha=0.2)\n";
  }

  void draw(const arrow_2d& arrow) override {
    ss_ << "ax.arrow(" << arrow.p[0] << "," << arrow.p[1] << "," << (arrow.q[0] - arrow.p[0]) << ","
        << (arrow.q[1] - arrow.p[1])
        << ", length_includes_head=True, head_width=" << arrow.head_length
        << ", head_length=" << arrow.head_length << ")\n";
  }

  void draw(const text_2d& text) override {
    ss_ << "ax.text(" << text.p[0] << "," << text.p[1] << "," << to_python_string_literal(text.text)
        << ", fontsize=" << text.size << ")\n";
  }

private:
  /**
   * Returns a Python-style single-quoted string literal from the given input.
   *
   * This function wraps the input string in single quotes ('...') and escapes
   * any internal single quotes by replacing them with \'.
   *
   * Example:
   * @code
   * to_python_string_literal("it's ok"); // returns "'it\\'s ok'"
   * @endcode
   *
   * @param str The input string to quote.
   * @return A string representing the Python-style literal.
   */
  static std::string to_python_string_literal(std::string_view str) {
    std::string out = "'";
    for (char character : str) {
      out += (character == '\'' ? "\\'" : std::string(1, character));
    }
    out += "'";
    return out;
  }

  /// Path where the resulting file is written to
  std::filesystem::path out_filepath_;
  /// Stream where all plot commands are written to
  std::ostringstream ss_;
};

} // namespace trailblaze::plot
