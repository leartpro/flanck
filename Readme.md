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
Optional kann ein Input angegeben werden.
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
Der erste Stapel

*Es ist zu beachten, dass der binäre Input von rechts nach links auf den Keller gelegt wird.
Beispielsweise entspricht `01100001` der Eingabe `a`.*

## SYNTAX

# TO-DO: der erste Keller soll als Ausgabe dienen, nicht der zweite
# TO-DO: es soll auch möglich sein, in der Eingabe Keller zu überspringen
# TO-DO: mit '<' zu Begin der Zeile soll, bei erfüllter Bedingung, der Ausgabekeller direkt ausgegeben werden und nicht erst am Ende des Programms (nicht geleert)
# TO-DO: mit > zu Begin der Zeile wird so lange auf eine Benutzereingabe gewartet, bis die Bedingung des Statements akzeptiert ist; auch falsche Eingaben werden gespeichert

1. Es kann so viele Keller geben wie man möchte
2. Pro Zeile darf es nur ein Statement geben
3. Jedes Statement setzt sich aus beliebig vielen Kellern als Bedingung, einem Trennzeichen `:` und danach aus beliebig vielen Anweisungen zusammen.
4. Es müssen keine Bedingungen oder Anweisungen in einem Statement vorkommen.
5. Mit `#` kann ein Zeilenkommentar gestartet werden, alles danach wird bis zum Ende der Zeile ignoriert.
6. Wenn als Bedingung mehr von einem Keller ausgelesen wird, als enthalten ist, gibt die Bedingung als nicht erfüllt.
7. Ein Keller wird mit `[` angefangen und mit `]` beendet.
8. Die Statements werden so lange wiederholend ausgeführt, bis es zu keinen Änderungen in den Kellern mehr kommt.
9. Die Keller verwalten als Symbole nur `0` und `1`.
10. Der Inhalt des zweiten Stapels wird am Ende des Programms als Ascii UTF-8 interpretiert und ausgegeben, dabei wird unten im Stapel angefangen.
11. Die Statements werden von oben nach unten abgearbeitet.
12. Die Programmeingabe kann als Text oder als Binär gegeben werden, dabei wird Text als Binär Interpretiert
13. Der Ausgabekeller wird am Ende des Programms ausgegeben

## EXAMPLES

Dieses beispiel zeigt ...
```shell
    [0]:[0][0]
    [0]:[01][1]
    [01]:[011][0]
    [011]:[0111][0]
    [0111]:[0][1]
    [0]:[0][0]
    [0]:[0][0]
    [0]:[1][0]
```