---
layout: default
title: Release Notes
parent: News
has_children: true
nav_order: 1
has_toc: false
---

# Release Notes
{: .no_toc }
The release notes of the flasher shell.

## Table of contents
{: .no_toc .text-delta }

1. TOC
{:toc}

---

## Release Notes 1.6.8

### Adding Progress Bar Information

The respective commands now show their progress through progress bar information.
<p align="center">
  <img src="img/release_1.6.8_progressBar.png" alt="progress bar example" width="100%" height="100%">
</p>

### Expanding the Help Command - New Design

<p align="center">
  <img src="img/release_1.6.8_help_command.png" alt="help command example" width="100%" height="100%">
</p>

### New Feature: Input Command

The input command reads a file with commands (one command per line) and executes them after the commands have been validated. An example of the input command can be seen in the following: 
<script id="asciicast-406267" src="https://asciinema.org/a/406267.js" async></script>

### New Feature: List Command

The list command activates the list mode and supports the creation and editing of a list of commands. Numerous auxiliary commands are available within this mode. The following clip shows an example of the list command:
<script id="asciicast-406268" src="https://asciinema.org/a/406268.js" async></script>

### New Feature: Debug Command 

The debug command enables debug information to be displayed or saved.
<p align="center">
  <img src="img/release_1.6.8_debug_command.png" alt="debug command example" width="100%" height="100%">
</p>

### Hash Command:  Expanded for Internal Flash

<p align="center">
  <img src="img/release_1.6.8_hash_IF01.png" alt="hash IF01 example" width="100%" height="100%">
</p>

### Adding Documentation (LDOC) of fsh.lua, progressbar.lua and flasher.lua 

The documentation of the modules can be found [here](https://muhkuh-sys.github.io//org.muhkuh.tools-flasher_pt/index_LDOC.html).

### Improvement of Minor Bugs
