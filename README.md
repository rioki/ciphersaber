
Rioki's Implementation of the Ciphersaber
=========================================

The [Ciphersaber][1] is a small and practical implementation of cryptography with 
the help of the RC4 cipher. 

This was a fun hobby project of mine. You should not use it for anything serious.
There are a number of flaws with the ciphersaber. It uses the system's rand 
function, initialized with time. The RC4 cipher is not considered safe anymore.

You can do with code whatever you like, see COPYING.txt for details.

Special thanks to [gnibbler][2] and [CodesInChaos][3] for pointing out the flaws 
int the code.

[1]: http://ciphersaber.gurus.org/
[2]: https://stackoverflow.com/users/174728/gnibbler
[3]: https://stackoverflow.com/users/445517/codesinchaos
