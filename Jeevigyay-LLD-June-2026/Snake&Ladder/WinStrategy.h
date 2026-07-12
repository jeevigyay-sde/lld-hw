class WinStrategy
{
public:
  virtual bool fnIsGameOver(std::vector<std::shared_ptr<Player>> clPlayerList, Board clBoard) = 0;
};