---
layout: default
title: FlaSH, the flasher Shell
nav_order: 1
description: ""
permalink: /
---

## Welcome to FlaSH, the Flasher Shell

In order to carry out the first steps with the FSH application, a short intro is shown below, which also gives an overview of this page.

The flasher application uses a command line interface (CLI) and support [word completion](https://muhkuh-sys.github.io//org.muhkuh.tools-flasher_pt/Word_Completion.html). To start it write the following in your terminal (same directory as flasher):

```bash
 ./lua5.1 fsh.lua
```

The application will now run and automatically start a scan command which detects all possible plugins.

After that, a connection to a device can be established, for example, by applying of the command:

```bash
 connect romloader_uart_ttyUSB0
```

A connection with the device is now available with the help of the plugin and commands can be executed.

An overview of all possible commands is given by the help command by entering the following in the CLI:

```bash
 help
```

More information about the individual commands is available through the command:

```bash
 help 'name of command'
```

An animation of this introduction is also shown in the example [getting started](https://muhkuh-sys.github.io//org.muhkuh.tools-flasher_pt/Example_1.html).

More Examples of the flasher application can be viewed in the following:
- [Write, Verify, Hash and Read Data](https://muhkuh-sys.github.io//org.muhkuh.tools-flasher_pt/Example_2.html) 
- [Erase and Iserase](https://muhkuh-sys.github.io//org.muhkuh.tools-flasher_pt/Example_3.html) 
- [Input Command](https://muhkuh-sys.github.io//org.muhkuh.tools-flasher_pt/Example_4.html) 
- [List Command Example 1](https://muhkuh-sys.github.io//org.muhkuh.tools-flasher_pt/Example_5.html) 
- [List Command Example 2](https://muhkuh-sys.github.io//org.muhkuh.tools-flasher_pt/Example_6.html) 
- Or all examples with the [asciinema player](https://muhkuh-sys.github.io//org.muhkuh.tools-flasher_pt/Examples_asciinema_player.html) 

Further details on the individual functions of the FSH application can be found in the documentation [LDOC](https://muhkuh-sys.github.io//org.muhkuh.tools-flasher_pt/index_LDOC.html). 

The [release notes](https://muhkuh-sys.github.io//org.muhkuh.tools-flasher_pt/release_notes.html) give an overview of the changes and newest features of the flasher application.
