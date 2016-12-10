TRLWO-2198

Description:
Create console client-server application for moving a file.

Assignee:
basecamp.lwo5

Subtasks:
1. Create "Socket" class.
2. Implement connection of client to server.
3. Create console interface.
4. Implement move command.
5. Add Linux OS support.
6. Improve console interface.

Project build info:

This project consists of two subprojects: Client and Server.
Use the included Makefiles to complile server.
Comlpile those programs using "make -f makecli" and "make -f makeserv".
After that you can launch "Server.out" (executable) using "./Server.out" in your terminal
and "Client.out" using "./Client.out".
This version allows to connect to a server and view the root files.

Workflow:
To start a server, press 'r' button during the program's flow.
To connect to a server by a client, select and appropriate item in the menu, and press 'o' or 'Enter'
button. Now you should see server's root files (C:\ or / for Unix).
To move to another folder you should "select it" by pointing with an arrow on the left,
and then press 'o' or 'Enter'. To move to the previous folder, press 'b'.
To select file for moving, press 'x', and paste into another folder by pressing 'v'.
Moving to another directory routine  - done.
Moving files - done, works with small files - 100%, requires further testing.
Moving to another drive will be implemented soon(I think so).