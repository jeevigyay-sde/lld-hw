#ifndef SEARCHSTRATEGY_H
#define SEARCHSTRATEGY_H

#include <memory>

#include "SearchResult.h"
#include "SearchCriteria.h"

class SearchStrategy
{
public:
  virtual std::shared_ptr<SearchResult> fnSearch(std::shared_ptr<SearchCriteria> criteria) = 0;
};

#endif // SEARCHSTRATEGY_H