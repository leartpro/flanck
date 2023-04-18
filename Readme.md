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
Optional kann ein Input als zweiter Parameter angegeben werden.
Dabei kann der Input für jeden Keller separat angegeben werden.
Ein beispielhafter Aufruf in der Konsole könnte sein:
```sh
    $ flanck helloWorld.flanck 0
```
Hier liegt die Zieldatei bereits im gleichen Verzeichnis 
und bekommt ``0`` als zusätzlichen Parameter.

Ein weiter Aufruf könnte wie folgt aussehen:
```sh
    $ flanck example.flanck 0|10010|1111
```
Hier wird auf die ersten drei Stapel gelegt.

## SYNTAX

1. Es kann so viele Spalten geben wie man möchte
2. Jeder Befehl wird durch eine neue Linie getrennt
3. Alle zeichen bis auf die folgenenden werden ignoriert: []:01\n
4. Ein Befehl besteht aus den spalten und was daraus gelesen werden einem : und was auf den spalten geschrieben wird
5. Es muss immer ein : geben, wie viele lese und schreibe spalten es gibt ist egal
6. gibt es mehr lese als schreibe oder mehr schreibe als lese spalten, wird rechts alle nicht angegebenen so gewertet, das sie weder gelesen, noch geschrieben werden
7. eine spalte wird mit [ angefangen und mit ] beendet
8. das linkeste zeichen wird zu erst gelesen, das rechte zu erst auf die spalte gelegt
9. man kann nur 0 und 1 auf eine spalte legen bzw. lesen
10. die erste spalte ist dem lesen, die zwei dem schreiben gewidmet
11. Die befehle werden von oben nach unten durchgeführt, wenn kein befehl mehr übrig ist, wird wieder von oben angefangen
12. das programm kann per standart nicht beendet werden, der interpretierer kann jedoch entscheiden das programm zu ändern wenn bei einem kompletten durchlauf kein stapel verändert wird, oder wenn das EOT zeichen ausgegeben wird
13. Das Zeichen was zuerst in der Spalte liegt wird zuerst ausgegeben
14. Comments macht man mit #, gibt nur Zeilenkommentare

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