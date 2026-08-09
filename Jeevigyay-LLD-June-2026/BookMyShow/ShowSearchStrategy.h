#ifndef SHOWSEARCHSTRATEGY_H
#define SHOWSEARCHSTRATEGY_H

#include <memory>
#include <unordered_map>

#include "SearchResult.h"
#include "SearchCriteria.h"
#include "ShowSearchResult.h"
#include "SearchStrategy.h"

class ShowSearchStrategy : public SearchStrategy
{
public:
  void fnSetTheatreToShowMap(std::unordered_map<
                             std::string, // movie
                             std::unordered_map<
                                 std::string, // city
                                 std::unordered_map<
                                     std::shared_ptr<Theatre>,
                                     std::vector<std::shared_ptr<Show>>>>>
                                 clpShowMap)
  {
    m_clTheatreToShowMap = clpShowMap;
  }

  std::shared_ptr<SearchResult> fnSearch(std::shared_ptr<SearchCriteria> criteria) override
  {
    if (nullptr == criteria)
    {
      return nullptr;
    }
    auto cityName = criteria->fnGetCityName();
    auto movieName = criteria->fnGetMovieName();

    std::shared_ptr<ShowSearchResult> clpSearchResult = std::make_shared<ShowSearchResult>();

    auto clpTheatre = criteria->fnGetTheatre();
    std::pair<std::string, std::string> pair;
    pair.first = cityName;
    pair.second = movieName;
    auto clpTheatreToShowVector = m_clTheatreToShowMap[cityName][movieName];
    if (nullptr == clpTheatre)
    {
      clpSearchResult->fnSetTheatreShowList(clpTheatreToShowVector);
    }
    else
    {
      clpSearchResult->fnSetShowList(clpTheatreToShowVector[clpTheatre]);
    }
    return clpSearchResult;
  }

private:
  std::unordered_map<
      std::string, // movie
      std::unordered_map<
          std::string, // city
          std::unordered_map<
              std::shared_ptr<Theatre>,
              std::vector<std::shared_ptr<Show>>>>>
      m_clTheatreToShowMap;
};

#endif // SHOWSEARCHSTRATEGY_H