<a href="https://github.com/branilson"><img src="https://github.com/branilson/1BtDimmer/raw/master/img/1BtD.png" title="Branilson Luiz" alt="BranlsonLuiz"></a>

<!-- [![Branilson Luiz(https://github.com/branilson/1BtDimmer/raw/master/img/1BtD.png](https://github.com/branilson) -->


# One buttom Dimmer Mbed code

> Finite state machine code sample for a dimmer controller by one buttom only

> The controlled light is the green LED LD7, connected to port PA9

> Made for ST STM32F4 Discovery board using ARM Mbed library and PlatformIO IoT Ecosystem.

> Challenge for students of the discipline Microprocessed Systems II at SENAI CIMATEC university center.

> Keywords: One buttom Dimmer, Finite State Machine, C/C++, Mbed, STM32F4

### Finite State Machine policy

***States:***
- DOWN select: Orange LED ON
- UP select: Blue LED ON
- FALL intensity: Decrease intensity 5% per second while the orange LED is ON and flashing off 0.2s per second
- MIN. reached: 0% intensity reached. Orange LED flashes at 5Hz until the button releases
- RISE intensity: Increase intensity 5% per second while the blue LED is ON and flashing off 0.2s per second
- MAX. reached: 100% intensity reached. Blue LED flashes at 5Hz until the button releases

***Transitions:***
- Initial state: UP
- Transition - UP -> DOWN: tBt<1s
- Transition - DOWN --> UP: tBt<1s
- Transition - DOWN --> FALL: tBt>=1s && i>0.0
- Transition - UP --> RISE: tBt>=1s && i<1.0
- Transition - UP --> RISE: tBt>=1s && i<1.0 
- Transition - FALL --> MIN: Bt==1 && i==0.0
- Transition - RISE --> MAX: Bt==1 && i==1.0
- Transition - MAX --> DOWN: Bt==0 && i==1.0
- Transition - MIN --> UP: Bt==0 && i==0.0

***Acronyms:***
- Bt = Buttom
- tBt =  time Button pressed
- i = intensity

***Diagram:***

<a href="https://github.com/branilson"><img src="https://github.com/branilson/1BtDimmer/raw/master/img/FSM_1BtD.png" title="Branilson Luiz" alt="BranlsonLuiz"></a>