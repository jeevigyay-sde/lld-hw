int main()
{
  std::unique_ptr<Coffee> clpCappuccinoCoffee =  CoffeeFactory::fnGetCoffee("Cappuccino");
  std::unique_ptr<Coffee> clpChocolateCappuccino = std::unique_ptr<ChocolateSyrup>(std::move(clpCappuccinoCoffee));
  
  std::cout<<"Cost of the coffee" <<clpChocolateCappuccino->getCost(); 

  std::unique_ptr<Coffee> clpEspressoCoffee =  CoffeeFactory::fnGetCoffee("Espresso");
  std::unique_ptr<Coffee> clpEspressoMilk = std::unique_ptr<ChocolateSyrup>(std::move(clpEspressoCoffee));

  std::cout<<"Cost of the coffee" <<clpEspressoMilk->getCost(); 

}