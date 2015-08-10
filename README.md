# New in C++11: range-based for loops

In my last post, I talked about the **auto** keyword (resurrected from obscurity as the default storage class type in plain C) and how it can make your code cleaner. Here's a quick code sample for review:

```C++
#include <stdio.h>
#include <vector>

// Load a vector with some integers
std::vector<int> integers;
for (int i=0; i<10; ++i) {
  integers.push_back(i);
}

// Iterate over the vector using our new friend, 'auto'.
for (auto x = integers.begin(); x != integers.end(); ++x) {
  printf("%d\n", *x);
}
``` 

The addition of **auto** is all about typing: letting us do less of it, and the compiler more of it.  That should be enough to make any programmer happy.

**But wait, there's more!**

The task of iteration over a range is so common that it seems utterly tedious to type code like the above: how often are you iterating over a vector or map without iterating over the entire range? Surely there must be a better way, right?

The answer is C++11's ranged-for syntax. To paraphrase the old adage, a piece of code is worth a thousand words:

```C++
// Load a vector with some integers
std::vector<int> integers;
for (int i=0; i<10; ++i) {
  integers.push_back(i);
}

// Iterate over the entire range of elements in the vector
for (auto x : integers) {
  printf("%d\n", x);
}
```
Pretty neat huh? Note that in the above example, the type of **x** is really **int**.  We could also modify the value of the element in place like this:

```C++
for (auto& x : integers) {
  x = 42;
}
```

This works on the standard containers and offers another big win in terms of readability (and saves typing as well.)

**Adding Support for your Classes**

It's also not difficult to customize your classes so that they can be iterated over with ranged-for loops.  The complete example below demonstrates how this is done. In a nutshell, you must provide basic iterator support:

1. You must provide prefix operator++ on the iterator
2. You must provide operator!= for the iterator
3. The iterator must support operator* to obtain the value
4. A begin() method (or free function) which returns an iterator
5. An end() method (or free function) which returns an iterator

**Example**

Let's take a look at a (somewhat) real world example. Suppose that we have a legacy Portfolio class that holds the constituents of a client portfolio. We'd like to enhance the class to support range-based iteration.

```C++
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
```

**Wrap Up**

As you can see, with a little bit of work, it is possible to add support to your classes that allow you to take advantage of the new, powerful syntax features of C++11.  

*Note: The code is also available on Github:*
https://github.com/tdial/ranged-for/)


