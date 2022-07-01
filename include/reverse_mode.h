#ifndef __AUTODIFF_H__
#define __AUTODIFF_H__

#include <map>

namespace nyok {
class reverse {
private:
  std::map<reverse, double> m_local_gradient;
  double m_value{};

public:
  reverse(const std::map<reverse, double> &, double);
  reverse(double);

  auto value() const noexcept -> double;
  auto local_gradient() const noexcept -> std::map<reverse, double>;

  auto operator<(const reverse &) const -> bool;
  auto operator>(const reverse &) const -> bool;
  auto operator==(const reverse &) const -> bool;
  auto operator!=(const reverse &) const -> bool;
};

auto operator+(const reverse &, const reverse &) -> reverse;
auto operator-(const reverse &, const reverse &) -> reverse;
auto operator*(const reverse &, const reverse &) -> reverse;
auto operator/(const reverse &, const reverse &) -> reverse;

auto pow(const reverse &, const reverse &) -> reverse;
auto exp(const reverse &) noexcept -> reverse;
auto ln(const reverse &) noexcept -> reverse;

auto sin(const reverse &) noexcept -> reverse;
auto cos(const reverse &) noexcept -> reverse;
auto tan(const reverse &) noexcept -> reverse;
auto cot(const reverse &) noexcept -> reverse;
auto sec(const reverse &) noexcept -> reverse;
auto csc(const reverse &) noexcept -> reverse;

auto sinh(const reverse &) noexcept -> reverse;
auto cosh(const reverse &) noexcept -> reverse;
auto tanh(const reverse &) noexcept -> reverse;
auto coth(const reverse &) noexcept -> reverse;
auto sech(const reverse &) noexcept -> reverse;
auto csch(const reverse &) noexcept -> reverse;

auto asin(const reverse &) noexcept -> reverse;
auto acos(const reverse &) noexcept -> reverse;
auto atan(const reverse &) noexcept -> reverse;
auto acot(const reverse &) noexcept -> reverse;
auto asec(const reverse &) noexcept -> reverse;
auto acsc(const reverse &) noexcept -> reverse;

auto asinh(const reverse &) noexcept -> reverse;
auto acosh(const reverse &) noexcept -> reverse;
auto atanh(const reverse &) noexcept -> reverse;
auto acoth(const reverse &) noexcept -> reverse;
auto asech(const reverse &) noexcept -> reverse;
auto acsch(const reverse &) noexcept -> reverse;

auto gradient(const reverse &) -> std::map<reverse, double>;

} // namespace nyok

#endif // __AUTODIFF_H__