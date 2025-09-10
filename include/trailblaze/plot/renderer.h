#ifndef TRAILBLAZE_PLOT_RENDERER_H_
#define TRAILBLAZE_PLOT_RENDERER_H_

#include "trailblaze/plot/scene.h"

namespace trailblaze {
namespace plot {

class Renderer
{
 public:
  virtual ~Renderer() = default;

  // Lifecycle
  virtual void BeginFigure(int width_px = 1000, int height_px = 800) = 0;
  virtual void EndFigure() = 0;

  // Drawing
  virtual void Draw(const Polyline2D& pl) = 0;
  virtual void Draw(const Polygon2D& pg) = 0;
  virtual void Draw(const Arrow2D& ar) = 0;
  virtual void Draw(const Text2D& t) = 0;

  // View / styling helpers (optional, no-ops by default)
  virtual void SetTitle(std::string title)
  {
  }

  virtual void SetAxisEqual(bool equal = true)
  {
  }

  virtual void SetXlim(double min_x, double max_x)
  {
  }

  virtual void SetYlim(double min_y, double max_y)
  {
  }
};

}  // namespace plot
}  // namespace trailblaze
#endif