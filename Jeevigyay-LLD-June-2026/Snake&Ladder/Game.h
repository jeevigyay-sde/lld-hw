class Game
{
private:
  std::shared_ptr<Board> clBoard;
  std::vector<std::shared_ptr> clPlayerList;
  std::shared_ptr<Dice> clDice;
  std::shared_ptr<WinStrategy> clWinStrategy;
  std::shared_ptr<TurnStrategy> clTurnStrategy;

public:
  Game(std::shared_ptr<Board> Board, std::vector<std::shared_ptr> playerList, std::shared_ptr<Dice> dice)
  {
    clBoard = board;
    clPlayerList = playerList;
    clDice = dice;
  }

  void fnSetWinStrategy(std::shared_ptr<WinStrategy> winStrategy)
  {
    clWinStrategy = winStrategy;
  }

  void fnTurnStrategy(std::shared_ptr<TurnStrategy> turnStrategy)
  {
    clTurnStrategy = turnStrategy;
  }

  void fnPlay()
  {
    while(!clWinStrategy->fnIsGameOver(clPlayerList))
    {
      std:shared_ptr<Player> clPlayer = clTurnStrategy->fnGetNextPlayerTurn();
      int num = clDice->fnGetDiceNumber();
      if(clBoard->fnIsValidMove(clCurrentPlayer->fnGetCurrentPos() + num))
      {
        int newPos = clBoard->fnGetFinalPos();
        clCurrentPlayer.move(newPos);    
      }
    }
    clTurnStrategy->fnOnTurnCompleted(num);
  }

};