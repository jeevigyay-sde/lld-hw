class AllExceptOneWinStrategy : public WinStrategy
{
public:
  bool fnIsGameOver(std::vector<std::shared_ptr<Player>> clPlayerList, Board clBoard) override
  {
    int count = 0;
    for(auto player : clPlayerList)
    {
      if(clBoard->fnHasPlayerWon(player))
      {
        count++;
      }
    }
    return count == (clPlayerList.size() - 1);
  }
};