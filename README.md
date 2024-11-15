# school-project-comp.cs.110
- Programming course 2, individual project, spring -22.
- Implementation of the game called "2048".
- Overall grade for the course: 4

## Usage

### Run locally
in path: school-project-comp.cs.110/student/12/numbers_gui  
Generate Makefile with qmake
```sh
qmake -o Makefile numbers_gui.pro
```
.. then build
```sh
make
```
.. and run the executable
on macOs
```sh
open numbers_gui.app
```
non-macOs, check Makefile´s "TARGET" to see where it places the executable and run
```sh
./numbers_gui
```


## Learning goals
Designing and implementing a graphical user interface with Qt.  
Using Qt documentation.  
Modularity and separating user interface from the action logic of the program.



