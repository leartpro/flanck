# FLANCK SIMPLE LIBRARY

Bei Flanck handelt es sich um eine Touring-Complete Sprache.
Dabei wurde der Syntax minimal gehalten und gleichzeitig eine hohe Funktionalität angestrebt.

## ABOUT

Die Bibliothek liefert den Lexer, den Parser und den Interpreter der Sprache Flanck.
Dazu ebenfalls die Utility-Klassen Stack, Statement und Token.
Der `Lexer` benötigt eine `char*` als Parameter und kann dann dem `Parser`als Parameter übergeben werden.
Dieser wiederum kann dem `Interpreter`als Parameter übergeben werden.
`Interpreter.interpret()` interpretiert den übergebenen Code.
Anschließend kann der Ausgabe-`Stack` abgerufen und ausgegeben werden.

### IDEA

Die Idee von Flanck orientiert sich an einem Kellerautomaten.
Das Alphabet besteht dabei nur aus `0` und `1`.
In Flanck kann es beliebig viele Keller geben, womit Flanck Touring-Complete ist.
Eine weitere Besonderheit ist, dass in jedem Schritt beliebig viele Terminale
von einem Keller gelesen werden können, als auch hinzugefügt werden können.

### SYNTAX

`[]` ist ein Keller.
In einem Keller können die Symbole `0` und `1` stehen.
Der erste Keller dient zur Ausgabe und alle (auch der erste) Keller dienen zur Eingabe.
In jeder Zeile steht genau ein Statement.
Ein Statement besteht aus Conditions, einem Separator (`:`) und Instructions.
Conditions und Instructions können aus beliebig vielen Kellern bestehen.
Ein Statement muss keine Conditions oder Instructions haben.
Alle Statements werden so lange von oben nach unten abgearbeitet, bis es keine Änderungen in den Stacks mehr gibt. 
Davon ausgenommen sind Statements ohne Conditions.
Instructions werden genau dann nicht ausgefüllt, wenn ein Stack in den Conditions nicht erfüllt ist.
Wenn ein Stack in den Conditions nicht betrachtet werden soll, wird er als leerer Keller repräsentiert.
Wenn die Conditions erfüllt sind, wird vor der Ausführung der Instructions das "gelesene" von den Stacks genommen.
Die Programmeingabe kann als Text oder als Binär gegeben werden, dabei wird Text zu Binär umgewandelt.
Keller sind Stacks, daher werden sie immer von oben betrachtet (oben->`[01010]`).
Alle Terminale, welche nicht zur Sprache gehören werden ignoriert.
Im Code ist ein Stack ein vector<> und dabei ist Index 0 oben.

<!--TODO: Programmeingabe muss richtig rum eingelesen werden, alles andere angepasst werden-->

## LIBRARY USAGE

1. create a folder called `libs` in your project root
2. checkout the `libs` folder and run
    ```sh
      git clone https://github.com/leartpro/flanck.git -b library
    ```
3. configure your CMakeLists.txt
    ```cmake
        add_subdirectory(libs/flanck)
        target_link_libraries(${PROJECT_NAME}
            flanck
            # Add any other libs you want to use here
        )
    ```
4. to use flanck in your code:
   ```c++
      #include "flanck.h"
   ```
   
## DEMO <!--TODO: does not work that way-->

Zuerst muss die Library kompiliert werden.
Dazu muss in das Verzeichnis `library` navigiert werden.
Anschließend muss `compile.sh` ausgeführt werden.

Nun kann `to_path.sh` ebenfalls ausgeführt werden, 
um die Bibliothek global verwenden zu können.
Da hier Zugriff auf `/usr/local/lib` benötigt wird,
muss mit `sudo` ausgeführt werden.

Im Verzeichnis `demo`muss nun ebenfalls `compile.sh`ausgeführt werden.
Jetzt kann `run_from_path.sh` oder `run_from_libary.sh` ausgeführt werden.
Um `run_from_path.sh` zu verwenden, muss vorher die Library global installiert worden sein.

Es sollte nun `Hello World` in der Konsole ausgegeben werden.

### USAGE <!--TODO: does not fit to #SYNTAX-->

Um eine ``.flanck`` Datei auszuführen muss der Pfad zur Datei angegeben werden.
Optional kann zusätzlich ein Input angegeben werden.
Ob der Input als Binär oder als Ascii interpretiert wird, kann durch eine Flag angegeben werden.
Dabei kann der Input für jeden Keller separat angegeben werden.
Ein beispielhafter Aufruf in der Konsole könnte sein:
```sh
    $ flanck helloWorld.flanck
```
Hier liegt die Zieldatei bereits im gleichen Verzeichnis
und bekommt keine zusätzlichen Parameter.

Ein weiter Aufruf könnte wie folgt aussehen:
```sh
    $ flanck example.flanck -b 0 10010 1111
```
Hier wird auf die ersten drei Stapel gelegt.
Durch die Flag `-b` wird der Input als Binär gelesen.
Hier ist die Flag optional, da die Eingabe standardmäßig als Binär interpretiert wird.

Wenn Text als Input gegeben wird, wird dieser zu Binär umgewandelt.
```sh
    $ flanck example.flanck -a Hello World!
```
Hier wird auf die ersten beiden Stapel gelegt, wobei `Hello` und `World!` als Ascii interpretiert werden.
Der erste Stapel würde daher das binäre Äquivalent von `Hello` enthalten (`0100100001100101011011000110110001101111`).

Durch eine zweite Flag kann die Ausgabe spezifiziert werden.
So wird im Folgenden der ascii Input als Binär ausgegeben.
```sh
    $ flanck example.flanck -a -b Hello World!
```

| flag | name   | usage                                |
|------|--------|--------------------------------------|
| -a   | ascii  | interprets/print as ascii            |
| -b   | binary | interprets/print as binary (default) |

Um einen Keller zu überspringen, kann `_` verwendet werden.
```sh
    $ flanck example.flanck -a -b _ Hello World!
```
Hier wird nur auf den zweiten und dritten Keller gelegt.

### EXAMPLES <!--TODO: incorrect syntax and thrash example-->

```shell
    [][0]:[0][0]
    [][0]:[1][10]
    [][10]:[0][110]
    [][110]:[0][1110]
    [][1110]:[1][110]
    [][110]:[0][10]
    [][10]:[0][0]
    [][0]:[0][1]
```

Dieses Beispiel zeigt, wie der Buchstabe `H` bitweise aufgebaut wird.
Da die Bedingung in der ersten Anweisung nur erfüllt ist, wenn eine `0` auf dem zweiten Stapel liegt
und eine Ausgabe in Ascii gewünscht ist, eignet sich der folgende Aufruf:
```sh
    $ flanck example.flanck -b -a _ 0
```