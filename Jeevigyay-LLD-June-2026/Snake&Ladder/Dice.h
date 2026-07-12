class Dice
{
private:
  int kFace;
  int iNum = 0;
  void fnRoll()
  {
    iNum = (rand() % kFace) + 1;
  }

public:
  Dice(int k)
  {
    kFace = k;
  }

  int fnGetDiceNumber()
  {
    fnRoll();
    return iNum;
  }

};