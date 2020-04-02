#include "util.h"

namespace da {

template <> int zero() { return 0; }

template <> double zero() { return 0.0; }

template <> float zero() { return 0.0f; }

} // namespace da
