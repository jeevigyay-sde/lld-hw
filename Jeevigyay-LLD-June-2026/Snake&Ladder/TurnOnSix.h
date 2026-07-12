class TurnOnSix : public TurnStrategy
{
public:
  TurnOnSix(std::vector<std::shared_ptr<Player>> clPlayerList) : TurnStrategy(clPlayerList){} 
  
  void fnOnTurnCompleted(int diceNumber) override
  {
    if(diceNumber == 6)
    {
      return;
    }
    __super::fnOnTurnCompleted(diceNumber);
};