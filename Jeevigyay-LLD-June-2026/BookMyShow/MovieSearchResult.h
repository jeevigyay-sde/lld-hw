#ifndef MOVIESEARCHRESULT_H
#define MOVIESEARCHRESULT_H

#include <vector>
#include <memory>

#include "SearchResult.h"
#include "Movie.h"

class MovieSearchResult : public SearchResult
{
public:
  void fnSetMovieList(std::vector<std::shared_ptr<Movie>> clpMovieVector)
  {
    m_clpMovieVector = clpMovieVector;
  }

  std::vector<std::shared_ptr<Movie>> fnGetMovieList()
  {
    return m_clpMovieVector;
  }

private:
  std::vector<std::shared_ptr<Movie>> m_clpMovieVector;
};

#endif // MOVIESEARCHRESULT_H