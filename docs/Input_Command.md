---
layout: default
title: Input Command
parent: Documentation
has_children: true
nav_order: 3
has_toc: false
---
The input command executes a file with a list of commands - line by line. There are three different ways of executing the input command:

1. By using of the command:

```bash
 input cmdList.txt
```

2. By using of the list command which can be seen in the example [List Command Example 1](https://muhkuh-sys.github.io//org.muhkuh.tools-flasher_pt/Examples_asciinema_player.html#list-command-example-1). First of all a list has to be created or loaded and is then executed with the 'run' command (separate command of the list command).
3. By using of the argument "-i" or "--input" like for example:

```bash
 ./lua5.1 fsh.lua -i cmdList.txt
```

or 

```bash
 ./lua5.1 fsh.lua --input cmdList.txt
```


