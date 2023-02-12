# wxScrab Gen

wxScrab gen is a Scrabble game generator

## Compilation

Compilation is done via `scons`

```
$ scons
```

To install, run 

```
$ scons install
```

## wxScrab other projects

wxScrab includes three programs:

* (wxScrab Gen)[https://github.com/philippechataignon/wxscrab_gen]: A generator built from parts of the program Eliot
   (http://www.nongnu.org/eliot/), which, from a dictionary in
   dawg format generates an XML file. 

   The contribution from Eliot is the addition of
   an algorithm of choice among different possible tops. The
   generator also includes a Python module in C for
   access the dictionary and verify the existence of a word (module
   dico). The programs are in the gen directory and the install script
   automates the construction (and includes a sudo to install the module
   Python)

* (wxScrab)[https://github.com/philippechataignon/wxscrab]: A server that is, from a file "part" generated in the previous step, will manage the game. The server is written in Python and uses Twisted. 

* (wxScrab_client)[https://github.com/philippechataignon/wxscrab_client]: A GUI client that can connect to the server. The program is written in Python and uses the wxPython library. To play on a existing server,
   as the public server wxscrab.ath.cx, port 12345, this is the only program required.
