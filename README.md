# dancingPaper

- set board address according to label on controller before flashing in boardConfig.h.
- Motor connectors A(+/-) and B(+/-) are interchangeble.
- Vm and VIN can be jumpered behind screw terminals.
- power can be supplied via screw terminals or USB socket of NodeMCU.
- supply voltage is 5V (USB).
- if IS_REMOTE_CONTROLLER is set to 'true' in boardConfig.h ADDRESS_NUMBERR_ON_LABEL will be ignored and board address is set to ADDRESS_OF_REMOTE_CONTROLLER.
- a switch form REMOTE_SWITCH_PIN (D5) to GND deactivates motors. (uses internal pullup)
- LED near USB connector of remote controller indicates performance execution.
