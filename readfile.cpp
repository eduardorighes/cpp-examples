#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <functional>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#if WANT_SLOW_FUNCTIONS
void read_file(const std::string& filename)
{
  // this function looks nice but it is slow...

  std::ifstream file(filename);

  file.seekg(0, std::ios::end);
  std::streampos fileSize = file.tellg();
  file.seekg(0, std::ios::beg);

  std::vector<char> buffer;
  buffer.reserve(fileSize);

  buffer.insert(buffer.begin(),
    std::istream_iterator<char>(file),
    std::istream_iterator<char>());

  std::ofstream devnull("/dev/null");
  std::ostream_iterator<char> out(devnull);
  std::copy(&buffer[0], &buffer[0]+fileSize, out);
}

void out_file(const std::string& filename)
{
  std::ifstream file(filename);
  std::ofstream devnull("/dev/null");

  std::ostream_iterator<char> out(devnull);
  std::copy(
    std::istreambuf_iterator<char>(file.rdbuf()),
    std::istreambuf_iterator<char>(),
    out);
}
#endif

void read_file_chunks(const std::string& filename)
{
  std::ifstream file(filename, std::ios::binary);
  std::ofstream devnull("/dev/null");

  //std::array<char, 32768> buffer;
  char buffer[32768];
  //while (file.read(&buffer[0], buffer.size()).gcount())
  while (file.read(buffer, sizeof(buffer)))
  {
    devnull.write(buffer, file.gcount());
  }
}

void read_file_chunks_c(const std::string& filename)
{
 std::array<char, 32768> buffer;
 FILE* fp = fopen(filename.c_str(), "rb");
 FILE* devnull = fopen("/dev/null", "wb");
 if (fp && devnull)
 {
  size_t r = fread(&buffer[0], buffer.size(), 1, fp);
  while (!feof(fp))
  {
    fwrite(&buffer[0], r, 1, devnull);
    r = fread(&buffer[0], buffer.size(), 1, fp);
  }
  fclose(fp);
  fclose(devnull);
 }
}

using ReadFn = std::function<void(const std::string&)>;

void timer(ReadFn fn, const std::string& filename, const std::string& what)
{
  std::cerr
    << "test: " << what
    << std::endl;
  clock_t start = clock();
  fn(filename);
  clock_t stop = clock();
  std::cerr
    << "time: " << double(stop-start) / CLOCKS_PER_SEC
    << std::endl;
}

int main(int argc, char** argv)
{
  try
  {
    timer(read_file_chunks, argv[1], "read_file_chunks");
    timer(read_file_chunks_c, argv[1], "read_file_chunks_c");
#if WANT_SLOW_FUNCTIONS
    timer(read_file, argv[1], "read_file");
    timer(out_file, argv[1], "out_file");
#endif
  }
  catch (const std::exception& error)
  {
    std::cerr << error.what() << std::endl;
  }
  return 0;
}
