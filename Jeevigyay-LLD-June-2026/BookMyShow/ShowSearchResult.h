#ifndef SHOWSEARCHRESULT_H
#define SHOWSEARCHRESULT_H

#include <vector>
#include <memory>
#include <unordered_map>

#include "SearchResult.h"
#include "Show.h"
#include "Theatre.h"

class ShowSearchResult : public SearchResult
{
public:
  void fnSetShowList(std::vector<std::shared_ptr<Show>> clpShowVector)
  {
    m_clpShowVector = clpShowVector;
  }

  std::vector<std::shared_ptr<Show>> fnGetShowList()
  {
    return m_clpShowVector;
  }

  void fnSetTheatreShowList(std::unordered_map<std::shared_ptr<Theatre>, std::vector<std::shared_ptr<Show>>> clpTheatreToShowVector)
  {
    m_clpTheatreToShowVector = clpTheatreToShowVector;
  }

  std::unordered_map<std::shared_ptr<Theatre>, std::vector<std::shared_ptr<Show>>> fnGetTheatreToShowList()
  {
    return m_clpTheatreToShowVector;
  }

private:
  std::vector<std::shared_ptr<Show>> m_clpShowVector;
  std::unordered_map<std::shared_ptr<Theatre>, std::vector<std::shared_ptr<Show>>> m_clpTheatreToShowVector;
};

#endif // SHOWSEARCHRESULT_H