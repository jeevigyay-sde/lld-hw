class Snake : public BoardItem
{
public:
  int fnGetFinalPos() override
  {
    return iStartPos;
  }
};