#ifndef HALLBUTTON_H
#define HALLBUTTON_H

#include "Button.h"
#include "ElevatorManagementSystem.h"
#include "Direction.h"

class HallButton : public Button
{
public:
  HallButton(std::shared_ptr<ElevatorManagementSystem> clpSystem, Direction enmaDirection, int iaFloor)
  {
    m_enmDirection = enmaDirection;
    m_iFloor = iaFloor;
    m_clpElevatorSystem = clpSystem;
  }

  void fnPressButton() override
  {
    std::shared_ptr<ExternalRequest> clpRequest = std::make_shared<ExternalRequest>(m_iFloor,
                                                                                    m_enmDirection);
    m_clpElevatorController = m_clpElevatorSystem->fnSubmitRequest(clpRequest);
  }

  std::shared_ptr<ElevatorController> fnGetElevatorController()
  {
    return m_clpElevatorController;
  }

private:
  Direction m_enmDirection;
  std::shared_ptr<ElevatorManagementSystem> m_clpElevatorSystem = nullptr;
  std::shared_ptr<ElevatorController> m_clpElevatorController = nullptr;
};

#endif // HALLBUTTON_H