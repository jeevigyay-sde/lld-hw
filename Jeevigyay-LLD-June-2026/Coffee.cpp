class Coffee
{
public:
  Coffee() = default;
  virtual ~Coffee() = default;
protected:
  virtual int getCost() = 0;
};


class EspresssoCoffee : public Coffee
{
public:
  EspresssoCoffee() = default;
  ~EspresssoCoffee() override = default;

  int getCost()
  {
    return 400;
  }
};

class CappuccinoCoffee : public Coffee
{
public:
  CappuccinoCoffee() = default;
  ~CappuccinoCoffee() override = default;

  int getCost()
  {
    return 500;
  }
};

