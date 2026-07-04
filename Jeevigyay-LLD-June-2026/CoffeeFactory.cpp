class CoffeeFactory
{
public:
  static std::unique_ptr<Coffee> fnGetCoffee(string name)
  {
    if("Cappuccino" == name)
    {
      return std::make_unique<CappuccinoCoffee>();
    }

    else if("Espresso" == name)
    {
      return std::make_unique<EspresssoCoffee>();
    }

    return nullptr;
  }
};