#ifndef TRAILBLAZE_QUATERNION_H_
#define TRAILBLAZE_QUATERNION_H_

namespace trailblaze {

struct Quaternion
{
  double x;
  double y;
  double z;
  double w;  // scalar last
};

inline Quaternion operator*(double scalar, const Quaternion& q)
{
  Quaternion result;
  result.x = scalar * q.x;
  result.y = scalar * q.y;
  result.z = scalar * q.z;
  result.w = scalar * q.w;
  return result;
}

inline Quaternion operator*(const Quaternion& q, double scalar)
{
  return scalar * q;
}

inline double SquaredNorm(const Quaternion& q)
{
  return (q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
}

inline double Norm(const Quaternion& q)
{
  return std::sqrt(SquaredNorm(q));
}

inline void Normalize(Quaternion& q)
{
  const double norm = Norm(q);
  if (norm != 0.)
  {
    q = (1. / norm) * q;
  }
}

inline Quaternion Normalized(Quaternion q)
{
  Quaternion normalized = q;
  Normalize(normalized);
  return normalized;
}

}  // namespace trailblaze

#endif