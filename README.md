Chat server and clients

Helpful link:
http://www.thegeekstuff.com/2011/12/c-socket-programming/?utm_source=feedburner


TODO:
1- Convert server to daemon - Done
2- Client shouldn't see its own prints locally. (probably need to remove a printf somewhere in the code...) - Done
3- Append given name to text in chat. - Done , issue #2.
4- Chat should be in a new clean window.
5- Send chat history to new connections - (Need to allocate a buffer for history, which will be updated with te recent data)

Nice to have:
1- Show "typing..." indication.
2- Add flags to client. - e.g. to allow server-ip as a parameter.


Issues:
1- No lock for protected access to mutual thread variable buf_len - and still somehow works. 
2- Output gets scrumbled - need to figure out why.


