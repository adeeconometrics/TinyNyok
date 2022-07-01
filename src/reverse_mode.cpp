#include "../include/reverse_mode.h"

#include <cmath>
#include <functional>
#include <map>

namespace nyok {

reverse::reverse(const std::map<reverse, double> &_local_gradient, double _value)
    : m_local_gradient(_local_gradient), m_value(_value) {}

reverse::reverse(double _value) : m_value(_value) {}

auto reverse::value() const noexcept -> double { return m_value; }

auto reverse::local_gradient() const noexcept -> std::map<reverse, double> {
  return m_local_gradient;
}

auto reverse::operator<(const reverse &rhs) const -> bool {
  return m_value < rhs.m_value;
}

auto reverse::operator>(const reverse &rhs) const -> bool {
  return m_value > rhs.m_value;
}

auto reverse::operator==(const reverse &rhs) const -> bool {
  return m_value == rhs.m_value;
}

auto reverse::operator!=(const reverse &rhs) const -> bool {
  return m_value != rhs.m_value;
}

auto operator+(const reverse &lhs, const reverse &rhs) -> reverse {
  return {{{lhs, 1.0}, {rhs, 1.0}}, lhs.value() + rhs.value()};
}

auto operator-(const reverse &lhs, const reverse &rhs) -> reverse {
  return {{{lhs, 1.0}, {rhs, -1.0}}, lhs.value() - rhs.value()};
}

auto operator*(const reverse &lhs, const reverse &rhs) -> reverse {
  return {{{lhs, rhs.value()}, {rhs, lhs.value()}}, lhs.value() * rhs.value()};
}

auto operator/(const reverse &lhs, const reverse &rhs) -> reverse {
  const reverse inverse{{{rhs, -1.0 / std::pow(rhs.value(), 2)}},
                       1.0 / rhs.value()};
  return lhs * inverse;
}

auto pow(const reverse &base, const reverse &exponent) -> reverse {
  const double df_base =
      exponent.value() * std::pow(base.value(), exponent.value() - 1);
  const double df_exp =
      std::pow(base.value(), exponent.value()) * std::log(base.value());

  return {{{base, df_base}, {exponent, df_exp}},
          std::pow(base.value(), exponent.value())};
}

auto exp(const reverse &rhs) noexcept -> reverse {
  const double value = std::exp(rhs.value());
  const double df_rhs = value;

  return {{{rhs, df_rhs}}, value};
}

auto ln(const reverse &rhs) noexcept -> reverse {
  const double value = std::log(rhs.value());
  const double df_rhs = 1.0 / rhs.value();

  return {{{rhs, df_rhs}}, value};
}

// auto log(const reverse &argument, const reverse &base) -> reverse {
//   double x{std::log(argument.value())}, y{std::log(base.value())};
//   const double value = x/y;
//   // double df_argument = 1.0/ y * ;
//   double df_base;
// }

auto sin(const reverse &rhs) noexcept -> reverse {
  const double value = std::sin(rhs.value());
  const double df_rhs = std::cos(rhs.value());
  return {{{rhs, df_rhs}}, value};
}

auto cos(const reverse &rhs) noexcept -> reverse {
  const double value = std::cos(rhs.value());
  const double df_rhs = -std::sin(rhs.value());
  return {{{rhs, df_rhs}}, value};
}

auto tan(const reverse &rhs) noexcept -> reverse {
  const double value = std::tan(rhs.value());
  const double df_rhs = 1.0 / std::pow(std::cos(rhs.value()), 2);
  return {{{rhs, df_rhs}}, value};
}

auto cot(const reverse &rhs) noexcept -> reverse {
  const double value = 1.0 / std::tan(rhs.value());
  const double df_rhs = -1.0 / std::pow(std::sin(rhs.value()), 2);
  return {{{rhs, df_rhs}}, value};
}

auto sec(const reverse &rhs) noexcept -> reverse {
  const double value = 1.0 / std::cos(rhs.value());
  const double df_rhs = value * std::tan(rhs.value());
  return {{{rhs, df_rhs}}, value};
}

auto csc(const reverse &rhs) noexcept -> reverse {
  const double value = 1.0 / std::sin(rhs.value());
  const double df_rhs = value * (-1.0 / std::tan(rhs.value()));
  return {{{rhs, df_rhs}}, value};
}

auto sinh(const reverse &rhs) noexcept -> reverse {
  const double value = std::sinh(rhs.value());
  const double df_rhs = std::cosh(rhs.value());
  return {{{rhs, df_rhs}}, value};
}

auto cosh(const reverse &rhs) noexcept -> reverse {
  const double value = std::cosh(rhs.value());
  const double df_rhs = std::sinh(rhs.value());
  return {{{rhs, df_rhs}}, value};
}

auto tanh(const reverse &rhs) noexcept -> reverse {
  const double value = std::tanh(rhs.value());
  const double df_rhs = 1.0 / std::pow(std::cosh(rhs.value()), 2); // cont ..
  return {{{rhs, df_rhs}}, value};
}

auto coth(const reverse &rhs) noexcept -> reverse {
  const double value = 1.0 / std::tanh(rhs.value());
  const double df_rhs = -1.0 / std::pow(std::sinh(rhs.value()), 2);
  return {{{rhs, df_rhs}}, value};
}

auto sech(const reverse &rhs) noexcept -> reverse {
  const double value = 1.0 / std::cosh(rhs.value());
  const double df_rhs = -value * std::tanh(rhs.value());
  return {{{rhs, df_rhs}}, value};
}

auto csch(const reverse &rhs) noexcept -> reverse {
  const double value = 1.0 / std::sinh(rhs.value());
  const double df_rhs = value * (-1.0 / std::tanh(rhs.value()));
  return {{{rhs, df_rhs}}, value};
}

auto asin(const reverse &rhs) noexcept -> reverse {
  const double value = std::asin(rhs.value());
  const double df_rhs = 1.0 / std::sqrt(1 - std::pow(rhs.value(), 2));
  return {{{rhs, df_rhs}}, value};
}

auto acos(const reverse &rhs) noexcept -> reverse {
  const double value = std::acos(rhs.value());
  const double df_rhs = -1.0 / std::sqrt(1 - std::pow(rhs.value(), 2));
  return {{{rhs, df_rhs}}, value};
}

auto atan(const reverse &rhs) noexcept -> reverse {
  const double value = std::atan(rhs.value());
  const double df_rhs = 1.0 / (1 + std::pow(rhs.value(), 2));
  return {{{rhs, df_rhs}}, value};
}

auto acot(const reverse &rhs) noexcept -> reverse {
  const double value = 1.0 / std::atan(rhs.value());
  const double df_rhs = -1.0 / (1 + std::pow(rhs.value(), 2));
  return {{{rhs, df_rhs}}, value};
}

auto asec(const reverse &rhs) noexcept -> reverse {
  const double value = 1.0 / std::acos(rhs.value());
  const double df_rhs = 1.0 / (std::pow(rhs.value(), 2) *
                               std::sqrt(1 - 1.0 / std::pow(rhs.value(), 2)));
  return {{{rhs, df_rhs}}, value};
}

auto acsc(const reverse &rhs) noexcept -> reverse {
  const double value = 1.0 / std::asin(rhs.value());
  const double df_rhs = 1.0 / (std::pow(rhs.value(), 2) *
                               std::sqrt(1 - 1.0 / std::pow(rhs.value(), 2)));
  return {{{rhs, df_rhs}}, value};
}

auto asinh(const reverse &rhs) noexcept -> reverse {
  const double value = std::asinh(rhs.value());
  const double df_rhs = 1.0 / std::sqrt(std::pow(rhs.value(), 2) + 1);
  return {{{rhs, df_rhs}}, value};
}

auto acosh(const reverse &rhs) noexcept -> reverse {
  const double value = std::acosh(rhs.value());
  const double df_rhs = -1.0 / std::sqrt(std::pow(rhs.value(), 2) - 1);
  return {{{rhs, df_rhs}}, value};
}

auto atanh(const reverse &rhs) noexcept -> reverse {
  const double value = std::atanh(rhs.value());
  const double df_rhs = 1.0 / (1 - std::pow(rhs.value(), 2));
  return {{{rhs, df_rhs}}, value};
}

auto acoth(const reverse &rhs) noexcept -> reverse {
  const double value = 1.0 / std::atanh(rhs.value());
  const double df_rhs = -1.0 / (1 - std::pow(rhs.value(), 2));
  return {{{rhs, df_rhs}}, value};
}

auto asech(const reverse &rhs) noexcept -> reverse {
  const double value = 1.0 / std::acosh(rhs.value());
  const double df_rhs =
      -1.0 / (rhs.value() * std::sqrt(1 - std::pow(rhs.value(), 2)));
  return {{{rhs, df_rhs}}, value};
}

auto acsch(const reverse &rhs) noexcept -> reverse {
  const double value = 1.0 / std::asinh(rhs.value());
  const double df_rhs =
      -1.0 / (std::abs(rhs.value()) * std::sqrt(1 + std::pow(rhs.value(), 2)));
  return {{{rhs, df_rhs}}, value};
}

auto gradient(const reverse &variable) -> std::map<reverse, double> {
  std::map<reverse, double> _gradients{};

  std::function<auto(const reverse &, double)->void> _compute_gradient =
      [&_compute_gradient, &_gradients](const reverse &variable,
                                        double path_value) {
        double value_of_path_to_child{};
        // std::cout << "outer: " << path_value << '\n';

        for (auto &[child, local_gradient] : variable.local_gradient()) {
          value_of_path_to_child = path_value * local_gradient;
          _gradients[child] += value_of_path_to_child;

          _compute_gradient(child, value_of_path_to_child);
        }
      };

  _compute_gradient(variable, 1);

  return _gradients;
}

} // namespace nyok