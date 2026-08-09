#ifndef MOVIESEARCHSTRATEGY_H
#define MOVIESEARCHSTRATEGY_H

#include <memory>

#include "SearchResult.h"
#include "SearchCriteria.h"
#include "MovieSearchResult.h"
#include "SearchStrategy.h"

class MovieSearchStrategy : public SearchStrategy
{
public:
  std::shared_ptr<SearchResult> fnSearch(std::shared_ptr<SearchCriteria> criteria) override
  {
    if (nullptr == criteria)
    {
      return nullptr;
    }
    auto clpTheatre = criteria->fnGetTheatre();
    if (nullptr == clpTheatre)
    {
      return nullptr;
    }
    std::shared_ptr<MovieSearchResult> clpSearchResult = std::make_shared<MovieSearchResult>();
    clpSearchResult->fnSetMovieList(clpTheatre->fnGetMovieList());
    return clpSearchResult;
  }
};

#endif // MOVIESEARCHSTRATEGY_H