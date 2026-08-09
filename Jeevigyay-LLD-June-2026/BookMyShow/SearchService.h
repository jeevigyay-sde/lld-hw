#ifndef SEARCHSERVICE_H
#define SEARCHSERVICE_H

#include <memory>

#include "SearchResult.h"
#include "SearchCriteria.h"
#include "SearchStrategy.h"

class SearchService
{
public:
  std::shared_ptr<SearchResult> fnSearch(std::shared_ptr<SearchCriteria> criteria)
  {
    return m_clpStrategy->fnSearch(criteria);
  }

  void fnSetStrategy(std::shared_ptr<SearchStrategy> clpStrategy)
  {
    m_clpStrategy = clpStrategy;
  }

private:
  std::shared_ptr<SearchStrategy> m_clpStrategy;
};

#endif // SEARCHSERVICE_H