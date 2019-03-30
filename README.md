<a href="https://github.com/branilson"><img src="https://github.com/branilson/1BtDimmer/raw/master/img/1BtD.png" title="Branilson Luiz" alt="BranlsonLuiz"></a>

<!-- [![Branilson Luiz(https://github.com/branilson/1BtDimmer/raw/master/img/1BtD.png](https://github.com/branilson) -->


# One buttom Dimmer Mbed code

> Finite state machine code sample for a dimmer controller by one buttom only.

> Made for ST STM32F4 Discovery board using ARM Mbed library and PlatformIO IoT Ecosystem.

> Challenge for students of the discipline Microprocessed Systems II at SENAI CIMATEC university center.

> Keywords: One buttom Dimmer, Finite State Machine, C/C++, Mbed, STM32F4

**Finite State Machine policy**

- States: 
* RISE selenct; DOWN select; FALL intensity; MIN. reached; UP select; RISE intensity; MAX. reached.
- Initial state: UP
- Transition Red -> Green: t=10s
- Transition - UP --> DOWM: tBt<1s
- Transition - DOWN --> UP: tBt<1s
- Transition - DOWN --> FALL: tBt>=1s && i>0.0
- Transition - UP --> RISE: tBt>=1s && i<1.0. Rises intensity 5% per second and blinks off Blue LED 0.2s per second
- t = elapsed time; tBt =  time Button pressed.

<a href="https://github.com/branilson"><img src="https://github.com/branilson/1BtDimmer/raw/master/img/FSM_1BtD.png" title="Branilson Luiz" alt="BranlsonLuiz"></a>