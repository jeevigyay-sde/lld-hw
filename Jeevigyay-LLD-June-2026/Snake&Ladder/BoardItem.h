class BoardItem
{
protected:
  int iStartPos;
  int iEndPos;


public:
  virtual int fnGetFinalPos() = 0;

  void fnSetStartPos(int pos)
  {
    iStartPos = pos;
  }

  void fnSetEndPos(int pos)
  {
    iEndPos = pos;
  }

  virtual ~BoardItem();
};