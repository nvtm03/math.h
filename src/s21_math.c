#include "s21_math.h"
int s21_abs(int x) { return x < 0 ? -x : x; }

long double s21_fabs(double x) {
  long double result = x;
  if (x != x) {
    result = S21_NAN;
  } else if (x == S21_INF || x == -S21_INF) {
    result = S21_INF;
  } else {
    result = x < 0 ? -x : x;
  }
  return result;
}

long double s21_atan(double x) {
  long double result = 0;
  if (x != x) {
    result = S21_NAN;
  } else if (x == S21_INF) {
    result = S21_PI / 2;
  } else if (x == -S21_INF) {
    result = -S21_PI / 2;
  } else {
    if (s21_fabs(x) == 1) {
      result = S21_PI / 4 * (x);
    } else if (s21_fabs(x) < 1) {
      double eps = 1.0;
      for (int i = 0; s21_fabs(eps) > S21_EPS; ++i) {
        eps = (s21_pow(-1, i) * s21_pow(x, 1 + 2 * i)) / (1 + 2 * i);
        result += eps;
      }
    } else if (s21_fabs(x) > 1) {
      result = (S21_PI * s21_sqrt(s21_pow(x, 2))) / (2 * x);
      double eps = 1.0;
      for (int i = 0; s21_fabs(eps) > S21_EPS; ++i) {
        eps = (s21_pow(-1, i) * s21_pow(x, -1 - 2 * i)) / (1 + 2 * i);
        result -= eps;
      }
    }
  }
  return result;
}

long double s21_ceil(double x) {
  long double result = (long long int)x;
  if (x != x) {
    result = S21_NAN;
  } else if (x == S21_INF || x == -S21_INF) {
    result = x;
  } else if (x > 0 && x - result != 0) {
    ++result;
  }
  return result;
}

long double s21_floor(double x) {
  long double result = (long long int)x;
  if (x != x) {
    result = S21_NAN;
  } else if (x == S21_INF || x == -S21_INF) {
    result = x;
  } else if (x < 0 && x - result != 0) {
    --result;
  }
  return result;
}

long double s21_log(double x) {
  long double result = 0;
  long double last = 0;
  int ex_pow = 0;
  if (x != x || x == S21_INF) {
    result = x;
  } else if (x == 0) {
    result = -S21_INF;
  } else if (x < 0) {
    result = S21_NAN;
  } else {
    for (; x >= S21_EXP; x /= S21_EXP, ++ex_pow)
      ;
    for (int i = 0; i < 100; ++i) {
      last = result;
      result = last + 2 * ((x - s21_exp(last)) / (x + s21_exp(last)));
    }
    result += ex_pow;
  }
  return result;
}

long double s21_asin(double x) {
  long double result;
  if (x != x) {
    result = S21_NAN;
  } else if (x == S21_INF || x == -S21_INF) {
    result = S21_NAN;
  } else if (s21_fabs(x) > 1) {
    result = S21_NAN;
  } else if (s21_fabs(x) == 1) {
    result = S21_PI / 2 * x;
  } else {
    result = s21_atan(x / (s21_sqrt(1 - x * x)));
  }
  return result;
}

long double s21_acos(double x) {
  long double result = S21_NAN;
  if (x != x) {
    result = S21_NAN;
  } else if (x == S21_INF || x == -S21_INF) {
    result = S21_NAN;
  } else {
    if (x >= 0 && x <= 1) {
      result = s21_atan((s21_sqrt(1 - x * x)) / x);
    } else if (x >= -1 && x < 0) {
      result = S21_PI + s21_atan((s21_sqrt(1 - x * x)) / x);
    }
  }
  return result;
}

long double s21_sin(double x) {
  long double result = 0;
  if (x != x || x == S21_INF || x == -S21_INF) {
    result = S21_NAN;
  } else {
    for (; x > S21_PI || x < -S21_PI;) {
      if (x > S21_PI)
        x -= 2 * S21_PI;
      else if (x < -S21_PI)
        x += 2 * S21_PI;
    }
    long double eps;
    for (int i = 0; i < 200; ++i) {
      eps = s21_pow(-1., i) * s21_pow(x, 1. + 2. * i) / s21_fact(1. + 2. * i);
      result += eps;
    }
  }
  return result;
}

long double s21_fact(long double x) {
  if (x == 0 || x == 1) {
    return 1;
  } else {
    return s21_fact(x - 1) * x;
  }
}

long double s21_cos(double x) {
  long double result = 0;
  if (x != x || x == S21_INF || x == -S21_INF) {
    result = S21_NAN;
  } else {
    for (; x > S21_PI || x < -S21_PI;) {
      if (x > S21_PI)
        x -= 2 * S21_PI;
      else if (x < -S21_PI)
        x += 2 * S21_PI;
    }
    long double eps;
    for (int i = 0; i < 100; ++i) {
      eps = s21_pow(-1., i) * s21_pow(x, 2. * i) / s21_fact(2. * i);
      result += eps;
    }
  }
  return result;
}

long double s21_tan(double x) { return s21_sin(x) / s21_cos(x); }

long double s21_sqrt(double x) {
  long double result = 2;
  if (x == S21_INF) {
    result = S21_INF;
  } else if (x != x || x == -S21_INF || x < 0) {
    result = S21_NAN;
  } else {
    for (int i = 0; i < 500; ++i) {
      result = 0.5 * (result + x / result);
    }
  }
  return result;
}

long double s21_fmod(double x, double y) {
  long double result = 0;
  if (x != x || x == S21_INF || x == -S21_INF || y != y || y == 0) {
    result = S21_NAN;
  } else if (y == S21_INF || y == -S21_INF) {
    result = x;
  } else {
    long long int temp;
    temp = x / y;
    result = x - y * temp;
  }
  return result;
}

long double s21_exp(double x) {
  long double result;
  if (x != x) {
    result = S21_NAN;
  } else if (x == S21_INF) {
    result = S21_INF;
  } else if (x == -S21_INF) {
    result = 0.;
  } else if (x <= -20) {
    result = 0;
  } else {
    long double eps = 1.;
    result = 1;
    for (long double i = 1; s21_fabs(eps) > S21_EPS; ++i) {
      eps *= x / i;
      result += eps;
      //            if (result > S21_DOUBLE_MAX) {
      //                result = S21_INF;
      //                break;
      //            }
    }
  }
  return result;
}

long double s21_pow(double base, double exp) {
  long double result = 1;
  if (exp == 0) {
    result = 1;
  } else if (base == 1) {
    result = 1;
  } else if (base == -1 && (exp == S21_INF || exp == -S21_INF)) {
    result = 1;
  } else if (base == -S21_INF && exp == S21_INF) {
    result = S21_INF;
  } else if ((base < 0 && base != -S21_INF && base != S21_INF) &&
             (exp - (long long int)exp != 0 && exp != S21_INF &&
              exp != -S21_INF)) {
    result = S21_NAN;
  } else {
    if (base < 0) {
      base = -base;
      result = s21_fmod(exp, 2) ? -result : result;
    }
    result *= s21_exp(exp * s21_log(base));
  }
  return result;
}
