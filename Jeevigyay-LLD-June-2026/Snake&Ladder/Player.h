class Player
{
private:
  string playerId;
  string username;
  int iCurrentPos;

public:

  Player(string id, string username)
  {
    playerId = id;
    username = username;
    iCurrentPos = 1;
  }

  void move(int newPos)
  {
    iCurrentPos = newPos;
  }

  int fnGetCurrentPos()
  {
    return iCurrentPos;
  }
  
};