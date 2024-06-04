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
using Str = std::string;
using StrStream = std::stringstream;
using InputStream = std::ifstream;
using OutputStream = std::ofstream;
template <typename T> using Vec = std::vector<T>;
template <typename T> using Set = std::unordered_set<T>;
template <typename S, typename T> using Map = std::unordered_map<S, T>;
} // namespace Defines
} // namespace TerreateIO
