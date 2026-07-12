class Ladder : public BoardItem
{
public:
  int fnGetFinalPos() override
  {
    return iEndPos;
  }
};