# compilers-course
## Progress description: 

![](https://i.imgur.com/ak2QpVP.jpg)

1. Creating a skeleton of our interpreter
- - We created 4 trivial functions READ, EVAL, PRINT, and rep (read-eval-print). READ, EVAL, and PRINT are basically just stubs that return their first parameter (a string cause our target language is a statically typed) and rep calls them in order passing the return to the input of the next.

- - Add a main loop that repeatedly prints a prompt, gets a line of input from the user, calls rep with that line of input, and then prints out the result from rep. It should also exit when we send it an EOF (often Ctrl-D).

- - As well as C++ is AOT lang (ahead-of-time rather than just-in-time), so we created make file for further work.