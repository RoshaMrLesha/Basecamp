TRLWO-2198

Description:
Create console client-server application for moving a file.

Assignee:
basecamp.lwo5

Subtasks:
1. Create "Socket" class. - done
2. Implement connection of client ot server. - done 
3. Create console interface. - done 
4. Implement move command. - done 
5. Add Linux OS support. - done 
6. Improve console interface.

Project build info:

This project consists of two subprojects: Client and Server.
To run client:
1. Add to your Visual Studio 201x project the following files:
	socket.h
	clientsocket.h
	clientsocket.cpp
	clientsource.cpp
	clientui.h
	clientui.cpp
	ui.h
	directoryprocessor.h
	directoryviewer.cpp
	directoryviewer.h
	unixgetch.h
	unixgetch.cpp
2. Compile using Visual Studio 201x.
To run server:
1. Add to another(!) Visual Studio 201x project the following files:
	socket.h
	serversocket.h
	serversocket.cpp
	serversource.cpp
	serverui.h
	serverui.cpp
	ui.h
	directoryprocessor.h
	directorymanager.h
	directorymanager.cpp
2. Compile using Visual Studio 201x.

Compilation under UNIX-systems is described in Deliverables/Readme.txt

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