#include "../include/forward_mode.h"

#include <cmath>
#include <functional>
#include <vector>

namespace nyok {

forward::forward(double _val, double _dot) : m_val(_val), m_dot(_dot) {}

forward::forward(double _val) : m_val(_val) {}

auto forward::value() const noexcept -> double { return m_val; }
auto forward::dot() const noexcept -> double { return m_dot; }

auto operator+(const forward &lhs, const forward &rhs) -> forward {
  return {lhs.value() + rhs.value(), lhs.dot() + rhs.dot()};
}

auto operator-(const forward &lhs, const forward &rhs) -> forward {
  return {lhs.value() - rhs.value(), lhs.dot() - rhs.dot()};
}

auto operator*(const forward &lhs, const forward &rhs) -> forward {
  return {lhs.value() * rhs.value(),
          lhs.dot() * rhs.value() + rhs.dot() * lhs.value()};
}

auto operator/(const forward &lhs, const forward &rhs) -> forward {
  const double df = (lhs.dot() * rhs.value() - lhs.value() * rhs.dot()) /
                    std::pow(rhs.value(), 2);
  return {lhs.value() / rhs.value(), df};
}
// has problems to address df.dexp and df.dbase case
auto pow(const forward &base, const forward &exp) -> forward {
  const double df_base =
      std::log(base.value()) * std::pow(base.value(), exp.value()) * exp.dot();
  return {std::pow(base.value(), exp.value()), df_base};
}

auto pow(const forward &base, double exp) -> forward {
  const double df_base = base.dot() * std::pow(base.value(), exp - 1);
  return {std::pow(base.value(), exp), df_base};
}

auto exp(const forward &rhs) noexcept -> forward {
  const double value = std::exp(rhs.value());
  const double df = value * rhs.dot();
  return {value, df};
}

auto ln(const forward &rhs) noexcept -> forward {
  const double value = std::log(rhs.value());
  const double df = (1.0f / rhs.value()) * rhs.dot();
  return {value, df};
}

auto sin(const forward &rhs) noexcept -> forward {
  const double value = std::sin(rhs.value());
  const double df = std::cos(rhs.value()) * rhs.dot();
  return {value, df};
}

auto cos(const forward &rhs) noexcept -> forward {
  const double value = std::cos(rhs.value());
  const double df = -std::sin(rhs.value()) * rhs.dot();
  return {value, df};
}

auto tan(const forward &rhs) noexcept -> forward {
  const double value = std::tan(rhs.value());
  const double df = std::pow(1.0f / std::cos(rhs.value()), 2) * rhs.dot();
  return {value, df};
}

auto cot(const forward &rhs) noexcept -> forward {
  const double value = 1.0f / std::tan(rhs.value());
  const double df = -std::pow(1.0f / std::sin(rhs.value()), 2) * rhs.dot();
  return {value, df};
}

auto sec(const forward &rhs) noexcept -> forward {
  const double value = 1.0f / std::cos(rhs.value());
  const double df = value * std::tan(rhs.value()) * rhs.dot();
  return {value, df};
}

auto csc(const forward &rhs) noexcept -> forward {
  const double value = 1.0f / std::sin(rhs.value());
  const double df = -value * (1.0f / std::tan(rhs.value())) * rhs.dot();
  return {value, df};
}

auto sinh(const forward &rhs) noexcept -> forward {
  const double value = std::sinh(rhs.value());
  const double df = std::cosh(rhs.value()) * rhs.dot();
  return {value, df};
}

auto cosh(const forward &rhs) noexcept -> forward {
  const double value = std::cosh(rhs.value());
  const double df = -std::sinh(rhs.value()) * rhs.dot();
  return {value, df};
}

auto tanh(const forward &rhs) noexcept -> forward {
  const double value = std::tanh(rhs.value());
  const double df = std::pow(1.0f / std::cosh(rhs.value()), 2) * rhs.dot();
  return {value, df};
}

auto coth(const forward &rhs) noexcept -> forward {
  const double value = 1.0f / std::tanh(rhs.value());
  const double df = -std::pow(1.0f / std::sinh(rhs.value()), 2) * rhs.dot();
  return {value, df};
}

auto sech(const forward &rhs) noexcept -> forward {
  const double value = 1.0f / std::cosh(rhs.value());
  const double df = value * std::tanh(rhs.value()) * rhs.dot();
  return {value, df};
}

auto csch(const forward &rhs) noexcept -> forward {
  const double value = 1.0f / std::sinh(rhs.value());
  const double df = -value * (1.0f / std::tanh(rhs.value())) * rhs.dot();
  return {value, df};
}

} // namespace nyok