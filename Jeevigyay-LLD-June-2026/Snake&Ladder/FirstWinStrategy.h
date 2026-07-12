class FirstWinStrategy : public WinStrategy
{
public:
  bool fnIsGameOver(std::vector<std::shared_ptr<Player>> clPlayerList, Board clBoard) override
  {
    for(auto player : clPlayerList)
    {
      if(clBoard->fnHasPlayerWon(player))
      {
        return true;
      }
    }
    return false;
  }
};