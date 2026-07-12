class TurnStrategy
{
public:
  TurnStrategy(<std::shared_ptr<Player>> clPlayerList)
  {
    for(auto player : clPlayerList)
    {
      clPlayerQueue.push(player);
    }
  }

  virtual ~TurnStrategy();
  
  std::shared_ptr<Player> fnGetNextPlayerTurn()
  {
    if(clPlayerQueue.empty())
    {
      return nullptr;
    }
    return clPlayerQueue.front();
  }

  virtual void fnOnTurnCompleted(int diceNumber)
  {
    while(!clPlayerQueue.empty())
    {
      std::shared_ptr<Player> player = clPlayerQueue.front();
      clPlayerQueue.pop();
      if(clPlayerQueue.empty())
      {
        return;
      }
      clPlayerQueue.push(player);
      return clPlayerQueue.front();
    }
    return nullptr;
  }

protected:
  std::queue<std::shared_ptr<Player>> clPlayerQueue;
};