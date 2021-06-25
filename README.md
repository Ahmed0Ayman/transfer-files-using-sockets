this commit I want to use the server to serve parallel client but how can that be  , so we have multiple solution 

one of them that I implemented in this commit is the nature of fork the process into multiple process 
but you need also to know that when you fork your process you are actually generate a new process with its Owen  resources but its bad solution when you deal with concurrency so the best solution that I prefer is use multi threads so you can generate as you want number of threads with Owen attributes 
so this commit I use to introduce the idea not much that this    
so if you look at the structure of the project you will find client & client2 & server these are executable  files that we will deal with so just type make in your terminal then open terminal for each process  

you can use signals to pause and resume the server application 


https://www.youtube.com/watch?v=dZ7Ve1CVWdY

