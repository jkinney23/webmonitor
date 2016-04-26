# webmonitor
A simple web-based linux system monitor based on sample GNU/Linux application from chapter 11 of [Advanced Linux Programming](http://advancedlinuxprogramming.com/alp-folder/advanced-linux-programming.pdf) by Mark Mitchell, Jeffrey Oldham,
and Alex Samuel (2001).

Additional modules will be added and html improved and styled with modern css as a final project for edX cs50.
```
Usage: ./server [ options ]
  -a, --address ADDR      Bind to local address (by default, bind to all local addresses).
  -h, --help              Print this information.
  -m, --module-dir DIR    Load modules from specified directory (by default, use executable directory).
  -p, --port PORT         Bind to specified port.
  -v, --verbose           Print verbose messages.
```
Modules are viewed in browser at `localhost:PORT/MODULE`

#####TODO:
- separate html head, etc, into html.h file for DRY-er html code (Complete!)
- finish styling for modules (Complete!)
- add a home page (Complete!)
- see about adding a navigation bar (Complete!)
- add nav buttons to footer
- clean up and separate nav-bar generation (future)
- separate and clean up other html generation (future)

License Note: The code this project is adapted from appears to be covered by the GPL version 2, which I suppose implies the code in this repository is also covererd by GPL version 2.
