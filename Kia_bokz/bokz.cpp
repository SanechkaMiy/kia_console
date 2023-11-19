#include "bokz.h"
Bokz::Bokz()
{

}

std::tuple<double, double, double> Bokz::math_alpha_delta_azimut(double Qo0, double Qo1, double Qo2, double Qo3)
{
    auto De = asinm(Qo0 * Qo0 - Qo1 * Qo1 - Qo2 * Qo2 + Qo3 * Qo3);
    auto cDe = cos(De);
    auto sA = 2 * (Qo2 * Qo3 - Qo0 * Qo1) / cDe;
    auto cA  = 2 * (Qo1 * Qo3 + Qo0 * Qo2) / cDe;
    auto Al = atan2m(sA, cA);
    sA = 2 * (Qo1 * Qo3 - Qo0 * Qo2) / cDe;
    cA = 2 * (Qo2 * Qo3 + Qo0 * Qo1) / cDe;
    auto Az = atan2m(sA, cA);
    //Al = Al * RTS;
    //De = De * RTS;
    //Az = Az * RTS;
    return {Al, De, Az};
}

double Bokz::atan2m(double y, double x)
{
    double ang;

    if (fabs(x) > 1e-10f) ang = atan2(y, x);
    else
    {
      if (y > 0.f) ang = PI/2.f;
      else ang = -PI/2.f;
    }
    if (ang<0.f) ang += PI2;
    return ang;
}

double Bokz::asinm(double x)
{
    if (x > 1.f) x = 1.f;
    else if (x < -1.f) x = -1.f;

    return asin(x);
}
