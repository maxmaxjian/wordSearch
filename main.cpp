#include <iostream>
#include <vector>
#include <string>

using pos = std::pair<size_t,size_t>;

class solution {
public:
  std::vector<std::string> findWords(const std::vector<std::string> & board, const std::vector<std::string> & words) {
    std::vector<std::string> found;
    std::copy_if(words.begin(), words.end(), std::inserter(found, found.begin()),
		 [&](const std::string & s){
		   return foundInBoard(board, s);
		 });
    return found;
  }

private:
  bool foundInBoard(const std::vector<std::string> & board, const std::string & str) {
    auto paths = getPaths(board, str, std::vector<pos>(), std::vector<std::vector<int>>(board.size(), std::vector<int>(board[0].size(), 0)));
    return !paths.empty();
  }

  std::vector<std::vector<pos>> getPaths(const std::vector<std::string> & board, const std::string & s, const std::vector<pos> & curr, const std::vector<std::vector<int>> & visit) {
    std::vector<std::vector<pos>> result;
    if (curr.size() == s.size())
      result.push_back(curr);
    else {
      std::vector<pos> next = getNext(board, s, curr, visit);
      for (auto nx : next) {
	auto curr_cpy = curr;
	curr_cpy.push_back(nx);
	auto visit_cpy = visit;
	visit_cpy[nx.first][nx.second] = 1;
	auto temp = getPaths(board, s, curr_cpy, visit_cpy);
	std::copy(temp.begin(), temp.end(), std::inserter(result, result.end()));
      }
    }
    return result;
  }

  std::vector<pos> getNext(const std::vector<std::string> & board, const std::string &s, const std::vector<pos> & curr, const std::vector<std::vector<int>> & visit) {
    std::vector<pos> next;
    if (curr.empty()) {
      for (size_t i = 0; i < board.size(); i++) {
	for (size_t j = 0; j < board[i].size(); j++) {
	  if (board[i][j] == s[curr.size()])
	    next.push_back(std::make_pair(i,j));
	}
      }
    }
    else {
      auto last = curr.back();
      if (last.first < board.size()-1 && s[curr.size()] == board[last.first+1][last.second] && visit[last.first+1][last.second] == 0)
	next.push_back(std::make_pair(last.first+1, last.second));
      if (last.first > 0 && s[curr.size()] == board[last.first-1][last.second] && visit[last.first-1][last.second] == 0)
	next.push_back(std::make_pair(last.first-1, last.second));
      if (last.second < board[0].size()-1 && s[curr.size()] == board[last.first][last.second+1] && visit[last.first][last.second+1] == 0)
	next.push_back(std::make_pair(last.first, last.second+1));
      if (last.second > 0 && s[curr.size()] == board[last.first][last.second-1] && visit[last.first][last.second-1] == 0)
	next.push_back(std::make_pair(last.first, last.second-1));
    }
    return next;
  }
};

int main() {
  std::vector<std::string> board{
    {"oaan"},
      {"etae"},
	{"ihkr"},
	  {"iflv"}
  };
  std::vector<std::string> words{"oath", "pea", "eat", "rain"};
  

  solution soln;
  auto wordsFound = soln.findWords(board, words);
  std::cout << "The words found in the board are:\n";
  std::copy(wordsFound.begin(), wordsFound.end(), std::ostream_iterator<std::string>(std::cout, " "));
  std::cout << std::endl;
}
