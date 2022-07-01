#ifndef __FORWARD_MODE_H__
#define __FORWARD_MODE_H__

#include <vector>

namespace nyok{
class forward{
private:
	double m_val{};
	double m_dot{};
public:
	forward(double, double);
	forward(double);

	auto value() const noexcept -> double;
	auto dot() const noexcept -> double;
};

auto operator+(const forward&, const forward&) -> forward;
auto operator-(const forward&, const forward&) -> forward;
auto operator*(const forward&, const forward&) -> forward;
auto operator/(const forward&, const forward&) -> forward;

auto pow(const forward&, const forward&) -> forward;

auto ln(const forward&) noexcept -> forward;

auto sin(const forward&) noexcept -> forward;
auto cos(const forward&) noexcept -> forward;
auto tan(const forward&) noexcept -> forward;
auto cot(const forward&) noexcept -> forward;
auto sec(const forward&) noexcept -> forward;
auto csc(const forward&) noexcept -> forward;

auto sinh(const forward&) noexcept -> forward;
auto cosh(const forward&) noexcept -> forward;
auto tanh(const forward&) noexcept -> forward;
auto coth(const forward&) noexcept -> forward;
auto sech(const forward&) noexcept -> forward;
auto csch(const forward&) noexcept -> forward;

auto asin(const forward&) noexcept -> forward;
auto acos(const forward&) noexcept -> forward;
auto atan(const forward&) noexcept -> forward;
auto acot(const forward&) noexcept -> forward;
auto asec(const forward&) noexcept -> forward;
auto acsc(const forward&) noexcept -> forward;

auto asinh(const forward&) noexcept -> forward;
auto acosh(const forward&) noexcept -> forward;
auto atanh(const forward&) noexcept -> forward;
auto acoth(const forward&) noexcept -> forward;
auto asech(const forward&) noexcept -> forward;
auto acsch(const forward&) noexcept -> forward;

} // namespace ad


#endif