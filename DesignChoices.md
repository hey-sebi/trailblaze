# Design Choices

This document lists decisions that were made during developmend of the library. Some decisions are listed with reasons why the selection was made.

## General / global impact choices

| What | Why  | Comment |
|------|------|---------|
| C++ version is limited to 17 | C++ 20 is not yet widely available. In order to provide wider flexibility, we stick with C++ 17 for now. | This is subject to change in the future |