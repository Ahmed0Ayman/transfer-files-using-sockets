


#this is simple makefile


all :  server  client  client2

server: server.o 
	gcc $^ -o $@


client:  client.o
	gcc $^ -o $@

client2:  client2.o
	gcc $^ -o $@



%.o: %.c 
	gcc  -c   $<

.PHONY: clean

clean: 
	rm  *.o  
	rm server client 
