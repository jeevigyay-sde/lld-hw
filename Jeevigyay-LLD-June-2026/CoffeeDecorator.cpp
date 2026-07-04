class CoffeeDecorator : public Coffee
{
public:
  CoffeeDecorator(std::unique_ptr<Coffee> clpaCoffee) : m_clpCoffee(std::move(clpaCoffee)){}

  virtual ~CoffeeDecorator()
  {
    m_clpCoffee = nullptr;
  }

protected:
  std::unique_ptr<Coffee> m_clpCoffee;

};

class ChocolateSyrup : public CoffeeDecorator
{
public:
  ChocolateSyrup(std::unique_ptr<Coffee> clpaCoffee) : CoffeeDecorator(std::move(clpaCoffee)){}
    
  ~ChocolateSyrup() override = default;

  int getCost()
  {
    return m_clpCoffee->getCost() + 200;
  }

};

class ExtraMilk : public CoffeeDecorator
{
public:
  ExtraMilk(std::unique_ptr<Coffee> clpaCoffee) : CoffeeDecorator(std::move(clpaCoffee)){}
    
  ~ExtraMilk() override = default;

  int getCost()
  {
    return m_clpCoffee->getCost() + 50;
  }
};