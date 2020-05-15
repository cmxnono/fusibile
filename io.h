#ifndef FUSIBILE_IO_
#define FUSIBILE_IO_

inline bool IsLittleEndian() {
#ifdef BOOST_BIG_ENDIAN
  return false;
#else
  return true;
#endif
}
template <typename T>
T ReverseBytes(const T& data) {
  T data_reversed = data;
  std::reverse(reinterpret_cast<char*>(&data_reversed),
               reinterpret_cast<char*>(&data_reversed) + sizeof(T));
  return data_reversed;
}
template <typename T>
T NativeToLittleEndian(const T x) {
  if (IsLittleEndian()) {
    return x;
  } else {
    return ReverseBytes(x);
  }
}
template <typename T>
void WriteBinaryLittleEndian(std::ostream* stream, const T& data) {
    const T data_little_endian = NativeToLittleEndian(data);
    stream->write(reinterpret_cast<const char*>(&data_little_endian), sizeof(T));
}

template <typename T>
void WriteBinaryLittleEndian(std::ostream* stream, const std::vector<T>& data) {
    for (const auto& elem : data) {
        WriteBinaryLittleEndian<T>(stream, elem);
    }
}

void WritePointsVisibility(
        const std::string& path,
        const std::vector<std::vector<int>>& points_visibility) {
    std::fstream file(path, std::ios::out | std::ios::binary);
    //CHECK(file.is_open()) << path;

    WriteBinaryLittleEndian<uint64_t>(&file, points_visibility.size());

    for (const auto& visibility : points_visibility) {
        WriteBinaryLittleEndian<uint32_t>(&file, visibility.size());
        for (const auto& image_idx : visibility) {
            WriteBinaryLittleEndian<uint32_t>(&file, image_idx);
        }
    }
}
#endif
