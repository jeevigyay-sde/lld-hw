#include "Board.h"
#include "BoardItem.h"

class BoardFactory
{
public:
  static std::shared_ptr<Board> fnCreateBoard()
  {
    int row = 10;
    int col = 10;

    std::pair<int,int> pair = {rows,col};
    
    std::vector<std::pair<int,int>> snakePair = {{10,99},{21,57},{22,61},{15,87},{45,52}};
    std::vector<std::pair<int,int>> ladderPair = {{12,44},{24,65},{41,72},{56,92},{67,98}};

    unordered_map<int,std::shared_ptr<BoardItem>> iBoardItemMap;
    for(int i=0;i<5;i++)
    {
      std::shared_ptr<BoardItem> snake = std::make_shared<snake>();
      snake->fnSetStartPos(snakePair[i].first);
      snake->fnSetEndPos(snakePair[i].second);

      iBoardItemMap[snakePair[i].second] = snake;

      std::shared_ptr<BoardItem> ladder = std::make_shared<Ladder>();
      snake->fnSetStartPos(ladderPair[i].first);
      snake->fnSetEndPos(ladderPair[i].second);

      iBoardItemMap[snakePair[i].first] = ladder;

    }

    std::shared_ptr<Board> clBoard = std::make_shared<Board>(pair,iBoardItemMap);
    return clBoard;
  }

};