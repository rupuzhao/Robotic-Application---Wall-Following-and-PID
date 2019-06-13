# Robotic-Application---Wall-Following-and-PID

Note: This program is made for Arduino hardware robot

This lab builds a library to use the distance sensors. The main task is to implement closed loop controls and wall following.

𝑢r(𝑡) = 𝑓sat( 𝐾p (𝑟(𝑡) − 𝑦(𝑡)))
𝑟(𝑡) − 𝑦(𝑡))represents the distance error that will change as 𝑦(𝑡) the real distance changes. When the real distance decrease, the error also decreases. 𝐾p represents proportional gain that influences the initial speed of robot. 𝑓sat is the function that limits the input of function “setSpeedsIPS”.

