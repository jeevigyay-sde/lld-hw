#ifndef BUTTON_H
#define BUTTON_H

class Button
{
public:
  virtual ~Button() = default;
  virtual void fnPressButton() = 0;

protected:
  int m_iFloor = -1;
};

#endif // BUTTON_H