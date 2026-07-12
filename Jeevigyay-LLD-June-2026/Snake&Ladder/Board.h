#include <BoardItem.h>

class Board
{
private:
  std::pair<int,int> iBoardSize;
  unordered_map<int,std::shared_ptr<BoardItem>> uBoardItemMap;
  
public:

  Board(std::pair<int,int> BoardSize, unordered_map<int,std::shared_ptr<BoardItem>> BoardItemMap)
  {
    iBoardSize = BoardSize;
    uBoardItemMap = BoardItemMap;
  }

  bool fnIsValidMove(int pos)
  {
    if(pos > iBoardSize.first * iBoardSize.second)
    {
      return false;
    }
    else if(pos < 1)
    {
      return false;
    }
    return true;
  }

  int fnGetFinalPos(int currentPos)
  {
    if(uBoardItemMap.find(currentPos) != uBoardItemMap.end())
    {
      clBoardItem = uBoardItemMap[currentPos];
      return clBoardItem->fnGetCurrentPos();
    }
    return currentPos;
  }

  bool fnHasPlayerWon(std::shared_ptr<Player> player)
  {
    return (player.fnGetCurrentPos() == iBoardSize.first * iBoardSize.second);
  }

};