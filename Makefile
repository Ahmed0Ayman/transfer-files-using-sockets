


#this is simple makefile


all :  server  client 

server: server.o 
	gcc $^ -o $@


client:  client.o
	gcc $^ -o $@

%.o: %.c 
	gcc  -c   $<

.PHONY: clean

clean: 
	rm  *.o  
	rm server client 
