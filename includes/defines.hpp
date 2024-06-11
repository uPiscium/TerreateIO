#include <cstdint>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace TerreateIO {
namespace Defines {
// type aliases
using Char = char;
using Byte = int8_t;
using Size = uint64_t;

using Bool = bool;
using Char = char;
using Byte = int8_t;
using Size = uint64_t;
using Int8 = int8_t;
using Int16 = int16_t;
using Int32 = int32_t;
using Int64 = int64_t;
using Uint8 = uint8_t;
using Uint16 = uint16_t;
using Uint32 = uint32_t;
using Uint64 = uint64_t;
using Float = float;
using Double = double;
using Str = std::string;

using StrStream = std::stringstream;
using InputStream = std::ifstream;
using OutputStream = std::ofstream;

template <typename T> using Vec = std::vector<T>;
template <typename T> using Set = std::unordered_set<T>;
template <typename S, typename T> using Map = std::unordered_map<S, T>;
} // namespace Defines
} // namespace TerreateIO
