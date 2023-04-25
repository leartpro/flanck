# FLANCK

Bei Flanck handelt es sich um eine Touring-Complete Sprache.
Dabei wurde der Syntax minimal gehalten und gleichzeitig eine hohe Funktionalität angestrebt.

## IDEA

Die Idee von Flanck orientiert sich an einem Kellerautomaten.
Das Alphabet besteht dabei nur aus `0` und `1`.
In Flanck kann es beliebig viele Keller geben, womit Flanck Touring-Complete ist.
Eine weitere Besonderheit ist, dass in jedem Schritt beliebig viele Terminale 
von einem Keller gelesen werden können, als auch hinzugefügt werden können.

## USAGE

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

## SYNTAX

Der erste Keller dient zur Ausgabe.
Pro Zeile darf es nur eine Anweisung geben.
Es kann so viele Keller geben wie man möchte
Pro Zeile darf es nur eine Anweisung geben.
Jede Anweisung setzt sich aus beliebig vielen Kellern als Bedingung, einem Trennzeichen `:` und danach aus beliebig vielen Instruktionen zusammen.
Es müssen keine Bedingungen oder Instruktionen in einem Statement vorkommen.
Alle Terminale, welche nicht zur Sprache gehören werden ignoriert.
Wenn als Bedingung mehr von einem Keller ausgelesen wird, als enthalten ist, gilt die Bedingung als nicht erfüllt.
Ein Keller wird mit `[` angefangen und mit `]` beendet.
Die Anweisungen werden so lange wiederholend ausgeführt, bis es zu keinen Änderungen in den Kellern mehr kommt.
Die Keller verwalten als Symbole nur `0` und `1`.
Die Anweisungen werden von oben nach unten abgearbeitet.
Die Programmeingabe kann als Text oder als Binär gegeben werden, dabei wird Text zu Binär umgewandelt.

## EXAMPLES

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