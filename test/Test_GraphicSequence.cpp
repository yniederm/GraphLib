#include <graphlib/algorithms>

#include <string>
#include <queue>
#include <iomanip>

int main(int argc, char const *argv[])
{
  using idx_t = gl::index_type;
  std::vector<std::string> strings = {"3 3 2 1 1 0","5 1 1 1 1 1","5 5 4 4 2 1 0 1 1 1","0 0 0 0 0 0","1 1 1 0 0","7 2 3 0 0 0 1","4 3 3 2 2 1"};
  std::vector<std::deque<idx_t>> deques = {{3,3,2,1,1,0},{5,1,1,1,1,1},{5,5,4,4,2,1,0,1,1,1},{0,0,0,0,0,0},{1,1,1,0,0},{7,2,3,0,0,0,1},{4,3,3,2,2,1}};

  std::cout << "Expected Result:\nThe first each 4 are graphic, the last 3 are not.\n";

  std::cout << "Strings:\n";
  // the first 4 are graphic, the last 3 are not
  for (auto x : strings) {
    std::cout << "[ " << x << " ]: " << std::setw(19 - (x.length()/2-5)*2)
              << (gl::algorithm::isGraphicSequence(x) ? "graphic" : "non-graphic") 
              << "\n";
  }

  std::cout << "Deques:\n";
  // the first 4 are graphic, the last 3 are not
  for (auto x : deques) {
    std::cout << "[";
    for (auto elem : x) {
      std::cout << " " << elem;
    }
    std::cout << " ]: " << std::setw(21 - (x.size()-5)*2)
              << (gl::algorithm::havelHakimi(x) ? "graphic" : "non-graphic") 
              << "\n";
  }

  return 0;
}
