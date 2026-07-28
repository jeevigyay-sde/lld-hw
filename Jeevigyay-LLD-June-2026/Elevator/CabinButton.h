#ifndef CABINBUTTON_H
#define CABINBUTTON_H

#include <memory>

#include "Button.h"
#include "InternalRequest.h"
#include "ElevatorController.h"

class CabinButton : public Button
{
public:
  CabinButton(std::shared_ptr<ElevatorController> clpController, int iaFloor)
  {
    m_iFloor = iaFloor;
    m_clpElevatorController = clpController;
  }

  void fnPressButton() override
  {
    std::shared_ptr<InternalRequest> clpRequest = std::make_shared<InternalRequest>(m_iFloor);
    m_clpElevatorController->fnSubmitRequest(clpRequest->fnGetDestinationFloor());
  }

private:
  std::shared_ptr<ElevatorController> m_clpElevatorController = nullptr;
};

#endif // CABINBUTTON_H