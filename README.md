##TODO:
#Sockets
- After disconnecting a lot of clients, the server start acting weird and stop listening to new clients (They can connect, but cannot send/receive much)
- The server doesn't seem to detect *every* disconnection
- To reproduce:
1. Start server
2. Start client "Livin and forkin"
3. Wait till about a hundred players are on the server
4. Kill the client (CTRL+C), the server will not disconnect all clients, despite them not existing anymore
5. Try to connect any client to the server, the server will quickly stop answering
6. Disconnect the new client, the server won't disconnect it
7. Connect a new client, the server will answer once or twice and then stop.[^1]
8. Disconnect it, the server will properly register it
9. Go back to step 5.

#Performance
- Disconnecting clients is relatively slow. May just be the printing.

[^1]: A variant if you stop the server with a lower amount of players on it is, it will only listen to *one* player and ignore others, *despite them connecting successfully*
