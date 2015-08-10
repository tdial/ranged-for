#include <iostream>
#include <vector>
#include <string>

class Portfolio {
 public:
  // Hard code the portfolio with some great holdings.
  Portfolio() : constituents_{"FDS", "GOOG", "AAPL", "NFLX"} {}

  friend class Iterator;

  class Iterator {
   public:
    Iterator(const Portfolio* portfolio, size_t position)
        : portfolio_(portfolio), position_(position) {}

    // 1. We must provide a prefix operator++ on the iterator.
    Iterator operator++() {
      ++position_;
      return *this;
    }

    // 2. We must provide != comparison between two iterators.
    bool operator!=(const Iterator& other) const {
      return position_ != other.position_;
    }

    // 3. We must provide a value accessor via operator*
    std::string operator*() const {
      return portfolio_->constituents_[position_];
    }

   private:
    const Portfolio* portfolio_;
    size_t position_;
  };

  // 4. We must provide begin() to return the start of the range.
  Iterator begin() const { return Iterator(this, 0); }

  // 5. We must provide end() to return the end of the range.
  Iterator end() const { return Iterator(this, constituents_.size()); }

 private:
  std::vector<std::string> constituents_;
};

using std::cout;
using std::endl;

int main(int argc, char* argv[])
{
  // Declare a portfolio
  Portfolio portfolio;

  // Print the constituents
  for (auto symbol : portfolio) {
    cout << symbol << endl;
  }

  return 0;
}
