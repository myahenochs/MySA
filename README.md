# MySA
(Actual title in the works)

Design and implementation an 8-Bit ISA simulation done for my CSCI 480 course.

The course goal is to do research, then design and implement a project in preparation for grad school.
I took this course because I had limited choice in the offered classes, not to prepare for grad school, so my project's goal is to make something I'm interested in and proud of at the end--a test of my own ability to design and learn to finish a solid implementation.

## Project Goals:
  1.  *Real-world hardware fidelity*: While this ISA design does not have physical limitations, as it is being implemented in software, they will still be considered. The intention is to create the ISA in such a way that a hardware implementation would be possible, given the means. 
  2.  *Extensive documentation and code readability*: Each component will be extensively documented in both design and behavior. This will be provided in the form of a UML, graphical depiction, and written explanation. The implementation will also feature comprehensible code where possible, rather than concision, with ample comments. Defining micro-operations for each instruction will be distinctly included as an exercise in attention to detail and fidelity. 
  3.  *Fully-modular components*: Because each component does not “know” about its environment, only its input and output, it would be most preferred to implement the components in this way, as well. This also has the added bonus of allowing for anyone to replace a component with their own, re-write control logic, or use a component in another ISA without the need to revise any implementation for it to work.  
  4.  *Register-level abstraction*: While it would be ideal to compose an ISA down to the logic gates, the timescale of the course would make this a large undertaking, and would also make the project much less accessible to others wanting to learn architecture. The chosen level of abstraction will omit digital logic outside of the logical instructions provided in the instruction set. 

## Components and Features:
  The CPU will contain a register file, ALU, and MMU as objects, 4 general-purpose registers, and the standard special-purpose registers (MDR, instruction register, etc.).
  Main memory will be one object that will interact with the CPU mainly via the data bus and address bus. Because I am not implementing parallel programming (yet), the MMU will have to interact directly with the RAM.
  Features implemented include, in order of addition:
  - [ ] Pointers
  - [ ] Arrays
  - [ ] Functions
  - [ ] Parameterized functions
  - [ ] Recursion
  
  I am not expecting all of these to be implemented by the end of this course, but goals are nice.
 
## Long-term goals:
  1.  Correct or add sacrificed ideas due to course limitations. Any design that was tweaked to fit a smaller scope will be revised to its originality, and features that were omitted will be included. 
  2.  Reduce abstraction as I learn more about computer architecture. Digital logic may either be a part of a forked project or added to this one. 
  3.  Implement a full system. This includes non-volatile memory and a graphics/picture processing unit. Modularity would continue to be a main design goal as more devices are added. 
  4.  Adding parallelism to further create a more true-to-life simulation.

## To Compile
  This program was completely developed in Linux and has not been tested in Windows or OS X whatsoever.

  1. `git clone https://github.com/myahenochs/MySA`
  2. `cd MySA`
  3. `make`

## To Use
  Create a file containing each byte of input on a separate line, then pass it as a command line argument to the program.
  
  main.cpp has some simple functions to use in order to check input and output and can be changed at will.
