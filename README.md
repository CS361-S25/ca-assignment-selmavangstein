# Continuous Cellular Automaton (CA)

This program implements a **continuous cellular automaton** using the [Empirical Toolkit (emp-toolkit)](https://github.com/devosoft/Empirical) and `emp::web::Animate`.

The readme file is created with the help of AI. 

##  How It Works

The CA evolves over a grid of cells where each cell has a continuous value between 0 and 1. The main update rule is non-linear and influenced only by **east and north neighbors**. In addition, there is an override case if a cell has exactly one active neighbor. 

Most configurations tested end up in a large rain-like pattern that I found pretty cool.

###  Rules of Evolution

Each cell is updated according to:
- A **sigmoid function** of the sum of its **east and north** neighbors:  
  $$\[
  \text{newvalue} = \frac{1}{1 + e^{-3(\text{sum} - 1)}}
  \]$$
- If a cell has **exactly 1 active neighbor** (value > 0.5), it is **turned up to max (1.0)**.

## Initial Configurations

The default initialization creates a small diagonal pattern that spreads. You can uncomment alternate configurations to test different setups, or create your own. 



[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/StQAS8iq)
