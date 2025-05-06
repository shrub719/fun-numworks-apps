constexpr float PI = 3.14159265f;
constexpr float TWO_PI = 6.28318531f;

float wrap_pi(float x) {
    while (x < 0.0f)
        x += TWO_PI;
    while (x >= TWO_PI)
        x -= TWO_PI;

    if (x >= PI)
        x -= TWO_PI;

    return x;
}

float approx_sin(float x) {
    x = wrap_pi(x);
    const float x3 = x * x * x;
    const float x5 = x3 * x * x;
    const float x7 = x5 * x * x;
    return x - x3 / 6.0f + x5 / 120.0f - x7 / 5040.0f;
}

float approx_cos(float x) {
    x = wrap_pi(x);
    const float x2 = x * x;
    const float x4 = x2 * x * x;
    const float x6 = x4 * x * x;
    return 1 - x2 / 2.0f + x4 / 24.0f - x6 / 720.0f;
}

float better_sin(float x) {
    x = wrap_pi(x);
    const float x3 = x * x * x;
    const float x5 = x3 * x * x;
    const float x7 = x5 * x * x;
    const float x9 = x7 * x * x;
    return x - x3 / 6.0f + x5 / 120.0f - x7 / 5040.0f + x9 / 362880.0f;
}

float better_cos(float x) {
    x = wrap_pi(x);
    const float x2 = x * x;
    const float x4 = x2 * x * x;
    const float x6 = x4 * x * x;
    const float x8 = x6 * x * x;
    return 1 - x2 / 2.0f + x4 / 24.0f - x6 / 720.0f + x8 / 40320.0f;
}
